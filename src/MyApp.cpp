
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
#include "Headline.h"
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
  std::string filename = pathPrefix + "src/data/nasdaq.csv";
  stocks = parseCSV(filename);

  std::string prefix = PathUtil::findPathFromApp();
  std::string filename2 = prefix + "src/data/headlines.csv";
  Headline::readFromCSV(filename2);
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
  @param argumentCount number of arguments which are passed in from javascript
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

/*!
  @brief stopTimer is a function which stops the in-game calendar
  @details stopTimer is a function which is called from javascript, and will perform cpp operations.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
**/
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

/*!
  @brief fastForward is a function which fast forwards the in-game calendar
  @details fastForward is a function which is called from javascript, and will perform cpp operations to
  fast forward the game time by given amount of time.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
  @param years (arguments[0]), number of years to skip
  @param months (arguments[1]), number of months to skip
  @param days (arguments[2]), number of days to skip
**/
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

/*!
  @brief commitPurchase is a function which commits a purchase and adds that purchase to the portfolio.
  @details checks if the user has enough money, then adds the purchase to portfolio if so.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
  @param jsSymbol (arguments[0]), the stocks ticker symbol
  @param jsBuyOrSell (arguments[1]), whether the purchase is long or short
  @param quantity (arguments[2]), the quantity being purchased
**/
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

    if (quantity > 0 && portfolio.getTotalBalance() - selectedStock.history[TIMECOUNT].closePrice * quantity >= 0)
    {
      portfolio.addPurchaseToPortfolio(portfolio, selectedStock, quantity, selectedStock.history[TIMECOUNT].closePrice, calendar, buyOrSell);
    }
    // portfolio.summarizePortfolio(TIMECOUNT);
  }
  return JSValueMakeNull(ctx);
}

/*!
  @brief commitSale is a function which commits a sale and removes that purchase from the portfolio.
  @details checks whether the purchase is a long or a short, then sells that purchase.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
  @param jsHoldingType (arguments[0]), whether the purchase is a long or a short
  @param jsSymbol (arguments[1]), the stocks ticker symbol
  @param amountToSell (arguments[2]), the quantity of stock being sold
  @param quantity (arguments[3]), the quantity of stock currently owned
**/
JSValueRef commitSale(JSContextRef ctx, JSObjectRef function,
                      JSObjectRef thisObject, size_t argumentCount,
                      const JSValueRef arguments[], JSValueRef *exception)
{
  if (argumentCount >= 4)
  {

    JSStringRef jsHoldingType = JSValueToStringCopy(ctx, arguments[0], nullptr);
    JSStringRef jsSymbol = JSValueToStringCopy(ctx, arguments[1], nullptr);
    int amountToSell = static_cast<int>(JSValueToNumber(ctx, arguments[2], nullptr));
    int quantity = static_cast<int>(JSValueToNumber(ctx, arguments[3], nullptr));

    // Convert JSStringRef to C++ std::string
    std::string holdingTypeStr = JSStringToStdString(jsHoldingType);
    std::string symbol = JSStringToStdString(jsSymbol);

    // Release JSStringRef
    JSStringRelease(jsHoldingType);
    JSStringRelease(jsSymbol);

    PositionType holdingType;
    if (holdingTypeStr == "Short")
    {
      holdingType = PositionType::Short;
    }
    else
    {
      holdingType = PositionType::Long;
    }

    std::vector<Purchase> purchases;

    Stock selectedStock = Stock::findStockBySymbol(symbol, stocks);

    const auto &history = selectedStock.history;

    if (quantity > 0)
    {
      portfolio.sellPurchase(selectedStock, amountToSell, selectedStock.history[TIMECOUNT].closePrice, holdingType);
    }

    // portfolio.summarizePortfolio(TIMECOUNT);
  }
  return JSValueMakeNull(ctx);
}

/*!
  @brief cppSelectStock is a function which loads the selected stock.
  @details predicts the future stock prices for the selected stock, and displays the price per stock on the screen.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
  @param jsSymbol (arguments[0]), the stocks ticker symbol
**/
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

    for (size_t i = 0; i < stocks.size(); ++i)
    {
      if (stocks[i].symbol == symbol)
      {
        stocks[i] = Stock::updateStockHistory(stocks[i]);
        selectedStock = stocks[i];
        break;
      }
    }

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

/*!
  @brief loadPortfolio is a function which sets a boolean to true.
  @details sets the boolean to true so that in the OnDOMReady function, the portfolio can be filled with purchases.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
**/
JSValueRef loadPortfolio(JSContextRef ctx, JSObjectRef function,
                         JSObjectRef thisObject, size_t argumentCount,
                         const JSValueRef arguments[], JSValueRef *exception)
{
  startLoadingPortfolio = true;
  return JSValueMakeNull(ctx);
}

/*!
  @brief toggleDropdown is a function which stops the calendar from counting when the dropdown is selected.
  @details stops the calendar so that stock prices arent continuosly changing when trying to purchase a stock.
  @param ctx Javascript context
  @param function Object reference
  @param thisObject Object reference
  @param argumentCount number of arguments which are passed in from javascript
  @param arguments list of arguments
  @param exception value reference
**/
JSValueRef toggleDropdown(JSContextRef ctx, JSObjectRef function,
                          JSObjectRef thisObject, size_t argumentCount,
                          const JSValueRef arguments[], JSValueRef *exception)
{
  calendar.pauseCounting();
  return JSValueMakeNull(ctx);
}

/*!
  @brief function which is called every time a new page is loaded onto the screen.
  @param caller instance of view
  @param frame_id the frame id
  @param is_main_frame bool which checks if current frame is the main frame.
  @param url the url of the page
**/
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
  JSStringRef commitSaleRef = JSStringCreateWithUTF8CString("commitSale");
  JSStringRef cppSelectStockRef = JSStringCreateWithUTF8CString("cppSelectStock");
  JSStringRef loadPortfolioRef = JSStringCreateWithUTF8CString("loadPortfolio");
  // JSStringRef toggleDropdownRef = JSStringCreateWithUTF8CString("toggleDropdown");
  // Create a garbage-collected JavaScript function that is bound to our native C callback 'startTimer()'.
  JSObjectRef startTimerFunc = JSObjectMakeFunctionWithCallback(ctx, startTimerRef, startTimer);
  JSObjectRef stopTimerFunc = JSObjectMakeFunctionWithCallback(ctx, stopTimerRef, stopTimer);
  JSObjectRef fastForwardFunc = JSObjectMakeFunctionWithCallback(ctx, fastForwardRef, fastForward);
  JSObjectRef commitPurchaseFunc = JSObjectMakeFunctionWithCallback(ctx, commitPurchaseRef, commitPurchase);
  JSObjectRef commitSaleFunc = JSObjectMakeFunctionWithCallback(ctx, commitSaleRef, commitSale);
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
  JSObjectSetProperty(ctx, globalObj, commitSaleRef, commitSaleFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, cppSelectStockRef, cppSelectStockFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, loadPortfolioRef, loadPortfolioFunc, 0, 0);
  // JSObjectSetProperty(ctx, globalObj, toggleDropdownRef, toggleDropdownFunc, 0, 0);
  // Release the JavaScript String we created earlier.
  JSStringRelease(startTimerRef);
  JSStringRelease(stopTimerRef);
  JSStringRelease(fastForwardRef);
  JSStringRelease(commitPurchaseRef);
  JSStringRelease(commitSaleRef);
  JSStringRelease(cppSelectStockRef);
  JSStringRelease(loadPortfolioRef);
  // JSStringRelease(toggleDropdownRef);

  caller->EvaluateScript("showStockInfo('Price per stock: ', '0')");
  caller->EvaluateScript("showDate('" + latestDate + "')");
  ultralight::String totalBalance = std::to_string(portfolio.getTotalBalance()).c_str();
  ultralight::String placeholder = "0";
  caller->EvaluateScript("initBalance('" + totalBalance + "')");
  caller->EvaluateScript("addInvestmentSummary('" + placeholder + "', '" + placeholder + "', '" + placeholder + "', '" + placeholder + "')");

  std::string prefix = PathUtil::findPathFromApp();
  std::string filepath = prefix + "src/data/graph/data.csv";
  ultralight::String filepathStr = filepath.c_str();
  caller->EvaluateScript("getFilePath('" + filepathStr + "')");

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
      std::string headlineStr = selectedStock.history[TIMECOUNT].headline;
      float headlineMultiplierStr = selectedStock.history[TIMECOUNT].multiplier;

      float totalProfit = portfolioValue - totalInvestment;
      float totalProfitPercentage = (totalProfit / totalInvestment) * 100;
      totalInvestment += purchase.getPurchaseValue();
      portfolioValue += purchase.getCurrentPurchaseValue(currentPriceFloat);

      std::string holdingTypeStr;
      PositionType type = purchase.getPositionType();
      if (type == PositionType::Short)
      {
        holdingTypeStr = "Short";
      }
      else
      {
        holdingTypeStr = "Long";
      }

      ultralight::String holdingType = holdingTypeStr.c_str();
      ultralight::String symbol = purchase.getStockSymbol().c_str();
      ultralight::String purchasePrice = std::to_string(purchase.getPurchasePrice()).c_str();
      ultralight::String currentPrice = std::to_string(currentPriceFloat).c_str();
      ultralight::String headline = headlineStr.c_str();
      ultralight::String headlineMultiplier = std::to_string(headlineMultiplierStr).c_str();
      ultralight::String quantity = std::to_string(purchase.getQuantity()).c_str();
      ultralight::String profitLoss = std::to_string(purchase.getProfitLoss(currentPriceFloat)).c_str();
      ultralight::String profitLossPercentage = std::to_string(purchase.getProfitLossPercentage(currentPriceFloat)).c_str();
      ultralight::String purchaseValue = std::to_string(purchase.getPurchaseValue()).c_str();
      ultralight::String currentPurchaseValue = std::to_string(purchase.getCurrentPurchaseValue(currentPriceFloat)).c_str();
      ultralight::String totalInvestmentStr = std::to_string(totalInvestment).c_str();
      ultralight::String portfolioValueStr = std::to_string(portfolioValue).c_str();
      ultralight::String totalProfitStr = std::to_string(totalProfit).c_str();
      ultralight::String totalProfitPercentageStr = std::to_string(totalProfitPercentage).c_str();

      caller->EvaluateScript("addStockTile('" + holdingType + "', '" + symbol + "', '" + purchasePrice + "', '" + currentPrice + "', '" + quantity + "', '" + profitLoss + "', '" + profitLossPercentage + "', '" + purchaseValue + "', '" + currentPurchaseValue + "', '" + headline + "', '" + headlineMultiplier + "')");

      caller->EvaluateScript("updateBalance('" + totalBalance + "')");

      caller->EvaluateScript("updateInvestmentSummary('" + totalInvestmentStr + "', '" + portfolioValueStr + "', '" + totalProfitStr + "', '" + totalProfitPercentageStr + "')");
    }
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
