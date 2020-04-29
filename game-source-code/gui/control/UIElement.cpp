#include "UIElement.h"
#include "resources/ResourceManager.h"
#include "utility/Utility.h"
#include <algorithm>

Gui::UIElement::UIElement()
    : numOfLinesInText_{0u}, isHidden_(false)
{
    initialize();
}

Gui::UIElement::UIElement(const std::string &textContent)
    : numOfLinesInText_{0u}, isHidden_(false)
{
    setText(textContent);
    initialize();
}

void Gui::UIElement::initialize() {
    auto defaultTextFont = "philosopher.ttf";
    auto defaultTextCharSize = 30u;

    initEvents();
    setTextFont(defaultTextFont);
    setTextCharSize(defaultTextCharSize);
    setPadding(0.0f);
    setMargin(0.0f);

    outline_.setFillColor(sf::Color::Transparent);
    border_.setFillColor(sf::Color::White);
    text_.setFillColor(sf::Color::Black);
}

void Gui::UIElement::initEvents() {
    addListener("textChanged", Callback<std::string>([this](const std::string &content) {
        if (content.empty()) {
            numOfLinesInText_ = 0;
            return;
        }
        numOfLinesInText_ = std::count(content.begin(), content.end(), '\n');
        numOfLinesInText_++; //Account for one line/last line (both dont have '\n')
        resize();
    }));

    addListener("charSizeChanged", Callback<>([this](){
        resize();
    }));

    addListener("dimensionsChanged", Callback<>([this](){
        resize();
        setPosition(getPosition().x, getPosition().y);
    }));
}

void Gui::UIElement::setPosition(float x, float y) {
    outline_.setPosition(x, y);
    border_.setPosition(
        outline_.getPosition().x + margin_.left,
        outline_.getPosition().y + margin_.top
    );
    text_.setPosition(
        border_.getPosition().x + padding_.left,
        border_.getPosition().y + padding_.top
	);
}

void Gui::UIElement::setMargin(float margin) {
    margin_ = {margin, margin, margin, margin};
    emit("dimensionsChanged");
}

void Gui::UIElement::setPadding(float padding) {
    padding_ = {padding, padding, padding, padding};
    emit("dimensionsChanged");
}

void Gui::UIElement::setMargin(const Gui::Margin &margin) {
    margin_ = margin;
    emit("dimensionsChanged");
}

void Gui::UIElement::setPadding(const Gui::Padding &padding) {
    padding_ = padding;
    emit("dimensionsChanged");
}

void Gui::UIElement::setFillColour(Gui::Colour fillColour) {
    border_.setFillColor(Utility::convertOwnColourToSFMLColour(fillColour));
}

void Gui::UIElement::setTextFont(const std::string &contentFont) {
    text_.setFont(ResourceManager::getFont(contentFont));
}

void Gui::UIElement::setTextCharSize(unsigned int charSize) {
    text_.setCharacterSize(charSize);
    emit("charSizeChanged");
}

void Gui::UIElement::setText(const std::string &content) {
    text_.setString(content);
    emit("textChanged", content);
}

void Gui::UIElement::setTextFillColour(Gui::Colour textFillColour) {
    text_.setFillColor(Utility::convertOwnColourToSFMLColour(textFillColour));
}

Gui::Colour Gui::UIElement::getTextFillColour() const {
    return Utility::convertSFMLColourToOwnColour(text_.getFillColor());
}

Gui::Colour Gui::UIElement::getFillColour() const {
    return Utility::convertSFMLColourToOwnColour(border_.getFillColor());
}

Position Gui::UIElement::getPosition() const {
    return {outline_.getPosition().x,
            outline_.getPosition().y};
}

Dimensions Gui::UIElement::getDimensions() const {
    return {outline_.getGlobalBounds().width,
            outline_.getGlobalBounds().height};
}

bool Gui::UIElement::contains(float x, float y) const{
    return (x >= border_.getPosition().x && x <= border_.getPosition().x +
            border_.getGlobalBounds().width) && (y >= border_.getPosition().y &&
            y <= border_.getPosition().y + border_.getGlobalBounds().height);
}

void Gui::UIElement::draw(Gui::Window &renderTarget) {
    renderTarget.draw(outline_);
    renderTarget.draw(border_);
    renderTarget.draw(text_);
}

void Gui::UIElement::resize() {
    border_.setSize(sf::Vector2f(
        text_.getGlobalBounds().width + padding_.left + padding_.right,
        text_.getGlobalBounds().height + padding_.top + padding_.bottom
    ));
    outline_.setSize(sf::Vector2f(
		border_.getGlobalBounds().width + margin_.left + margin_.right,
        border_.getGlobalBounds().height + margin_.top + margin_.bottom
    ));
}

void Gui::UIElement::hide() {
    isHidden_ = true;
    Utility::makeInvisible(outline_);
    Utility::makeInvisible(border_);
    Utility::makeInvisible(text_);
}

void Gui::UIElement::show() {
    isHidden_ = false;
    Utility::makeVisible(outline_);
    Utility::makeVisible(border_);
    Utility::makeVisible(text_);
}

bool Gui::UIElement::isHidden() const {
    return isHidden_;
}

Gui::Padding Gui::UIElement::getPadding() const {
    return padding_;
}

Gui::Margin Gui::UIElement::getMargin() const {
    return margin_;
}

Gui::UIElement::~UIElement() = default;
