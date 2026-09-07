#pragma once
#include "scaffolder/ui/choices.hpp"
#include <ftxui/component/component.hpp>

namespace TempMaker::UI {
    using namespace ftxui;

    Component radioCategory(
        WizardState& state,
        TemplateConfig& config,
        SelectionTree& tree,
        std::vector<std::string>& current_libraries
    );

    Component radioLibrary(
        WizardState& state,
        TemplateConfig& config,
        SelectionTree& tree,
        const std::vector<std::string>& current_libraries,
        std::vector<std::string>& current_variants
    );

    Component radioVariant(
        WizardState& state,
        TemplateConfig& config,
        SelectionTree& tree,
        const std::vector<std::string>& current_variants
    );

    Component radioPkgManager(WizardState& state, TemplateConfig& config);

    Component radioGit(TemplateConfig& config);
}