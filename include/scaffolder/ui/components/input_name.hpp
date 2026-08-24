#pragma once
#include <ftxui/component/component.hpp>
#include <string>

namespace TempMaker::UI {
    ftxui::Component input_name(std::string& name, int& step);
}