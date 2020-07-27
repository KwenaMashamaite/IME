#include "IME/factory/GuiFactory.h"
#include "IME/gui/control/UIElement.h"
#include "IME/gui/layout/Panel.h"
#include "IME/gui/control/Button.h"
#include "IME/gui/control/TextBlock.h"
#include "IME/gui/layout/DockPanel.h"
#include "IME/gui/layout/StackPanel.h"
#include "IME/gui/layout/Canvas.h"
#include <utility>

namespace IME {
    template<class T, typename... Args>
    std::unique_ptr<Gui::UIElement> GuiFactory::getUIElement(Args&&... args) const {
        return std::move(instantiate<T>(std::forward<Args>(args)...));
    }

    template<class T, typename ... Args>
    std::unique_ptr<Gui::Panel> GuiFactory::getPanel(Args&&... args) const {
        return std::move(instantiate<T>(std::forward<Args>(args)...));
    }

    template<class T, typename... Args>
    std::unique_ptr<T> GuiFactory::instantiate(Args&&... args) const {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
}
