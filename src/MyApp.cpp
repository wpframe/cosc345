#include "MyApp.h"
#include "Stock.h"
#include "Calendar.h"
#include "Purchase.h"
#include "Portfolio.h"
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000
Calendar calendar;
Portfolio portfolio;
int TIMECOUNT;
bool startLoadingPortfolio = false;
std::vector<Stock> stocks;

/*
TODO:
- refactor page navigation, using: overlay_->view()->LoadURL("file:///portfolio.html");
-
**/

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

  /* read in the stocks csv only once, when the app is run */

  // std::string filename = "../../../../src/data/scraping/nasdaq_etf_screener_1691614852999.csv"; // FOR MAC
  // std::string filename = "../../../../src/data/nasdaq_screener_filtered.csv"; // FOR MAC

  // std::string filename = "src/data/scraping/nasdaq_etf_screener_1691614852999.csv"; // FOR WINDOWS
  // std::string filename = "../src/data/nasdaq_screener_filtered.csv"; // FOR WINDOWS

  std::string pathPrefix = findPathFromApp();
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

std::string MyApp::findPathFromApp()
{
  std::string pathPrefix;
#if defined(__linux__)
  pathPrefix = "../";
#elif defined(__APPLE__)
  pathPrefix = "../../../../";
#else
  pathPrefix = "../";
#endif

  return pathPrefix;
}

void MyApp::OnUpdate()
{
  ///
  /// OnUpdate is called constantly by the app so anything that needs to be updated on the page goes in here
  ///
  ultralight::String script;
  std::string jsScript = "";
  if (startLoadingPortfolio == 1)
  {

    std::vector<Purchase> purchases = portfolio.getPurchases();
    for (const Purchase &purchase : purchases)
    {
      // std::string symbol = purchase.getStockSymbol();
      // std::string currentPrice = std::to_string(purchase.getPurchasePrice());
      // std::string quantity = std::to_string(purchase.getQuantity());
      ultralight::String symbol = purchase.getStockSymbol().c_str();
      ultralight::String currentPrice = std::to_string(purchase.getPurchasePrice()).c_str();
      ultralight::String quantity = std::to_string(purchase.getQuantity()).c_str();

      script = "addStockTile('" + symbol + "', '" + currentPrice + "', '" + quantity + "')";
      view_->EvaluateScript("addStockTile('" + symbol + "', '" + currentPrice + "', '" + quantity + "')");
    }

    // ultralight::String script = jsScript.c_str();

    startLoadingPortfolio = false;
  }
  if (!calendar.isCounting())
  {
    return;
  }
  TIMECOUNT = calendar.getWeeks();
  calendar.update();
  ultralight::String date = calendar.getDate().c_str();
  view_->EvaluateScript("showDate('" + date + "')"); // view_ is an instance of View so can be called upon as you would 'caller'

  // view_->EvaluateScript("addStockTile('ebay', '888888', '43')");
}

void MyApp::OnClose(ultralight::Window *window)
{
  app_->Quit();
}

void MyApp::OnResize(ultralight::Window *window, uint32_t width, uint32_t height)
{
  ///
  /// This is called whenever the window changes size (values in pixels).
  ///
  /// We resize our overlay here to take up the entire window.
  ///
  overlay_->Resize(width, height);
}

void MyApp::OnFinishLoading(ultralight::View *caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const String &url)
{
  ///
  /// This is called when a frame finishes loading on the page.
  ///
}

std::string JSStringToStdString(JSStringRef jsString)
{
  size_t maxBufferSize = JSStringGetMaximumUTF8CStringSize(jsString);
  char *utf8Buffer = new char[maxBufferSize];

  JSStringGetUTF8CString(jsString, utf8Buffer, maxBufferSize);
  std::string result(utf8Buffer);

  delete[] utf8Buffer;
  return result;
}

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
    portfolio.addPurchaseToPortfolio(portfolio, selectedStock, quantity, selectedStock.history[TIMECOUNT].closePrice, calendar);

    // Purchase *p = portfolio.getPurchase(selectedStock.getSymbol());

    // std::string purchaseInfo = "Symbol: " + p->getStock().getSymbol() +
    //                            "  Quantity: " + std::to_string(p->getQuantity()) +
    //                            "  Purchase Price:" + std::to_string(p->getPurchasePrice()) +
    //                            "  Purchase Date:" + p->getTimeStamp();

    // std::string jscode =
    //     "document.getElementById('purchaseInfoDiv').innerHTML = '" + purchaseInfo + "'";

    // const char *str = jscode.c_str();
    // // Create our string of JavaScript
    // JSStringRef script = JSStringCreateWithUTF8CString(str);

    // // Execute it with JSEvaluateScript, ignoring other parameters for now
    // JSEvaluateScript(ctx, script, 0, 0, 0, 0);

    // // Release our string (we only Release what we Create)
    // JSStringRelease(script);

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
  // Create a garbage-collected JavaScript function that is bound to our native C callback 'startTimer()'.
  JSObjectRef startTimerFunc = JSObjectMakeFunctionWithCallback(ctx, startTimerRef, startTimer);
  JSObjectRef stopTimerFunc = JSObjectMakeFunctionWithCallback(ctx, stopTimerRef, stopTimer);
  JSObjectRef fastForwardFunc = JSObjectMakeFunctionWithCallback(ctx, fastForwardRef, fastForward);
  JSObjectRef commitPurchaseFunc = JSObjectMakeFunctionWithCallback(ctx, commitPurchaseRef, commitPurchase);
  JSObjectRef cppSelectStockFunc = JSObjectMakeFunctionWithCallback(ctx, cppSelectStockRef, cppSelectStock);
  JSObjectRef loadPortfolioFunc = JSObjectMakeFunctionWithCallback(ctx, loadPortfolioRef, loadPortfolio);

  // Get the global JavaScript object (aka 'window')
  JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
  // Store our function in the page's global JavaScript object so that it accessible from the page as 'startTimer()'.
  JSObjectSetProperty(ctx, globalObj, startTimerRef, startTimerFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, stopTimerRef, stopTimerFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, fastForwardRef, fastForwardFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, commitPurchaseRef, commitPurchaseFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, cppSelectStockRef, cppSelectStockFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, loadPortfolioRef, loadPortfolioFunc, 0, 0);
  // Release the JavaScript String we created earlier.
  JSStringRelease(startTimerRef);
  JSStringRelease(stopTimerRef);
  JSStringRelease(fastForwardRef);
  JSStringRelease(commitPurchaseRef);
  JSStringRelease(cppSelectStockRef);
  JSStringRelease(loadPortfolioRef);

  caller->EvaluateScript("showStockInfo('Price per stock: ', '0')");

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
