
/*!
    @file
    @brief The implementation for linking with UI
    @details Gives us the ability to display web assets (HTML, CSS, JS) on the screen
      while linking to c++ and javascript functions
*/

#include "MyApp.h"
#include "Stock.h"
#include "Calendar.h"
#include "Purchase.h"
#include "Portfolio.h"
#include "PathUtil.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000
Calendar calendar;
Portfolio portfolio(100000.0);
int TIMECOUNT;
float TOTALBALANCE;
bool startLoadingPortfolio = false;
std::vector<Stock> stocks;
ultralight::String latestDate = "01/01/2023";

/*
TODO:
- refactor page navigation, using: overlay_->view()->LoadURL("file:///portfolio.html");
- seg faults when a stock with no data is chosen from the dropdown
**/

/*!
    @brief Constructor for the MyApp class.
    @details This constructor initializes the main application, creates a resizable window,
      sets up an HTML overlay, loads a webpage, registers listeners for various events,
      and reads stock data from a CSV file.

*/
MyApp::MyApp()
{
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
                           false, kWindowFlags_Titled | kWindowFlags_Resizable);

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(window_, 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_.get(), window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///homepage.html");

  ///
  /// Register our MyApp instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our MyApp instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our MyApp instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  overlay_->view()->set_load_listener(this);

  ///
  /// Register our MyApp instance as a ViewListener so we can handle the
  /// View's OnChangeCursor and OnChangeTitle events below.
  ///
  overlay_->view()->set_view_listener(this);

  std::string pathPrefix = PathUtil::findPathFromApp();
  std::string filename = pathPrefix + "src/data/nasdaq_screener_filtered.csv";

  stocks = parseCSV(filename);
  if (!stocks.empty())
  {
    // for (int i = 0; i < static_cast<int>(stocks.size()); ++i) // FOR LOOP FOR ALL STOCKS
    for (int i = 0; i < std::min(100, static_cast<int>(stocks.size())); ++i) // FOR LOOP FOR FIRST 100
    {
      const Stock &stock = stocks[i];
      stocks[i].parseHistory();
      stocks[i].predictNextX(2600);
    }
  }
  else
  {
    std::cout << "No stocks found in the CSV.  MyApp.cpp - MyApp::OnDOMReady method" << std::endl;
  }
}

MyApp::~MyApp()
{
}

void MyApp::Run()
{
  app_->Run();
}

/*!
  @brief Method called by the app's update loop.
  @details This method performs all operations which need to be constantly updated.
    Calculates the in-game date.
*/
void MyApp::OnUpdate()
{
  ///
  /// OnUpdate is called constantly by the app so anything that needs to be updated on the page goes in here
  ///

  if (!calendar.isCounting())
  {
    // calendar.update();
    return;
  }
  ultralight::String date = calendar.getDate().c_str();
  latestDate = date;
  view_->EvaluateScript("showDate('" + date + "')"); // view_ is an instance of View so can be called upon as you would 'caller'
  TIMECOUNT = calendar.getWeeks();
  calendar.update();
}

/*!
  @brief Method is called whenever the window is closed.
  @details Quits the application.
  @param window an ultralight instance of the Window.
**/
void MyApp::OnClose(ultralight::Window *window)
{
  app_->Quit();
}

/*!
  @brief Method is called whenever the window changes size.
  @details resizes the overlay to take up the entire window.
  @param window an ultralight instance of Window.
  @param width width of the screen in pixels.
  @param height height of the screen in pixels.
**/
void MyApp::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

/*!
  @brief Method is called when a frame finishes loading on the page.
  @details Not used.
  @param caller instance of View.
  @param frame_id id for the current frame.
  @param is_main_frame check for whether current frame is main frame.
  @param url url.
**/
void MyApp::OnFinishLoading(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url)
{
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

/*!
  @brief Method which converts a JSString into a std::string
  @param jsString a JSString
  @return result, a std::string
**/
std::string JSStringToStdString(JSStringRef jsString)
{
  size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
  char *utf8Buffer = new char[maxBufferSize];

  JSStringGetUTF8CString(jsString, utf8Buffer, maxBufferSize);
  std::string result(utf8Buffer);

  delete[] utf8Buffer;
  return result;
}

/*!
  @brief startTimer is a function which starts the in-game calendar
  @details startTimer is a function which is called from javascript, and will perform cpp operations.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which
  @param arguments list of arguments
  @param exception value reference
**/
JSValueRef startTimer(JSContextRef ctx, JSObjectRef function,
                      JSObjectRef thisObject, size_t argumentCount,
                      const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// startTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.startCounting();
  return JSValueMakeNull(ctx);
}

JSValueRef stopTimer(JSContextRef ctx, JSObjectRef function,
                     JSObjectRef thisObject, size_t argumentCount,
                     const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// stopTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.pauseCounting();
  return JSValueMakeNull(ctx);
}

JSValueRef fastForward(JSContextRef ctx, JSObjectRef function,
                       JSObjectRef thisObject, size_t argumentCount,
                       const JSValueRef arguments[], JSValueRef *exception)
{
  if (argumentCount >= 3)
  {
    int years = static_cast<int>(JSValueToNumber(ctx, arguments[0], nullptr));
    int months = static_cast<int>(JSValueToNumber(ctx, arguments[1], nullptr));
    int days = static_cast<int>(JSValueToNumber(ctx, arguments[2], nullptr));

    calendar.skipTime(years, months, days);
  }
  return JSValueMakeNull(ctx);
}

JSValueRef commitPurchase(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[], JSValueRef *exception)
{
  if (argumentCount >= 3)
  {
    JSStringRef jsSymbol = JSValueToStringCopy(ctx, arguments[0], nullptr);
    JSStringRef jsBuyOrSell = JSValueToStringCopy(ctx, arguments[1], nullptr);
    int quantity = static_cast<int>(JSValueToNumber(ctx, arguments[2], nullptr));
    // JSStringRef jsPurchase = JSValueToStringCopy(ctx, arguments[3], nullptr);

    // Convert JSStringRef to C++ std::string
    std::string symbol = JSStringToStdString(jsSymbol);
    std::string buyOrSell = JSStringToStdString(jsBuyOrSell);
    // std::string purchaseString = JSStringToStdString(jsPurchase);

    // Release JSStringRef
    JSStringRelease(jsSymbol);
    JSStringRelease(jsBuyOrSell);
    // JSStringRelease(jsPurchase);

    std::vector<Purchase> purchases;

    Stock selectedStock = Stock::findStockBySymbol(symbol, stocks);

    const auto &history = selectedStock.history;
    if (buyOrSell == "Buy")
    {
      if (quantity > 0)
      {
        portfolio.addPurchaseToPortfolio(portfolio, selectedStock, quantity, selectedStock.history[TIMECOUNT].closePrice, calendar);
      }
    }
    if (buyOrSell == "Sell")
    {
      if (quantity > 0)
      {
        // portfolio.addPurchaseToPortfolio(portfolio, selectedStock, quantity, selectedStock.history[TIMECOUNT].closePrice, calendar);
        portfolio.sellPurchase(selectedStock, quantity, selectedStock.history[TIMECOUNT].closePrice);
      }
    }

    portfolio.summarizePortfolio(TIMECOUNT);
  }
  return JSValueMakeNull(ctx);
}

JSValueRef cppSelectStock(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[], JSValueRef *exception)
{
  if (argumentCount >= 1)
  {
    JSStringRef jsSymbol = JSValueToStringCopy(ctx, arguments[0], nullptr);
    std::string symbol = JSStringToStdString(jsSymbol);

    JSStringRelease(jsSymbol);

    Stock selectedStock = Stock::findStockBySymbol(symbol, stocks);
    // Stock selectedStock = stocks[10];

    const auto &history = selectedStock.history;

    std::string closePriceString = std::to_string(selectedStock.history[TIMECOUNT].closePrice);

    std::string jscode =
        "document.getElementById('currentPrice').innerText = 'Price per stock: $" + closePriceString + "'";

    const char *str = jscode.c_str();

    // Create our string of JavaScript
    JSStringRef script = JSStringCreateWithUTF8CString(str);

    // Execute it with JSEvaluateScript, ignoring other parameters for now
    JSEvaluateScript(ctx, script, 0, 0, 0, 0);

    // Release our string (we only Release what we Create)
    JSStringRelease(script);
  }
  return JSValueMakeNull(ctx);
}

JSValueRef loadPortfolio(JSContextRef ctx, JSObjectRef function,
                         JSObjectRef thisObject, size_t argumentCount,
                         const JSValueRef arguments[], JSValueRef *exception)
{
  startLoadingPortfolio = true;
  return JSValueMakeNull(ctx);
}

JSValueRef toggleDropdown(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// startTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.pauseCounting();
  return JSValueMakeNull(ctx);
}

void MyApp::OnDOMReady(ultralight::View *caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String &url)
{
  view_ = caller; // creating a new instance of View with the contents of caller, for use in other functions

  //  This is called when a frame's DOM has finished loading on the page. /
  //  This is the best time to setup any JavaScript bindings./
  //  This method will be called every time the UI shows a different html page.

  // Acquire the JS execution context for the current page.
  auto scoped_context = caller->LockJSContext();
  // Typecast to the underlying JSContextRef.
  JSContextRef ctx = (*scoped_context);
  // Create a JavaScript String containing the name of our callback.
  JSStringRef startTimerRef = JSStringCreateWithUTF8CString("startTimer");
  JSStringRef stopTimerRef = JSStringCreateWithUTF8CString("stopTimer");
  JSStringRef fastForwardRef = JSStringCreateWithUTF8CString("fastForward");
  JSStringRef commitPurchaseRef = JSStringCreateWithUTF8CString("commitPurchase");
  JSStringRef cppSelectStockRef = JSStringCreateWithUTF8CString("cppSelectStock");
  JSStringRef loadPortfolioRef = JSStringCreateWithUTF8CString("loadPortfolio");
  // JSStringRef toggleDropdownRef = JSStringCreateWithUTF8CString("toggleDropdown");
  // Create a garbage-collected JavaScript function that is bound to our native C callback 'startTimer()'.
  JSObjectRef startTimerFunc = JSObjectMakeFunctionWithCallback(ctx, startTimerRef, startTimer);
  JSObjectRef stopTimerFunc = JSObjectMakeFunctionWithCallback(ctx, stopTimerRef, stopTimer);
  JSObjectRef fastForwardFunc = JSObjectMakeFunctionWithCallback(ctx, fastForwardRef, fastForward);
  JSObjectRef commitPurchaseFunc = JSObjectMakeFunctionWithCallback(ctx, commitPurchaseRef, commitPurchase);
  JSObjectRef cppSelectStockFunc = JSObjectMakeFunctionWithCallback(ctx, cppSelectStockRef, cppSelectStock);
  JSObjectRef loadPortfolioFunc = JSObjectMakeFunctionWithCallback(ctx, loadPortfolioRef, loadPortfolio);
  // JSObjectRef toggleDropdownFunc = JSObjectMakeFunctionWithCallback(ctx, toggleDropdownRef, toggleDropdown);

  // Get the global JavaScript object (aka 'window')
  JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
  // Store our function in the page's global JavaScript object so that it accessible from the page as 'startTimer()'.
  JSObjectSetProperty(ctx, globalObj, startTimerRef, startTimerFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, stopTimerRef, stopTimerFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, fastForwardRef, fastForwardFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, commitPurchaseRef, commitPurchaseFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, cppSelectStockRef, cppSelectStockFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, loadPortfolioRef, loadPortfolioFunc, 0, 0);
  // JSObjectSetProperty(ctx, globalObj, toggleDropdownRef, toggleDropdownFunc, 0, 0);
  // Release the JavaScript String we created earlier.
  JSStringRelease(startTimerRef);
  JSStringRelease(stopTimerRef);
  JSStringRelease(fastForwardRef);
  JSStringRelease(commitPurchaseRef);
  JSStringRelease(cppSelectStockRef);
  JSStringRelease(loadPortfolioRef);
  // JSStringRelease(toggleDropdownRef);

  caller->EvaluateScript("showStockInfo('Price per stock: ', '0')");
  caller->EvaluateScript("showDate('" + latestDate + "')");
  ultralight::String totalBalance = std::to_string(portfolio.getTotalBalance()).c_str();
  ultralight::String placeholder = "0";
  caller->EvaluateScript("initBalance('" + totalBalance + "')");
  caller->EvaluateScript("addInvestmentSummary('" + placeholder + "', '" + placeholder + "', '" + placeholder + "', '" + placeholder + "')");

  if (startLoadingPortfolio == 1)
  {
    float totalInvestment = 0.0;
    float portfolioValue = 0.0;
    std::vector<Purchase> purchases = portfolio.getPurchases();
    for (const Purchase &purchase : purchases)
    {
      Stock selectedStock = purchase.getStock();
      const auto &history = selectedStock.history;
      float currentPriceFloat = selectedStock.history[TIMECOUNT].closePrice;
      totalInvestment += purchase.getPurchaseValue();
      portfolioValue += purchase.getCurrentPurchaseValue(currentPriceFloat);

      float totalProfit = portfolioValue - totalInvestment;
      float totalProfitPercentage = (totalProfit / totalInvestment) * 100;

      ultralight::String symbol = purchase.getStockSymbol().c_str();
      ultralight::String purchasePrice = std::to_string(purchase.getPurchasePrice()).c_str();
      ultralight::String currentPrice = std::to_string(currentPriceFloat).c_str();
      ultralight::String quantity = std::to_string(purchase.getQuantity()).c_str();
      ultralight::String profitLoss = std::to_string(purchase.getProfitLoss(currentPriceFloat)).c_str();
      ultralight::String profitLossPercentage = std::to_string(purchase.getProfitLossPercentage(currentPriceFloat)).c_str();
      ultralight::String purchaseValue = std::to_string(purchase.getPurchaseValue()).c_str();
      ultralight::String currentPurchaseValue = std::to_string(purchase.getCurrentPurchaseValue(currentPriceFloat)).c_str();
      ultralight::String totalInvestmentStr = std::to_string(totalInvestment).c_str();
      ultralight::String portfolioValueStr = std::to_string(portfolioValue).c_str();
      ultralight::String totalProfitStr = std::to_string(totalProfit).c_str();
      ultralight::String totalProfitPercentageStr = std::to_string(totalProfitPercentage).c_str();

      caller->EvaluateScript("addStockTile('" + symbol + "', '" + purchasePrice + "', '" + currentPrice + "', '" + quantity + "', '" + profitLoss + "', '" + profitLossPercentage + "', '" + purchaseValue + "', '" + currentPurchaseValue + "')");
      // caller->EvaluateScript("addStockTile('" + symbol + "', '" + currentPrice + "', '" + quantity + "')");

      caller->EvaluateScript("updateBalance('" + totalBalance + "')");

      caller->EvaluateScript("updateInvestmentSummary('" + totalInvestmentStr + "', '" + portfolioValueStr + "', '" + totalProfitStr + "', '" + totalProfitPercentageStr + "')");
      // addInvestmentSummary(totalInvestment, portfolioValue, totalProfit, totalProfitPercentage)
      //  ultralight::String totalBalance = std::to_string(portfolio.getTotalBalance()).c_str();
    }

    // ultralight::String script = jsScript.c_str();

    startLoadingPortfolio = false;
  }

  if (!stocks.empty())
  {
    /*  LOADS EVERY STOCK ONTO THE STOCK SELECTOR **/
    // for (const Stock &stock : stocks)
    // {
    //   ultralight::String symbol = stock.symbol.c_str();
    //   caller->EvaluateScript("addStockDropdown('" + symbol + "')");
    // }

    /* LOADS FIRST 100 STOCKS **/
    for (int i = 0; i < std::min(100, static_cast<int>(stocks.size())); ++i)
    {
      const Stock &stock = stocks[i];
      ultralight::String symbol = stock.symbol.c_str();
      caller->EvaluateScript("addStockDropdown('" + symbol + "')");
    }
  }
  else
  {
    std::cout << "No stocks found in the CSV.  MyApp.cpp - MyApp::OnDOMReady method" << std::endl;
  }
}

void MyApp::OnChangeCursor(ultralight::View *caller,
                           Cursor cursor)
{
  ///
  /// This is called whenever the page requests to change the cursor.
  ///
  /// We update the main window's cursor here.
  ///
  window_->SetCursor(cursor);
}

void MyApp::OnChangeTitle(ultralight::View *caller,
                          const String &title)
{
  ///
  /// This is called whenever the page requests to change the title.
  ///
  /// We update the main window's title here.
  ///
  window_->SetTitle(title.utf8().data());
}
