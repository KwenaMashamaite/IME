////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_PANEL_H
#define IME_PANEL_H

#include "IME/Config.h"
#include "IContainer.h"
#include "IME/graphics/ui/renderers/PanelRenderer.h"
#include <TGUI/Widgets/Panel.hpp>
#include <memory>

namespace IME {
    namespace UI {
        /**
         * @brief A widget container that has a background colour and
         *        optional borders
         */
        class IME_API Panel : public IContainer {
        public:
            using sharedPtr = std::shared_ptr<Panel>; //!< Shared widget pointer

            /**
             * @brief Constructor
             */
            Panel();

            /**
             * @brief Create a new panel widget
             * @return The new panel
             */
            static sharedPtr create();

            /**
             * @brief Set the panels renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the panel is displayed.
             *
             * @note The panel has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<PanelRenderer> renderer);

            /**
             * @brief Get the panels renderer
             * @return The panels renderer
             *
             * The renderer gives access to functions that determine how the
             * panel is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             */
            std::shared_ptr<PanelRenderer> getRenderer();

            /**
             * @brief Set the text content of the panel
             * @param text New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text) override;

            /**
             * @brief Get the panels text content
             * @return The panels text content
             */
            std::string getText() const override;

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the panel
             * @param width The width of the panel
             * @param height The height of the panel
             */
            void setSize(float width, float height) override;

            /**
             * @brief Get the size of the panel
             * @return Current size of the panel
             *
             * This function only returns the size of the panel (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the panel
             * @return The absolute size of the panel
             *
             * The absolute size includes the size of the panel, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Get the type of the panel
             * @return The type of the panel
             */
            std::string getType() const override;

            /**
             * @brief Show a hidden panel
             *
             * This function will reveal the panel that was hidden prior to
             * function call. Calling this function on a panel that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Hide panel
             */
            void hide() override;

            /**
             * @brief Check if the panel is hidden or not
             * @return True if the panel is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Toggle the visibility of the panel
             *
             * This function will hide the panel if its currently
             * visible and vice versa
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the panel
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the panel, false if
             *         coordinates do not lie inside the panel
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the panel
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the panel is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the panel
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the panel is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Get the position of the panel
             * @return Current position of the panel
             */
            Vector2f getPosition() const override;

            /**
             * @brief Set the orientation of the panel
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the panel is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the panel
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the panel,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the panel
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the panel
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the panel
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the panel by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the panel,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the panel by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the panel,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the panel
             * @return Current scale of the panel
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the panel
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the panel defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the panel, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the panel is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the panel
             * @param origin New origin
             *
             * The origin of the panel defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the panel, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the panel is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the panel
             * @return Local origin of the panel
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the panel by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the panel,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the panel by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the panel,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Add a widget to the container
             * @param widget Widget to be added
             * @param name Unique name of the widget
             * @return True if the widget was added to the container or false
             *         if the container already has a widget with the same name
             *         as the specified widget name
             *
             * The name of the widget must not contain whitespaces
             */
            bool addWidget(std::shared_ptr<IWidget> widget,
                const std::string &name) override;

            /**
             * @brief Get a widget in the container
             * @param name Name of the widget to retrieve
             * @return Pointer to the specified widget or a nullptr if the
             *         container does not have a widget with the specified
             *         name
             *
             * The container will first search for widgets that are direct
             * children of it, but when none of the child widgets match the
             * given name, a recursive search will be performed.
             */
            std::shared_ptr<IWidget> getWidget(const std::string &name) const override;

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
            size_t moveWidgetForward(std::shared_ptr<UI::IWidget> widget) override;

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t moveWidgetBackward(std::shared_ptr<UI::IWidget> widget) override;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note If the focused widget is a container, then a pointer to
             * the container is returned rather than a pointer to the focused
             * widget inside that container
             *
             * @see getFocusedLeaf
             */
            std::shared_ptr<UI::IWidget> getFocusedWidget() const override;

            /**
             * @brief Get the currently focused widget inside the container
             * @return Pointer to the focused child widget or a nullptr if none
             *         of the widgets are currently focused
             *
             * @note Unlike getFocusedWidget which returns a pointer to
             * a container when the focused widget is a child of another
             * container within the container, this function will always return
             * the focused widget regardless of whether its a direct child of
             * the container or not
             *
             * @see getFocusedWidget
             */
            std::shared_ptr<UI::IWidget> getFocusedLeaf() const override;

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the container
             *          view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            std::shared_ptr<UI::IWidget> getWidgetAtPosition(Vector2f pos) const override;

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
            std::unordered_map<std::string, std::shared_ptr<IWidget>> widgets_; //!< Widgets container
            std::shared_ptr<tgui::Panel> panel_;                                //!< Pointer to third party panel
            std::shared_ptr<PanelRenderer> renderer_;                           //!< Renderer
        };
    }
}

#endif //IME_PANEL_H
