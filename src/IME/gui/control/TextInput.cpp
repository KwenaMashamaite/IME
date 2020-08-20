#include "IME/gui/input/Mouse.h"
#include "IME/gui/control/TextInput.h"
#include "IME/gui/input/Keyboard.h"

namespace IME::Gui {
    TextInput::TextInput(const std::string& placeholder) : ClickableUIElement(placeholder),
         placeholder_(placeholder), isPlaceholderCleared_(false), isFocused_(false), caretPosition_(0)
     {
        onFocusOutlineColour_ = {37, 63, 255}; // Blue
        defaultOutlineColour_ = {61, 61, 61}; // Grey

        setPadding(2.0f);
        setOutlineThickness(1.0f);
        setTextColour(Colour::Black);
        setBackgroundColour(Colour::White);
        setOutlineColour(defaultOutlineColour_); // Grey
        init();
    }

    void TextInput::init() {
        // Focus the element when it is clicked
        addEventListener("click", Callback<>([this]{
            setFocus(true);
        }));

        // Clear placeholder when element gains focus and no text has been entered
        addEventListener("focused", Callback<>([this]{
            if (!isPlaceholderCleared()){
                auto width = getText().size();
                setText("|");
                setSize(width, getTextCharSize());
                isPlaceholderCleared_ = true;
            }
            setOutlineColour(onFocusOutlineColour_);
        }));

        // reapply placeholder when element loses focus and no text has been entered
        addEventListener("unfocused", Callback<>([this]{
            if (getText().front() == '|') { //User did not enter any text
                auto width = getText().size();
                setText(placeholder_);
                setSize(width, getTextCharSize());
                isPlaceholderCleared_ = false;
            }
            setOutlineColour(defaultOutlineColour_);
        }));
    }

    void TextInput::setFocus(bool isFocused) {
        if (isFocused_ != isFocused && !isHidden()){
            isFocused_ = isFocused;
            if (isFocused)
                emit("focused");
            else
                emit("unfocused");
        }
    }

    void TextInput::setPlaceHolder(const std::string &placeholder) {
        if (placeholder_ != placeholder) {
            placeholder_ = placeholder;
            if (!isPlaceholderCleared())
                setText(placeholder_); // Replace old placeholder with a new one
        }
    }

    void TextInput::setSize(float width, float height) {
        // UIElement assumes the dimensions of the text content, therefore we will
        // adjust the size of the element by altering its text properties
        if (width >= 0 && height >= 0) {
            if (getTextCharSize() != height)
                setTextCharSize(height);
            if (getText().size() != width) {
                auto newText = getText();
                newText.resize(width, ' ');
                setText(newText);
            }
        }
    }

    void TextInput::setSize(Dimensions size) {
        setSize(size.width, size.height);
    }

    void TextInput::popBack() {
        if (caretPosition_ > 0) {
            auto text = getText();
            caretPosition_--;
            if (caretPosition_ == 0) { // Prevent container from collapsing due to no text @todo fix this
                text.at(caretPosition_) = '|';
                text.at(caretPosition_ + 1) = ' ';
            } else {
                text.at(caretPosition_) = '|';
                if (caretPosition_ + 1 < text.size())
                    text.at(caretPosition_ + 1) = ' ';
            }
            setText(text);
        }
    }

    bool TextInput::isFocused() const {
        return isFocused_;
    }

    bool TextInput::isPlaceholderCleared() const {
        return isPlaceholderCleared_;
    }

    std::string TextInput::getType() const {
        return "TextInput";
    }

    void TextInput::append(char character) {
        auto text = getText();
        if (caretPosition_ != text.size()) {
            text.insert(caretPosition_, 1, character);
            text.pop_back();
            caretPosition_++;
            setText(text);
            emit("keyPressed", character);

            auto caretPos = text.find_first_of('|');
            if (caretPos < text.size())
                emit("textEntered", text.substr(0, caretPos));
            else
                emit("textEntered", text);
        }
    }

    void TextInput::handleEvent(sf::Event event) {
        ClickableUIElement::handleEvent(event);

        if (event.type == sf::Event::TextEntered) {
            if (auto character = static_cast<char>(event.text.unicode); isFocused()) {
                static constexpr auto enterKeyCode = 13;
                static constexpr auto backspaceKeyCode = 8;
                if (static_cast<int>(character) != enterKeyCode) {
                    if (static_cast<int>(character) == backspaceKeyCode)
                        popBack();
                    else
                        append(character);
                }
            }
        } else if (event.type ==  sf::Event::MouseButtonPressed) {
            auto pressedButton = static_cast<Input::Mouse::Button>(
                    static_cast<unsigned int>(event.mouseButton.button));
            if (pressedButton == Input::Mouse::Button::Left &&
                !isMouseOverElement() && isFocused())
                setFocus(false);
        }
    }
}
