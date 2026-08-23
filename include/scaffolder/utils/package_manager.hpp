#pragma once
#include "find_executable.hpp"
#include <vector>
#include <string_view>

namespace TempMaker::SystemUtils {
    std::vector<std::string_view> check_package_managers(const IEnvironmentChecker& checker);
}
