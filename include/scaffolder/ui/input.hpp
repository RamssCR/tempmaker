#pragma once
#include "scaffolder/ui/choices.hpp"
#include <ftxui/component/component.hpp>

namespace TempMaker::UI {
    using namespace ftxui;

    Component inputName(WizardState& state, TemplateConfig& config);
}