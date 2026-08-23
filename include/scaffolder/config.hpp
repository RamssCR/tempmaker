#pragma once
#include <string>

namespace TempMaker {
    struct Stack {
        std::string library{};
        std::string framework{};
        bool has_scaffolder_cli{};
    };

    struct TemplateConfig {
        std::string name{};
        std::string type{};
        std::string package_manager{};
        Stack stack{};
        bool git{};
    };
}