#include "scaffolder/utils/package_manager.hpp"
#include <array>

namespace TempMaker::SystemUtils {
    std::vector<std::string_view> check_package_managers(const IEnvironmentChecker& checker) {
        static constexpr std::array<std::string_view, 5> pkg_managers{"npm", "yarn", "pnpm", "deno", "bun"};
        std::vector<std::string_view> available_pkg_managers{};
        available_pkg_managers.reserve(pkg_managers.size());

        for (const auto manager : pkg_managers) {
            const auto path{checker.find_executable(manager)};
            if (!path.empty()) available_pkg_managers.emplace_back(manager);
        }

        return available_pkg_managers;
    }
}
