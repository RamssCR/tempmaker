#include "scaffolder/ui/components/radio_category.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <vector>
#include <string_view>
#include <iostream>

namespace TempMaker::UI {
    using namespace ftxui;

    Component radio_category(Category& category, int& step) {
        const std::vector<std::string_view> categories{"Frontend", "Backend"};
        int selected{0};

        RadioboxOption options{};
        options.on_change = [&step] { ++step; };

        auto radio{Radiobox(&categories, &selected, options)};
        category = static_cast<Category>(selected);

        std::cout << selected << '\n';

        return radio;
    }
}