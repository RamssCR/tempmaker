#include "scaffolder/ui/wizard.hpp"
#include "scaffolder/ui/choices.hpp"
#include "scaffolder/config.hpp"
#include "scaffolder/ui/input.hpp"
#include "scaffolder/ui/radio.hpp"
#include <format>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

namespace TempMaker::UI {
    using namespace ftxui;

    void start_wizard() {
        TemplateConfig config{};
        WizardState state{};
        SelectionTree tree{};

        std::vector<std::string> current_libraries{};
        std::vector<std::string> current_variants{};

        auto screen{ScreenInteractive::TerminalOutput()};

        auto input{inputName(state, config)};
        auto radio_category{radioCategory(state, config, tree, current_libraries)};
        auto radio_library{radioLibrary(state, config, tree, current_libraries, current_variants)};
        auto radio_variant{radioVariant(state, config, tree, current_variants)};
        auto radio_package_manager{radioPkgManager(state, config)};
        auto radio_git{radioGit(config)};

        auto container{Container::Tab({
            input,
            radio_category,
            radio_library,
            radio_variant,
            radio_package_manager,
            radio_git
        }, &state.current_step)};

        auto renderer{Renderer(container, [&] {
            Element current_element{};

            switch (state.current_step) {
                case 0:
                    current_element = vbox({
                        text(" Enter your Project Name: ") | bold,
                        input->Render()
                    });
                    break;
                case 1:
                    current_element = vbox({
                        text(" Select Category: ") | bold,
                        radio_category->Render()
                    });
                    break;
                case 2:
                    current_element = vbox({
                        text(std::format(" Category: {}", config.category)) | dim,
                        text(" Select Library: ") | bold,
                        radio_library->Render()
                    });
                    break;
                case 3:
                    current_element = vbox({
                        text(std::format(" Category: {} > {}", config.category, config.stack.library)) | dim,
                        text(" Select Target Framework/Variant: ") | bold,
                        radio_variant->Render()
                    });
                    break;
                case 4:
                    current_element = vbox({
                        text(std::format(
                            " Category: {} > {} > {}",
                            config.category,
                            config.stack.library,
                            config.stack.framework
                            )
                        ) | dim,
                        text(" Select Package Manager: ") | bold,
                        radio_package_manager->Render()
                    });
                    break;
                case 5:
                    current_element = vbox({
                        text(std::format(
                            " Category: {} > {} > {} > {}",
                            config.category,
                            config.stack.library,
                            config.stack.framework,
                            config.package_manager
                            )
                        ) | dim,
                        text(" Initialize Git? ") | bold,
                        radio_git->Render()
                    });
                    break;
                default:
                    current_element = text("???");
                    break;
            }

            return vbox({
                text(" CLI Scaffolder Wizard ") | center | bold,
                separator(),
                current_element | flex
            }) | border | size(WIDTH, GREATER_THAN, 50);
        })};

        screen.Loop(renderer);
    }
}
