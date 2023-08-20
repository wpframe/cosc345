#include "MyApp.h"
#include "Stock.h"
#include "Calendar.h"
#include <iostream>
#include <vector>
#include <string>

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000
Calendar calendar;

// WILL NEED THIS FUNCTION BECAUSE PATH FROM APP TO CSV FILES IS DIFFERENT ON MACOS

// std::string findPathFromApp()
// {

//   // char buffer[PATH_MAX]; // PATH_MAX is a macro representing the maximum path length
//   // if (getcwd(buffer, sizeof(buffer)) == nullptr)
//   // {
//   //   std::cout << "Could not find current directory: " << std::endl;
//   //   return "";
//   // }
//   std::string buffer = "/Users/admin/Desktop/cosc345/cosc345/build/MyApp.app/Contents/MacOS/MyApp";

//   // std::__fs::filesystem::path currentPath = std::__fs::filesystem::current_path(); // NEED TO UPDATE COMPILER TO USE THIS
//   std::string modifiedPath = buffer;

//   size_t pos = modifiedPath.rfind("build");

//   if (pos != std::string::npos)
//   {
//     modifiedPath.erase(pos);
//   }

//   return modifiedPath;
// }

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
}

MyApp::~MyApp()
{
}

void MyApp::Run()
{
  app_->Run();
}

void MyApp::OnUpdate()
{
  ///
  /// OnUpdate is called constantly by the app so anything that needs to be updated on the page goes in here
  ///
  if (!calendar.isCounting())
  {
    return;
  }

  calendar.update();
  ultralight::String date = calendar.getDate().c_str();
  view_->EvaluateScript("showDate('" + date + "')"); // view_ is an instance of View so can be called upon as you would 'caller'
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
JSValueRef forwardWeek(JSContextRef ctx, JSObjectRef function,
                       JSObjectRef thisObject, size_t argumentCount,
                       const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// stopTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.skipTime(1, 0, 0);
  return JSValueMakeNull(ctx);
}
JSValueRef forwardMonth(JSContextRef ctx, JSObjectRef function,
                        JSObjectRef thisObject, size_t argumentCount,
                        const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// stopTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.skipTime(0, 1, 0);
  return JSValueMakeNull(ctx);
}
JSValueRef forwardYear(JSContextRef ctx, JSObjectRef function,
                       JSObjectRef thisObject, size_t argumentCount,
                       const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// stopTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.skipTime(0, 0, 1);
  return JSValueMakeNull(ctx);
}
JSValueRef forwardDecade(JSContextRef ctx, JSObjectRef function,
                         JSObjectRef thisObject, size_t argumentCount,
                         const JSValueRef arguments[], JSValueRef *exception)
{
  ///
  /// stopTimer is a javascript function, when called will perform the following c++ operations
  ///
  calendar.skipTime(0, 0, 10);
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

  /* Below is the C++ side of a javascript function, all C++ additions are in the function JSValueRef startTimer() **/

  // Acquire the JS execution context for the current page.
  auto scoped_context = caller->LockJSContext();
  // Typecast to the underlying JSContextRef.
  JSContextRef ctx = (*scoped_context);
  // Create a JavaScript String containing the name of our callback.
  JSStringRef startTimerRef = JSStringCreateWithUTF8CString("startTimer");
  JSStringRef stopTimerRef = JSStringCreateWithUTF8CString("stopTimer");
  JSStringRef forwardWeekRef = JSStringCreateWithUTF8CString("forwardWeek");
  JSStringRef forwardMonthRef = JSStringCreateWithUTF8CString("forwardMonth");
  JSStringRef forwardYearRef = JSStringCreateWithUTF8CString("forwardYear");
  JSStringRef forwardDecadeRef = JSStringCreateWithUTF8CString("forwardDecade");
  // Create a garbage-collected JavaScript function that is bound to our native C callback 'startTimer()'.
  JSObjectRef startTimerFunc = JSObjectMakeFunctionWithCallback(ctx, startTimerRef, startTimer);
  JSObjectRef stopTimerFunc = JSObjectMakeFunctionWithCallback(ctx, stopTimerRef, stopTimer);
  JSObjectRef forwardWeekFunc = JSObjectMakeFunctionWithCallback(ctx, forwardWeekRef, forwardWeek);
  JSObjectRef forwardMonthFunc = JSObjectMakeFunctionWithCallback(ctx, forwardMonthRef, forwardMonth);
  JSObjectRef forwardYearFunc = JSObjectMakeFunctionWithCallback(ctx, forwardYearRef, forwardYear);
  JSObjectRef forwardDecadeFunc = JSObjectMakeFunctionWithCallback(ctx, forwardDecadeRef, forwardDecade);

  // Get the global JavaScript object (aka 'window')
  JSObjectRef globalObj = JSContextGetGlobalObject(ctx);
  // Store our function in the page's global JavaScript object so that it accessible from the page as 'startTimer()'.
  JSObjectSetProperty(ctx, globalObj, startTimerRef, startTimerFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, stopTimerRef, stopTimerFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, forwardWeekRef, forwardWeekFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, forwardMonthRef, forwardMonthFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, forwardYearRef, forwardYearFunc, 0, 0);
  JSObjectSetProperty(ctx, globalObj, forwardDecadeRef, forwardDecadeFunc, 0, 0);
  // Release the JavaScript String we created earlier.
  JSStringRelease(startTimerRef);
  JSStringRelease(stopTimerRef);
  JSStringRelease(forwardWeekRef);
  JSStringRelease(forwardMonthRef);
  JSStringRelease(forwardYearRef);
  JSStringRelease(forwardDecadeRef);

  /* USED TO POPULATE THE DROP DOWN WITH STOCKS LOADED IN FROM CSV INTO STOCK OBJECTS **/
  caller->EvaluateScript("showStockInfo('$1000000', '48964')"); // will be changed so that once a stock is selected, their current price is displayed

  // std::string filename = absPath + "src/data/scraping/nasdaq_etf_screener_1691614852999.csv"; // FOR ALL???
  std::string filename = "../../../../src/data/scraping/nasdaq_etf_screener_1691614852999.csv"; // FOR MAC
  // std::string filename = "src/data/scraping/nasdaq_etf_screener_1691614852999.csv";  // FOR WINDOWS
  std::vector<Stock> stocks = parseCSV(filename);
  if (!stocks.empty())
  {
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
