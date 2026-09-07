#include "scaffolder/ui/radio.hpp"
#include "scaffolder/utils/package_manager.hpp"
#include <array>
#include <ftxui/component/event.hpp>

namespace TempMaker::UI {
    using namespace ftxui;

    Component radioCategory(
        WizardState &state,
        TemplateConfig &config,
        SelectionTree& tree,
        std::vector<std::string>& current_libraries
    ) {
        RadioboxOption radio_category_options{};
        radio_category_options.on_change = [&] {
            config.category = tree.categories[state.category_idx];
            current_libraries = tree.libraries[config.category];
        };
        return Radiobox(&tree.categories, &state.category_idx, radio_category_options)
            | CatchEvent([&](const Event& event) {
                if (event == Event::Return) {
                    config.category = tree.categories[state.category_idx];
                    current_libraries = tree.libraries[config.category];
                    state.current_step = 2;

                    return true;
                }

                return false;
            });
    }

    Component radioLibrary(
        WizardState& state,
        TemplateConfig& config,
        SelectionTree& tree,
        const std::vector<std::string>& current_libraries,
        std::vector<std::string>& current_variants
    ) {
        RadioboxOption radio_library_options{};
        radio_library_options.on_change = [&] {
            config.stack.library = current_libraries[state.library_idx];
            current_variants = tree.variants[config.stack.library];
            state.variant_idx = 0;
        };
        return Radiobox(&current_libraries, &state.library_idx, radio_library_options)
            | CatchEvent([&](const Event& event) {
                if (event == Event::Return) {
                    config.stack.library = current_libraries[state.library_idx];
                    current_variants = tree.variants[config.stack.library];
                    state.variant_idx = 0;

                    state.current_step = 3;

                    return true;
                }

                return false;
            });
    }

    Component radioVariant(
        WizardState &state,
        TemplateConfig &config,
        SelectionTree& tree,
        const std::vector<std::string>& current_variants
    ) {
        RadioboxOption radio_variant_options{};
        radio_variant_options.on_change = [&] {
            config.stack.framework = current_variants[state.variant_idx];
            config.stack.has_scaffolder = tree.framework[config.stack.framework];
        };
        return Radiobox(&current_variants, &state.variant_idx, radio_variant_options)
            | CatchEvent([&](const Event& event) {
                if (event == Event::Return) {
                    config.stack.framework = current_variants[state.variant_idx];
                    config.stack.has_scaffolder = tree.framework[config.stack.framework];

                    state.current_step = 4;
                    return true;
                }

                return false;
            });
    }

    Component radioPkgManager(WizardState &state, TemplateConfig &config) {
        const SystemUtils::BoostEnvironmentChecker checker{};
        const auto managers{SystemUtils::check_package_managers(checker)};

        RadioboxOption package_manager_options{};
        package_manager_options.on_change = [&] {
            config.package_manager = managers[state.package_idx];
        };
        return Radiobox(&managers, &state.package_idx, package_manager_options)
            | CatchEvent([&](const Event& event) {
                if (event == Event::Return) {
                    config.package_manager = managers[state.package_idx];
                    state.current_step = 5;

                    return true;
                }

                return false;
            });
    }

    Component radioGit(TemplateConfig &config) {
        const std::vector<std::string_view> choice{"Yes", "No"};
        int index{0};

        RadioboxOption radio_git_options{};
        radio_git_options.on_change = [&] { config.git = index == 0; };

        return Radiobox(&choice, &index, radio_git_options)
            | CatchEvent([&](const Event& event) {
                if (event == Event::Return) {
                    config.git = index == 0;

                    return true;
                }

                return false;
            });
    }
}
