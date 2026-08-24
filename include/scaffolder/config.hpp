#pragma once
#include <string>
#include <string_view>

namespace TempMaker {
    enum Category {
        Frontend,
        Backend,
    };

    struct Stack {
        std::string library{};
        std::string framework{};
        bool has_scaffolder{};
    };

    struct TemplateConfig {
        std::string name{};
        Category category{};
        std::string package_manager{};
        Stack stack{};
        bool git{};
    };
}