#include "PathUtil.h"

/*!
  @brief Method which finds the relative path from app to the src directory.
  @details checks what operating system a user is on and defines a relative path prefix.
  @return the path prefix.

**/

std::string PathUtil::findPathFromApp()
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
