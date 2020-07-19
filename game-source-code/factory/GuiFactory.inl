#include "GuiFactory.h"
#include "gui/control/UIElement.h"
#include "gui/layout/Panel.h"
#include "gui/control/Button.h"
#include "gui/control/TextBlock.h"
#include "gui/layout/DockPanel.h"
#include "gui/layout/StackPanel.h"
#include "gui/layout/Canvas.h"
#include <utility>
#include <cassert>
#include <type_traits>

//The functions below can be made into a single function, they only separate
//for convenience

namespace IME {
    template<class T, typename... Args>
    std::unique_ptr<T> GuiFactory::getUIElement(Args &&... args) const {
        static_assert(std::is_base_of_v<Gui::UIElement, T>, "class T is not derived from Gui::UIElement");
        return std::move(instantiate<T>(std::forward<Args>(args)...));
    }

    template<class T, typename ... Args>
    std::unique_ptr<T> GuiFactory::getPanel(Args &&... args) const {
        static_assert(std::is_base_of_v<Gui::Panel, T>, "class T is not derived from Gui::Panel");
        return std::move(instantiate<T>(std::forward<Args>(args)...));
    }

    template<class T, typename... Args>
    std::unique_ptr<T> GuiFactory::instantiate(Args &&... args) const {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}
