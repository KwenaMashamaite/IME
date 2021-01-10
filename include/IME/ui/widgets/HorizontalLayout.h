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

#ifndef IME_HORIZONTALLAYOUT_H
#define IME_HORIZONTALLAYOUT_H

#include "IBoxLayout.h"
#include "IME/ui/renderers/BoxLayoutRenderer.h"
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A widget container that stacks widgets horizontally
         * 
         * The widget automatically resizes children to fit the entire 
         * size of the container
         */
        class IME_API HorizontalLayout : public IBoxLayout {
        public:
            using sharedPtr = std::shared_ptr<HorizontalLayout>; //!< Shared widget pointer

            /**
             * @brief Constructor
             * @param width Width of the layout relative to the size of its parent
             * @param height Height of the layout relative to the size of its
             *        parent
             * 
             * The relative size is specified in percentages as shown:
             * 
             * @code
             * HorizontalLayout({"50%", "20%"});
             * @endcode
             * 
             * By default, the layout is the same size as its parent
             */
            explicit HorizontalLayout(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Create a new HorizontalLayout widget
             * @param width Width of the panel relative to the size of its parent
             * @param height Height of the panel relative to the size of its parent
             * @return The new HorizontalLayout
             * 
             * * The relative size is specified in percentages as shown:
             * 
             * @code
             * HorizontalLayout::create({"50%", "20%"});
             * @endcode
             * 
             * By default, the new panel is the same size as its parent
             */
            static sharedPtr create(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Set the layout renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the layout is displayed. The layout
             * has a default renderer which can be manipulated using the
             * getRenderer function
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<BoxLayoutRenderer> renderer);

            /**
             * @brief Get the layout renderer
             * @return The layout renderer
             *
             * The renderer gives access to functions that determine how the
             * layout is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            std::shared_ptr<BoxLayoutRenderer> getRenderer();

            /**
             * @brief Set the character size of all existing and future widgets
             * @param charSize New character size
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of all widgets in the layout
             * @return The character size of all the widgets
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the layout
             * @param width The width of the layout
             * @param height The height of the layout
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the layout relative to the size of
             *        its parent
             * @param width The new width of the layout
             * @param height The new height of the layout
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * layout->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the layout
             * @return Current size of the layout
             *
             * This function only returns the size of the layout (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the layout
             * @return The absolute size of the layout
             *
             * The absolute size includes the size of the layout, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the layout
             * @param width New width of the layout
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the layout relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * layout->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the layout while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the layout
             * @param height New height of the layout
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the layout relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * layout->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the layout while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Get the type of the layout
             * @return The type of the layout
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show a hidden layout
             *
             * This function will reveal the layout that was hidden prior to
             * function call. Calling this function on a layout that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Hide layout
             */
            void hide() override;

            /**
             * @brief Check if the layout is hidden or not
             * @return True if the layout is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Toggle the visibility of the layout
             *
             * This function will hide the layout if its currently
             * visible and vice versa
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the layout
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the layout, false if
             *         coordinates do not lie inside the layout
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the layout
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the layout is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the layout
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead. 
             * 
             * The default position of the layout is (0, 0)
             * 
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the layout relative to the
             *        size of its parent
             * @param x New x coordinate of the layout
             * @param y New y coordinate of the layout
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * layout->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the layout is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the layout
             * @return Current position of the layout
             */
            Vector2f getPosition() const override;

            /**
             * @brief Set the orientation of the layout
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. 
             * 
             * The default rotation of the layout is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the layout
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the layout,
             * unlike setRotation which overwrites it
             * 
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the layout
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the layout
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the layout
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the layout by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the layout,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the layout by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the layout,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the layout
             * @return Current scale of the layout
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the layout
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the layout defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the layout, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the layout is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the layout
             * @param origin New origin
             *
             * The origin of the layout defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the layout, and ignore all
             * transformations (position, scale, rotation).
             * 
             * The default origin of the layout is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the layout
             * @return Local origin of the layout
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the layout by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the layout,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the layout by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the layout,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Insert a widget to the container
             * @param index Where the widget should be inserted
             * @param widget Pointer to the widget to be inserted
             * @param name Name of the widget
             *
             * The name must be unique and contain no whitespaces because the
             * container cannot store two distinct widgets with the same name
             *
             * @note If @a index is too high, the widget will simply be
             * added at the end of the list
             */
            void insertWidget(std::size_t index, std::shared_ptr<IWidget> widget,
                 const std::string &name) override;

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
            using IContainer::getWidget;

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
            size_t moveWidgetForward(std::shared_ptr<IWidget> widget) override;

            /**
             * @brief Place a widget one step backwards in the z-order
             * @param widget The widget that should be moved one step backward
             * @return New index in the widgets list (one higher than the old
             *         index or the same if the widget was already in front),
             */
            size_t moveWidgetBackward(std::shared_ptr<IWidget> widget) override;

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
            std::shared_ptr<IWidget> getFocusedWidget() const override;

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
            std::shared_ptr<IWidget> getFocusedLeaf() const override;

            /**
             * @brief Get a widget at a given position
             * @param pos The position of the widget relative to the container
             *          view
             * @return Pointer to the widget at the specified position or a
             *         nullptr if there is no widget at that position
             */
            std::shared_ptr<IWidget> getWidgetAtPosition(Vector2f pos) const override;

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
            std::shared_ptr<tgui::HorizontalLayout> layout_;                    //!< Pointer to third party library
            std::shared_ptr<BoxLayoutRenderer> renderer_;                       //!< Renderer for this layout
        };
    }
}

#endif // IME_HORIZONTALLAYOUT_H
