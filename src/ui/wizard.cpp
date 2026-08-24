#include "scaffolder/ui/wizard.hpp"
#include "scaffolder/config.hpp"
#include "scaffolder/ui/components/input_name.hpp"
#include "scaffolder/ui/components/radio_category.hpp"
#include <ftxui/component/app.hpp>

namespace TempMaker::UI {
    using namespace ftxui;

    void start_wizard() {
        TemplateConfig config{};
        int step{0};

        auto input{input_name(config.name, step)};
        auto radio{radio_category(config.category, step)};

        auto screen{App::TerminalOutput()};
        auto container{Container::Tab({ input, radio }, &step)};

        screen.Loop(container);
    }
}
