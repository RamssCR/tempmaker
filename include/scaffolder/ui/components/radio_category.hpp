#pragma once
#include "scaffolder/config.hpp"
#include <ftxui/component/component.hpp>

namespace TempMaker::UI {
    using namespace ftxui;

    Component radio_category(Category& category, int& step);
}