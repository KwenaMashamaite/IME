#include "IME/graphics/ui/layout/ChildWindow.h"

namespace IME::Graphics::UI {
    ChildWindow::ChildWindow(const std::string &title, unsigned int titleButtons)
        : window_{tgui::ChildWindow::create(title, titleButtons)}
    {}

    void ChildWindow::setClientSize(Dimensions size) {

    }

    Dimensions ChildWindow::getClientSize() const {
        return Dimensions();
    }

    void ChildWindow::setMaximumSize(Dimensions size) {

    }

    Dimensions ChildWindow::getMaximumSize() const {
        return Dimensions();
    }

    void ChildWindow::setMinimumSize(Dimensions size) {

    }

    Dimensions ChildWindow::getMinimumSize() const {
        return Dimensions();
    }

    void ChildWindow::setTitle(const std::string &title) {
        window_->setTitle(title);
    }

    std::string ChildWindow::getTitle() const {
        return window_->getTitle().toAnsiString();
    }

    void ChildWindow::setTitleTextSize(unsigned int size) {
        window_->setTitleTextSize(size);
    }

    unsigned int ChildWindow::getTitleTextSize() const {
        return window_->getTitleTextSize();
    }

    void ChildWindow::setTitleAlignment(ChildWindow::TitleAlignment alignment) {
        window_->setTitleAlignment(static_cast<tgui::ChildWindow::TitleAlignment>(alignment));
    }

    ChildWindow::TitleAlignment ChildWindow::getTitleAlignment() const {
        return static_cast<TitleAlignment>(window_->getTitleAlignment());
    }

    void ChildWindow::setTitleButtons(unsigned int buttons) {
        window_->setTitleButtons(buttons);
    }

    void ChildWindow::close() {
        window_->close();
    }

    void ChildWindow::destroy() {
        window_->destroy();
    }

    void ChildWindow::setResizable(bool resizable) {
        window_->setResizable(resizable);
    }

    bool ChildWindow::isResizable() const {
        return window_->isResizable();
    }

    void ChildWindow::setDraggable(bool draggable) {
        window_->setPositionLocked(draggable);
    }

    bool ChildWindow::isDraggable() const {
        return window_->isPositionLocked();
    }

    void ChildWindow::setKeepInParent(bool enabled) {
        window_->setKeepInParent(enabled);
    }

    bool ChildWindow::isKeptInParent() const {
        return window_->isKeptInParent();
    }

    void ChildWindow::setTextSize(unsigned int charSize) {
        window_->setTextSize(charSize);
    }

    void ChildWindow::setText(const std::string &content) {

    }

    void ChildWindow::setSize(float width, float height) {
        window_->setSize({width, height});
    }

    Dimensions ChildWindow::getSize() const {
        return {window_->getSize().x, window_->getSize().y};
    }

    Dimensions ChildWindow::getAbsoluteSize() {
        return {window_->getFullSize().x, window_->getFullSize().y};
    }

    std::string ChildWindow::getText() const {
        return "";
    }

    unsigned int ChildWindow::getTextSize() const {
        return window_->getTextSize();
    }

    std::string ChildWindow::getType() const {
        return "ChildWindow";
    }

    void ChildWindow::toggleVisibility() {
        if (isHidden())
            show();
        else
            hide();
    }

    bool ChildWindow::contains(float x, float y) const {
        return window_->isMouseOnWidget({x, y});
    }

    void ChildWindow::hide() {
        window_->hideWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    void ChildWindow::show() {
        window_->showWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    bool ChildWindow::isHidden() const {
        return !window_->isVisible();
    }

    void ChildWindow::setPosition(float x, float y) {
        window_->setPosition({x, y});
    }

    void ChildWindow::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void ChildWindow::setRotation(float angle) {
        window_->setRotation(angle);
    }

    void ChildWindow::setScale(float factorX, float factorY) {
        window_->setScale({factorX, factorY});
    }

    void ChildWindow::setOrigin(float x, float y) {
        window_->setOrigin({x, y});
    }

    Position ChildWindow::getPosition() const {
        return {window_->getPosition().x, window_->getPosition().y};
    }

    Position ChildWindow::getOrigin() const {
        return {window_->getOrigin().x, window_->getOrigin().y};
    }

    float ChildWindow::getRotation() const {
        return window_->getRotation();
    }

    void ChildWindow::move(float offsetX, float offsetY) {
        window_->setPosition(getPosition().x + offsetX,
                             getPosition().y + offsetY);
    }

    void ChildWindow::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void ChildWindow::scale(float factorX, float factorY) {
        setScale(window_->getScale().x + factorX, window_->getScale().y + factorY);
    }

    void ChildWindow::addWidget(const std::shared_ptr<IWidget> widgetPtr,
        const std::string &widgetName)
    {
        window_->add(widgetPtr->getInternalPtr(), widgetName);
    }

    std::shared_ptr<IWidget>
    ChildWindow::getWidget(const std::string &widgetName) const {
        return std::shared_ptr<IWidget>();
    }

    const std::vector<IWidget> &ChildWindow::getWidgets() const {

    }

    bool ChildWindow::removeWidget(std::shared_ptr<IWidget> widget) {
        return false;
    }

    void ChildWindow::removeAllWidgets() {
        window_->removeAllWidgets();
    }

    void ChildWindow::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
        window_->moveWidgetToFront(widget->getInternalPtr());
    }

    void ChildWindow::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
        window_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t ChildWindow::moveWidgetForward(std::shared_ptr<IWidget> widget) {
        return window_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t
    ChildWindow::moveWidgetBackward(std::shared_ptr<IWidget> widget) {
        return window_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<IWidget> ChildWindow::getFocusedWidget() const {
        return std::shared_ptr<IWidget>();
    }

    std::shared_ptr<IWidget> ChildWindow::getFocusedLeaf() const {
        return std::shared_ptr<IWidget>();
    }

    std::shared_ptr<IWidget>
    ChildWindow::getWidgetAtPosition(Position pos) const {
        return std::shared_ptr<IWidget>();
    }

    bool ChildWindow::focusNextWidget(bool recursive) {
        return window_->focusNextWidget(recursive);
    }

    bool ChildWindow::focusPreviousWidget(bool recursive) {
        return window_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> ChildWindow::getInternalPtr() {
        return window_;
    }
}