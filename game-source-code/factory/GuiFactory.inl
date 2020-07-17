#include "GuiFactory.h"
#include "gui/control/Button.h"
#include "gui/control/TextBlock.h"
#include "gui/layout/DockPanel.h"
#include "gui/layout/StackPanel.h"
#include "gui/layout/Canvas.h"
#include <utility>

//The functions below can be made into a single function, they only separate
//for convenience

template<class T, typename... Args>
std::unique_ptr<Gui::UIElement> GuiFactory::getUIElement(Args&&... args) const {
    return std::move(instantiate<T>(std::forward<Args>(args)...));
}

template<class T, typename ... Args>
std::unique_ptr<Gui::Panel> GuiFactory::getPanel(Args&&... args) const{
    return std::move(instantiate<T>(std::forward<Args>(args)...));
}

template<class T, typename... Args>
std::unique_ptr<T> GuiFactory::instantiate(Args&&... args) const{
    return std::make_unique<T>(std::forward<Args>(args)...);
}
