#pragma once
#include <ftxui/component/component.hpp>
#include <string>

namespace TempMaker::UI {
    using namespace ftxui;

    Component input(std::string& name, int& step);
}