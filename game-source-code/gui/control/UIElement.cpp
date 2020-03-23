#include "UIElement.h"
#include "resources/ResourceManager.h"
#include <algorithm>

Gui::UIElement::UIElement(const std::string &content, const std::string &font, unsigned int textCharSize)
    : numOfLinesInText_{0u}
{
    //Resize element when text changes
    eventEmitter_.addListener("textChanged", Callback<std::string>([this](const std::string &content) {
        if (content.empty()) {
            numOfLinesInText_ = 0;
            return;
        }
        numOfLinesInText_ = std::count(content.begin(), content.end(), '\n');
        numOfLinesInText_++; //Account for one line/last line (both dont have '\n')
        resize();
    }));
    //Resize element when the character size changes
    eventEmitter_.addListener("charSizeChanged", Callback<>([this](){
        resize();
    }));
    //Update element on dimension changes (padding and margin changes)
    eventEmitter_.addListener("dimensionsChanged", Callback<>([this](){
        resize();
        setPosition(getPosition().x, getPosition().y);
    }));

    setTextFont(font);
    setTextCharSize(textCharSize);
    setText(content);
    border_.setOutlineThickness(0.6f);
    border_.setOutlineColor(sf::Color::Transparent);
    parentRectangle_.setFillColor(sf::Color::Transparent);
    border_.setFillColor(sf::Color::Black);
    textRectangle_.setFillColor(sf::Color::Transparent);
    text_.setFillColor(sf::Color::White);
}

void Gui::UIElement::setPosition(float x, float y) {
    parentRectangle_.setPosition(x, y);
    border_.setPosition(
      	parentRectangle_.getPosition().x + margin_.left,
      	parentRectangle_.getPosition().y + margin_.top
    );
    textRectangle_.setPosition(
      	border_.getPosition().x + padding_.left,
      	border_.getPosition().y + padding_.top
    );
    text_.setPosition(
        textRectangle_.getPosition().x,
        textRectangle_.getPosition().y
	);
}

void Gui::UIElement::setMargin(float margin) {
    margin_.left = margin_.right = margin_.bottom = margin_.top = margin;
    eventEmitter_.emit("dimensionsChanged");
}

void Gui::UIElement::setPadding(float padding) {
    padding_.left = padding_.right = padding_.top = padding_.bottom = padding;
    eventEmitter_.emit("dimensionsChanged");
}

void Gui::UIElement::setMargin(const Gui::Margin &margin) {
    margin_ = margin;
    eventEmitter_.emit("dimensionsChanged");
}

void Gui::UIElement::setPadding(const Gui::Padding &padding) {
    padding_ = padding;
    eventEmitter_.emit("dimensionsChanged");
}

void Gui::UIElement::setFillColour(Gui::Colour fillColour) {
    border_.setFillColor(convertOwnColourToSFMLColour(fillColour));
}

void Gui::UIElement::setTextFont(const std::string &contentFont) {
    text_.setFont(ResourceManager::getFont(contentFont));
}

void Gui::UIElement::setTextCharSize(unsigned int charSize) {
    text_.setCharacterSize(text_.getFont()->getGlyph(
        L'A', charSize, false).bounds.height
    );
    eventEmitter_.emit("charSizeChanged");
}

void Gui::UIElement::setText(const std::string &content) {
    text_.setString(content);
    eventEmitter_.emit("textChanged");
}

void Gui::UIElement::setTextFillColour(Gui::Colour textFillColour) {
    text_.setFillColor(convertOwnColourToSFMLColour(textFillColour));
}

Gui::Colour Gui::UIElement::getTextFillColour() const {
    return convertSFMLColourToOwnColour(text_.getFillColor());
}

Gui::Colour Gui::UIElement::getFillColour() const {
    return convertSFMLColourToOwnColour(border_.getFillColor());
}

Position Gui::UIElement::getPosition() const {
    return Position{
        parentRectangle_.getPosition().x,
        parentRectangle_.getPosition().y
    };
}

Dimensions Gui::UIElement::getDimensions() const {
    return Dimensions{
        parentRectangle_.getGlobalBounds().width,
        parentRectangle_.getGlobalBounds().height
    };
}

bool Gui::UIElement::contains(float x, float y) const{
    return (x >= border_.getPosition().x && x <= border_.getPosition().x +
            border_.getGlobalBounds().width) && (y >= border_.getPosition().y &&
            y <= border_.getPosition().y + border_.getGlobalBounds().height);
}

void Gui::UIElement::draw(Gui::Window &renderTarget) {
    renderTarget.draw(parentRectangle_);
    renderTarget.draw(border_);
    renderTarget.draw(textRectangle_);
    renderTarget.draw(text_);
}

void Gui::UIElement::resize() {
    auto textHeight = (text_.getCharacterSize() * numOfLinesInText_ <
                      text_.getGlobalBounds().height ?
                      text_.getGlobalBounds().height :
                      text_.getCharacterSize() * numOfLinesInText_);

    textRectangle_.setSize(
        sf::Vector2f(text_.getGlobalBounds().width, textHeight
    ));
    border_.setSize(sf::Vector2f(
            textRectangle_.getGlobalBounds().width + padding_.left + padding_.right,
            textRectangle_.getGlobalBounds().height + padding_.top + padding_.bottom
    ));
    parentRectangle_.setSize(sf::Vector2f(
		border_.getGlobalBounds().width + margin_.left + margin_.right,
        border_.getGlobalBounds().height + margin_.top + margin_.bottom
    ));
}

sf::Color Gui::UIElement::convertOwnColourToSFMLColour(Gui::Colour color) {
    return {static_cast<sf::Uint8>(color.red),
            static_cast<sf::Uint8>(color.blue),
            static_cast<sf::Uint8>(color.green),
            static_cast<sf::Uint8>(color.opacity)};
}

Gui::Colour Gui::UIElement::convertSFMLColourToOwnColour(sf::Color SFMLColour) {
    return {SFMLColour.r, SFMLColour.b, SFMLColour.g, SFMLColour.a};
}

Gui::UIElement::~UIElement() = default;
