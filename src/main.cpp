#include "MyApp.h"
#include <iostream>
#include <filesystem>
#include <string>

int main()
{
  std::__fs::filesystem::path currentPath = std::__fs::filesystem::current_path();
  std::cout << "Current directory: " << currentPath << std::endl;

  std::string path = currentPath;

  size_t pos = path.rfind("build");

  if (pos != std::string::npos)
  {
    // Erase everything after the found position
    path.erase(pos); // +7 to include "cosc345"

    std::cout << "Modified path: " << path << std::endl;
  }
  else
  {
    std::cerr << "Substring not found in the path." << std::endl;
  }

  MyApp app;
  app.Run();

  return 0;
}
