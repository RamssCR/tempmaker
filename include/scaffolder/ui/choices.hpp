#pragma once
#include "scaffolder/config.hpp"
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace TempMaker::UI {
    struct StackOption {
        std::string name{};
        bool has_scaffolder{};
    };

    using StackTree = std::unordered_map<Category, std::unordered_map<std::string, std::vector<StackOption>>>;

    inline const StackTree stack_tree {
        { Frontend, {
            {"react", {{"Next.js", true}, {"Vite.js", true}}},
            {"svelte", {{"SvelteKit", true}, {"Vite.js", true}}},
        }},
        { Backend, {
            {"express", {{"Vanilla", false}}},
            {"fastify", {{"Vanilla", false}}},
        }}
    };
}