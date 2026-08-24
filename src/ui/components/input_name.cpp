#include "scaffolder/ui/components/input_name.hpp"
#include "ftxui/component/event.hpp"

namespace TempMaker::UI {
    using namespace ftxui;

    Component input_name(std::string& name, int& step) {
        InputOption input_option{};
        input_option.on_enter = [&step]{ ++step; };

        auto input{Input(&name, "my-app", input_option)};

        return input |= CatchEvent([&](const Event& event) {
            return event.is_character() && static_cast<unsigned char>(std::isspace(event.character()[0]));
        });
    }
}
