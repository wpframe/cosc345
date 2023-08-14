#include "MyApp.h"
#include "Stock.h"
#include <iostream>
#include <vector>
#include <string>
// #include <unistd.h>    // NEED THIS FOR THE findPathFromApp METHOD BUT DOES NOT BUILD ON WINDOWS

#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000

std::string findPathFromApp()
{

  // char buffer[PATH_MAX]; // PATH_MAX is a macro representing the maximum path length
  // if (getcwd(buffer, sizeof(buffer)) == nullptr)
  // {
  //   std::cout << "Could not find current directory: " << std::endl;
  //   return "";
  // }
  std::string buffer = "/Users/admin/Desktop/cosc345/cosc345/build/MyApp.app/Contents/MacOS/MyApp";

  // std::__fs::filesystem::path currentPath = std::__fs::filesystem::current_path(); // NEED TO UPDATE COMPILER TO USE THIS
  std::string modifiedPath = buffer;

  size_t pos = modifiedPath.rfind("build");

  if (pos != std::string::npos)
  {
    modifiedPath.erase(pos);
  }

  return modifiedPath;
}

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
  overlay_->view()->LoadURL("file:///app.html");

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
  /// This is called repeatedly from the application's update loop.
  ///
  /// You should update any app logic here.
  ///
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

void MyApp::OnDOMReady(ultralight::View *caller,
                       uint64_t frame_id,
                       bool is_main_frame,
                       const String &url)
{

  caller->EvaluateScript("showStockInfo('$1000000', '48964')");
  // std::string absPath = findPathFromApp();
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
    std::cout << "No stocks found in the CSV." << std::endl;
  }
  //  This is called when a frame's DOM has finished loading on the page. /
  //  This is the best time to setup any JavaScript bindings./
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
