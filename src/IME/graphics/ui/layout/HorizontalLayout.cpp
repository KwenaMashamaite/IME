#include "IME/graphics/ui/layout/HorizontalLayout.h"
#include <cassert>

namespace IME::Graphics::UI {
    HorizontalLayout::HorizontalLayout(float width, float height)
        : layout_{tgui::HorizontalLayout::create({width, height})},
          renderer_{std::make_shared<BoxLayoutRenderer>()}
        {
            renderer_->setInternalPtr(layout_->getRenderer());
        }

        void HorizontalLayout::setRenderer(std::shared_ptr<BoxLayoutRenderer> renderer) {
            assert(renderer && "A nullptr cannot be set as a renderer");
            renderer_ = renderer;
            layout_->setRenderer(renderer->getInternalPtr()->getData());
        }

        std::shared_ptr<BoxLayoutRenderer> HorizontalLayout::getRenderer() {
            return renderer_;
        }

    void HorizontalLayout::setTextSize(unsigned int charSize) {
        layout_->setTextSize(charSize);
    }

    void HorizontalLayout::setText(const std::string &content) {

    }

    void HorizontalLayout::setSize(float width, float height) {
        layout_->setSize({width, height});
    }

    Dimensions HorizontalLayout::getSize() const {
        return {layout_->getSize().x, layout_->getSize().y};
    }

    Dimensions HorizontalLayout::getAbsoluteSize() {
        return {layout_->getFullSize().x, layout_->getFullSize().y};
    }

    std::string HorizontalLayout::getText() const {
        return "";
    }

    unsigned int HorizontalLayout::getTextSize() const {
        return layout_->getTextSize();
    }

    std::string HorizontalLayout::getType() const {
        return "HorizontalLayout";
    }

    void HorizontalLayout::toggleVisibility() {
        if (isHidden())
            show();
        else
            hide();
    }

    bool HorizontalLayout::contains(float x, float y) const {
        return layout_->isMouseOnWidget({x, y});
    }

    void HorizontalLayout::hide() {
        layout_->hideWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    void HorizontalLayout::show() {
        layout_->showWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    bool HorizontalLayout::isHidden() const {
        return !layout_->isVisible();
    }

    void HorizontalLayout::setPosition(float x, float y) {
        layout_->setPosition({x, y});
    }

    void HorizontalLayout::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void HorizontalLayout::setRotation(float angle) {
        layout_->setRotation(angle);
    }

    void HorizontalLayout::setScale(float factorX, float factorY) {
        layout_->setScale({factorX, factorY});
    }

    void HorizontalLayout::setOrigin(float x, float y) {
        layout_->setOrigin({x, y});
    }

    Position HorizontalLayout::getPosition() const {
        return {layout_->getPosition().x, layout_->getPosition().y};
    }

    Position HorizontalLayout::getOrigin() const {
        return {layout_->getOrigin().x, layout_->getOrigin().y};
    }

    float HorizontalLayout::getRotation() const {
        return layout_->getRotation();
    }

    void HorizontalLayout::move(float offsetX, float offsetY) {
        layout_->setPosition(getPosition().x + offsetX,
             getPosition().y + offsetY);
    }

    void HorizontalLayout::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void HorizontalLayout::scale(float factorX, float factorY) {
        setScale(layout_->getScale().x + factorX, layout_->getScale().y + factorY);
    }

    void HorizontalLayout::insertWidget(std::size_t index,
        std::shared_ptr<IWidget> widget, const std::string &widgetName)
    {
        layout_->insert(index, widget->getInternalPtr(), widgetName);
    }

    bool HorizontalLayout::removeWidgetAt(std::size_t index) {
        return layout_->remove(index);
    }

    std::shared_ptr<IWidget>
    HorizontalLayout::getWidgetAt(std::size_t index) const {
        return std::shared_ptr<IWidget>();
    }

    void HorizontalLayout::addSpace(float ratio) {
       layout_->addSpace(ratio);
    }

    void HorizontalLayout::insertSpace(std::size_t index, float ratio) {
        layout_->insertSpace(index, ratio);
    }

    bool HorizontalLayout::setRatio(std::shared_ptr<IWidget> widget, float ratio) {
        return layout_->setRatio(widget->getInternalPtr(), ratio);
    }

    bool HorizontalLayout::setRatio(std::size_t index, float ratio) {
        return layout_->setRatio(index, ratio);
    }

    float HorizontalLayout::getRatio(std::shared_ptr<IWidget> widget) const {
        return layout_->getRatio(widget->getInternalPtr());
    }

    float HorizontalLayout::getRatio(std::size_t index) const {
        return layout_->getRatio(index);
    }

    void HorizontalLayout::addWidget(const std::shared_ptr<UI::IWidget> widgetPtr,
    const std::string &widgetName) {
        layout_->add(widgetPtr->getInternalPtr(), widgetName);
    }

    std::shared_ptr<IWidget>
    HorizontalLayout::getWidget(const std::string &widgetName) const {
        return std::shared_ptr<IWidget>();
    }

    const std::vector<IWidget> &HorizontalLayout::getWidgets() const {

    }

    bool HorizontalLayout::removeWidget(std::shared_ptr<UI::IWidget> widget) {
        return false;
    }

    void HorizontalLayout::removeAllWidgets() {
        layout_->removeAllWidgets();
    }

    void HorizontalLayout::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToFront(widget->getInternalPtr());
    }

    void HorizontalLayout::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t HorizontalLayout::moveWidgetForward(std::shared_ptr<UI::IWidget> widget) {
        return layout_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t
    HorizontalLayout::moveWidgetBackward(std::shared_ptr<UI::IWidget> widget) {
        return layout_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<UI::IWidget> HorizontalLayout::getFocusedWidget() const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget> HorizontalLayout::getFocusedLeaf() const {
        return std::shared_ptr<UI::IWidget>();
    }

    std::shared_ptr<UI::IWidget>
    HorizontalLayout::getWidgetAtPosition(Position pos) const {
        return std::shared_ptr<UI::IWidget>();
    }

    bool HorizontalLayout::focusNextWidget(bool recursive) {
        return layout_->focusNextWidget(recursive);
    }

    bool HorizontalLayout::focusPreviousWidget(bool recursive) {
        return layout_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> HorizontalLayout::getInternalPtr() {
        return layout_;
    }
}