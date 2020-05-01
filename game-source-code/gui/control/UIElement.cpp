#include "UIElement.h"
#include "resources/ResourceManager.h"
#include "utility/Utility.h"
#include <algorithm>

Gui::UIElement::UIElement()
    : isHidden_(false)
{
    initialize();
}

Gui::UIElement::UIElement(const std::string &textContent)
    : isHidden_(false)
{
    initialize();
    setText(textContent);
    text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
}

void Gui::UIElement::initialize() {
    auto defaultTextFont = "philosopher.ttf";
    auto defaultTextCharSize = 20u;

    initEvents();
    setTextFont(defaultTextFont);
    setTextCharSize(defaultTextCharSize);
    setPadding(0.0f);
    setOutlineThickness(0.0f);

    outline_.setFillColor(sf::Color(40, 26, 5)); //Dark brown
    border_.setFillColor(sf::Color::White);
    text_.setFillColor(sf::Color::Black);
}

void Gui::UIElement::initEvents() {
    addListener("textLocalBoundsChanged", Callback<>([this]{
        text_.setOrigin(text_.getLocalBounds().left, text_.getLocalBounds().top);
    }));

    addListener("textFontChanged", Callback<>([this]{
        onTextDimensionsChange();
    }));

    addListener("textContentChanged", Callback<>([this] {
        onTextDimensionsChange();
    }));

    addListener("textCharSizeChanged", Callback<>([this](){
        onTextDimensionsChange();
    }));

    addListener("elemDimensionsChanged", Callback<>([this](){
        onTextDimensionsChange();
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

void Gui::UIElement::setOutlineThickness(float margin) {
    margin_ = {margin, margin, margin, margin};
    emit("elemDimensionsChanged");
}

void Gui::UIElement::setPadding(float padding) {
    padding_ = {padding, padding, padding, padding};
    emit("elemDimensionsChanged");
}

void Gui::UIElement::setMargin(const Gui::Margin &margin) {
    margin_ = margin;
    emit("elemDimensionsChanged");
}

void Gui::UIElement::setPadding(const Gui::Padding &padding) {
    padding_ = padding;
    emit("elemDimensionsChanged");
}

void Gui::UIElement::setFillColour(Gui::Colour fillColour) {
    border_.setFillColor(Utility::convertOwnColourToSFMLColour(fillColour));
}

void Gui::UIElement::setTextFont(const std::string &contentFont) {
    text_.setFont(ResourceManager::getFont(contentFont));
    emit("textFontChanged");
    emit("textLocalBoundsChanged");
}

void Gui::UIElement::setTextCharSize(unsigned int charSize) {
    text_.setCharacterSize(charSize);
    emit("textCharSizeChanged");
    emit("textLocalBoundsChanged");
}

void Gui::UIElement::setText(const std::string &content) {
    text_.setString(content);
    emit("textContentChanged");
}

void Gui::UIElement::setTextFillColour(Gui::Colour textFillColour) {
    text_.setFillColor(Utility::convertOwnColourToSFMLColour(textFillColour));
}

void Gui::UIElement::setOutlineColour(Gui::Colour outlineColour) {
    outline_.setFillColor(Utility::convertOwnColourToSFMLColour(outlineColour));
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

void Gui::UIElement::onTextDimensionsChange() {
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

void Gui::UIElement::toggle() {
    isHidden_ = !isHidden_;
    if (isHidden_)
        show();
    else
        hide();
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
