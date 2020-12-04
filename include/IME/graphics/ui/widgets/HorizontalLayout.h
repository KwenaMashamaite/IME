////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Container that automatically resizes children to fit the entire
 *        available space between children. The children are stacked
 *        horizontally
 */

#ifndef IME_HORIZONTALLAYOUT_H
#define IME_HORIZONTALLAYOUT_H

#include "IBoxLayout.h"
#include "IME/graphics/ui/renderers/BoxLayoutRenderer.h"
#include <TGUI/Widgets/HorizontalLayout.hpp>

namespace IME {
    namespace UI {
        class IME_API HorizontalLayout : public IBoxLayout {
        public:
            /**
             * @brief Create a horizontal layout
             * @param width Width of the layout
             * @param height Height of the layout
             */
            HorizontalLayout(float width, float height);

            /**
             * @brief Set the layout renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the button is displayed. The layout
             * has a default renderer which can be manipulated using the
             * @see getRenderer() function
             */
            void setRenderer(std::shared_ptr<BoxLayoutRenderer> renderer);

            /**
             * @brief Get the layout renderer
             * @return The layout renderer
             *
             * The renderer gives access to functions that determine how the
             * layout is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            std::shared_ptr<BoxLayoutRenderer> getRenderer();

            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Set the text content of the widget
             * @param content New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &content) override;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The hieght of teh widget
             */
            void setSize(float width, float height) override;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget, to get the
             * absolute size (with the margin, outline thickness etc...)
             * @see getAbsoluteSize()
             */
            Vector2f getSize() const override;

            /**
            * @brief Get the absolute size of the widget
            * @return The absolute size of the widget
            *
            * The absolute size includes the size of the widget, the padding,
            * margin and outline thickness. To get just the size of the widget
            * use @see getSize()
            */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Get the widgets text content
             * @return Elements text content
             */
            std::string getText() const override;

            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Get the type of the widget
             * @return Type of the widget
             */
            std::string getType() const override;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will make the widget invisible if its currently
             * visible and vice versa. The visibility is not automatically
             * reflected on the render target. A call to draw() must be made
             * after calling this function
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Hide widget from a render target
             */
            void hide() override;

            /**
             * @brief Show a hidden widget
             *
             * This function will reveal the widget that was hidden prior to
             * function call. Calling this function on an object that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Check is the widget is hidden or not
             * @return True if the widget is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Set the position of the widget
             * @param X coordinate of the new position
             * @param Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable widget
             * is (0, 0).
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the widget
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * See the move function to apply an offset based on the previous
             * position instead. The default position of a transformable widget
             * is (0, 0).
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the orientation of the widget
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. The default rotation of a transformable widget
             * is 0.
             */
            void setRotation(float angle) override;

            /**
             * @brief Set the scale factors of the widget
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale.
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factors of the object
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Get the current scale of the object
             * @return Current scale of the object
             */
            Vector2f getScale() const override;

            /**
             * @brief set the local origin of the object
             * @param origin New origin
             *
             * The origin of an object defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the object, and ignore all
             * transformations (position, scale, rotation).
             * The default origin of a transformable object is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Move the object by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the object,
             * unlike @see setPosition which overwrites it
             */
            void move(Vector2f offset) override;

            /**
             * @brief Scale the object by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the object,
             * unlike @see setScale which overwrites it
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Set the local origin of the widget
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of an widget defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the widget, and ignore all
             * transformations (position, scale, rotation).
             * The default origin of a transformable widget is (0, 0).
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Get the position of the widget
             * @return Current position of the widget
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the local origin of the widget
             * @return get the local origin of the widget
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Get the orientation of the widget
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360].
             */
            float getRotation() const override;

            /**
             * @brief Move the widget by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the widget,
             * unlike setPosition which overwrites it.
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Rotate the widget
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the widget,
             * unlike setRotation() which overwrites it
             */
            void rotate(float angle) override;

            /**
             * @brief Scale the widget
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the widget,
             * unlike setScale() which overwrites it.
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Insert a widget to the container
             * @param index Where the widget should be inserted
             * @param widget Pointer to the widget to be inserted
             * @param widgetName Name of the widget
             *
             * The widget name must be set if the widget is to be retrieved at
             * a later time. In addition, the name must not contain whitespaces
             * @note If the index is too high, the widget will simply be added
             * at the end of the list
             */
            void insertWidget(std::size_t index, std::shared_ptr<IWidget> widget,
                 const std::string &widgetName) override;

            /**
             * @brief Remove a single widget that was added to the container
             * @param index Position of the widget to be removed
             * @return True if the widget was removed, or false if the index is
             *          invalid
             */
            bool removeWidgetAt(std::size_t index) override;

            /**
             * @brief Get the widget at a certain position
             * @param index Position of the widget to retrieve
             * @return Widget at the given position or nullptr if the index is
             *         invalid
             */
            std::shared_ptr<IWidget> getWidgetAt(std::size_t index) const override;

            /**
             * @brief Add an extra space after the last widget
             * @param ratio Ratio to determine the size compared to other widgets
             *
             * The space will act as an invisible non-interactable widget, the
             * ratio will be part of the total ratio of all widgets
             */
            void addSpace(float ratio) override;

            /**
             * @brief Insert an extra space between widgets
             * @param index Index of the widget in the container
             * @param ratio Ratio to determine the size compared to other widgets
             *
             * The space will act as an invisible non-interactable widget, the
             * ratio will be part of the total ratio of all widgets.
             */
            void insertSpace(std::size_t index, float ratio) override;

            /**
             * @brief Set the ratio of a widget
             * @param widget Widget from which the ratio should be changed
             * @param ratio New ratio to determine the size compared to other
             *         widgets
             * @return True if the widget was valid and the ratio was changed,
             *          or false if the widget was not found
             */
            bool setRatio(std::shared_ptr<IWidget> widget, float ratio) override;

            /**
             * @brief Set the ratio of a widget at a certain index
             * @param index Index of the widget or space
             * @param ratio ew ratio to determine the size compared to other
             *         widgets
             * @return True if the index is valid and the ratio was changed,
             *          otherwise false
             */
            bool setRatio(std::size_t index, float ratio) override;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param widget Widget from which the ratio should be returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            float getRatio(std::shared_ptr<IWidget> widget) const override;

            /**
             * @brief Get the ratio of a widget at a certain index
             * @param index Index of the widget from which the ratio should be
             *         returned
             * @return The ratio of the widget or 0 when the widget was not
             *         found
             */
            float getRatio(std::size_t index) const override;

            /**
             * @brief Add a widget to the container
             * @param widgetPtr Widget to be added
             * @param widgetName Unique name of the widget
             * @return True if the widget was added to the container or false
             *         if the container already has a widget with the same name
             *         as the specified widget name
             *
             * The name of the widget must not contain whitespaces
             */
            bool addWidget(std::shared_ptr<IWidget> widgetPtr,
                const std::string &widgetName) override;

            /**
             * @brief Get a widget in the container
             * @param widgetName Name of the widget to retrieve
             * @return Pointer to the specified widget or a nullptr if the
             *         container does not have a widget with the specified
             *         name
             *
             * The container will first search for widgets that are direct
             * children of it, but when none of the child widgets match the
             * given name, a recursive search will be performed.
             */
            std::shared_ptr<IWidget> getWidget(const std::string &widgetName)
                const override;

            /**
             * @brief Get a list of all widgets in the container
             * @return A vector of all widgets in the container
             */
            const std::vector<IWidget> &getWidgets() const override;

            /**
             * @brief Remove a widget from the container
             * @param widget Name of the widget to be removed from the container
             * @return True if the widget was removed or false if the widget
             *         does not exist in the container
             */
            bool removeWidget(const std::string &widget) override;

            /**
             * @brief Remove all widgets from the container
             */
            void removeAllWidgets() override;

            /**
             * @brief Place a widget before all other widgets, to the front
             *        of the z-order
             * @param widget The widget that should be moved to the front
             */
            void moveWidgetToFront(std::shared_ptr<IWidget> widget) override;

            /**
            * @brief Place a widget behind all other widgets, to the back
            *        of the z-order
            * @param widget The widget that should be moved to the front
            */
            void moveWidgetToBack(std::shared_ptr<IWidget> widget) override;

            /**
             * @brief Place a widget one step forward in the z-order
             * @param widget The widget that should be moved one step forward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t
            moveWidgetForward(std::shared_ptr<UI::IWidget> widget) override;

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t
            moveWidgetBackward(std::shared_ptr<UI::IWidget> widget) override;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note If the focused widget is a container, then a pointer to
             * the container is returned rather than a pointer to the focused
             * widget inside that container. @see getFocusedLeaf() should be
             * used to get the widget that is focused inside a container
             */
            std::shared_ptr<UI::IWidget> getFocusedWidget() const override;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note Unlike @see getFocusedWidget() which returns a pointer to
             * a container when the focused widget is a child of another
             * container within the container, this function will always return
             * the focused widget regardless of whether its a direct child of
             * the container or not
             */
            std::shared_ptr<UI::IWidget> getFocusedLeaf() const override;

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the container
             *          view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            std::shared_ptr<UI::IWidget>
            getWidgetAtPosition(Vector2f pos) const override;

            /**
             * @brief Focus the next widget in the container
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusNextWidget(bool recursive) override;

            /**
             * @brief Focus the previous widget in the container
             * @param recursive Set true to focus next widget when the currently
             *        focused widget is a container or false to focus the sibling
             *        of that container
             * @return True if the next widget was focused, otherwise false
             */
            bool focusPreviousWidget(bool recursive) override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget object
             * @return The internal pointer to a third party widget object
             *
             * @warning This function is intended for internal use only and
             * must never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

        private:
            /**
             * @brief Initialize events
             *
             * These events will notify event listeners about an internal state
             * change of the object when that state changes
             */
            void initEvents();

        private:
            //Widgets container
            std::unordered_map<std::string, std::shared_ptr<IWidget>> widgets_;
            //Pointer to third party layout
            std::shared_ptr<tgui::HorizontalLayout> layout_;
            //Renderer for this layout
            std::shared_ptr<BoxLayoutRenderer> renderer_;
            //How long the layout takes before its completely hidden or shown
            static const int fadeAnimDuration_ = 100;
        };
    }
}

#endif
