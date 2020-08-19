template<class T, typename... Args>
std::unique_ptr<Gui::UIElement> GuiFactory::getUIElement(Args &&... args) const {
    return std::move(instantiate<T>(std::forward<Args>(args)...));
}

template<class T, typename ... Args>
std::unique_ptr<Gui::Panel> GuiFactory::getPanel(Args &&... args) const {
    return std::move(instantiate<T>(std::forward<Args>(args)...));
}

template<class T, typename... Args>
std::unique_ptr<T> GuiFactory::instantiate(Args &&... args) const {
    return std::make_unique<T>(std::forward<Args>(args)...);
}
