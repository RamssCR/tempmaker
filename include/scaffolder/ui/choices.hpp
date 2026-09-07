#pragma once
#include "scaffolder/config.hpp"
#include <array>
#include <map>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace TempMaker::UI {
    struct StackOption {
        std::string name{};
        bool has_scaffolder{};
    };

    struct WizardState {
        int current_step{0};
        int category_idx{0};
        int library_idx{0};
        int variant_idx{0};
        int package_idx{0};
    };

    // Tree Structure: Category -> Library -> Variants
    struct SelectionTree {
        std::vector<std::string> categories{"Frontend", "Backend"};

        std::unordered_map<std::string_view, std::vector<std::string>> libraries{
            {"Frontend", {"React", "Svelte"}},
            {"Backend",  {"Express", "Fastify"}}
        };

        std::unordered_map<std::string, std::vector<std::string>> variants{
            {"React",   {"Vite", "Next.js"}},
            {"Svelte",  {"Vite", "SvelteKit"}},
            {"Express", {"Vanilla"}},
            {"Fastify", {"Vanilla"}}
        };

        std::map<std::string_view, bool> framework{
            {"Next.js", true},
            {"Vite", true},
            {"SvelteKit", true},
            {"Vanilla", false}
        };
    };
}