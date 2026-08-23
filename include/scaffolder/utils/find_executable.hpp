#pragma once
#include <string_view>
#include <boost/process/environment.hpp>

namespace TempMaker::SystemUtils {
    class IEnvironmentChecker {
    public:
        virtual ~IEnvironmentChecker() = default;
        [[nodiscard]] virtual boost::filesystem::path find_executable(std::string_view name) const = 0;
    };

    class BoostEnvironmentChecker : public IEnvironmentChecker {
    public:
        [[nodiscard]] boost::filesystem::path find_executable(std::string_view name) const override {
            return boost::process::v2::environment::find_executable(name);
        }
    };
}