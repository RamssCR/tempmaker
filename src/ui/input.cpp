#include "scaffolder/ui/input.hpp"

namespace TempMaker::UI {
    using namespace ftxui;

    Component inputName(WizardState& state, TemplateConfig& config) {
        InputOption input_options{};
        input_options.on_enter = [&] { state.current_step = 1; };

        return Input(&config.name, "my-app", input_options);
    }
}