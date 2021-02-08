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

#ifndef IME_TABS_H
#define IME_TABS_H

#include "IME/Config.h"
#include "IWidget.h"
#include "IME/ui/renderers/TabsRenderer.h"
#include <TGUI/Widgets/Tabs.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A Tabs widget
         *
         * This widget can hold multiple tabs. If you want Tabs with
         * panels, checkout the TabsContainer class
         */
        class IME_API Tabs : public IWidget {
        public:
            using sharedPtr = std::shared_ptr<Tabs>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Tabs>; //!< const shared widget pointer

            /**
             * @brief Constructor
             */
            Tabs();

            /**
             * @brief Create a new tabs widget
             * @return The new tabs widget
             */
            static sharedPtr create();

            /**
             * @brief Create a copy of another tabs
             * @param other The tabs to copy
             * @param shareRenderer True if the new tabs should have the
             *          same renderer as the copied tabs
             * @return The new tabs widget
             *
             * When the tabs share a renderer, changes in a render
             * property of one of the tabs automatically reflect on
             * the other tabs, otherwise each tabs has its own renderer
             * and changes in render properties are isolated to the specific
             * tabs.
             *
             * @note when the tabs don't share a render, the renderer of
             * the new tabs widget will initially have the properties of
             * the copied tabs such that the two look the same after this
             * function returns
             *
             * By default, the tabs share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the tabs renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the tab is displayed.
             *
             * @note The tab has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(TabsRenderer::sharedPtr renderer);

            /**
             * @brief Get the tabs renderer
             * @return The tabs renderer
             *
             * The renderer gives access to functions that determine how the
             * tab is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            TabsRenderer::sharedPtr getRenderer();

            /**
             * @brief Set whether or not the tabs auto-size
             * @param autoSize True to enable auto-size, otherwise false
             *
             * When the tabs are in auto-size mode, the width of the tabs
             * will be dependent on the text which they contain. Otherwise,
             * all tabs have an equal width to fill the size of the widget
             *
             * The tabs are auto-sized by default
             */
            void setAutoSize(bool autoSize);

            /**
             * @brief Check whether if the tabs are auto-sized or not
             * @return True if auto-sized, otherwise false
             *
             * @see setAutoSize
             */
            bool getAutoSize() const;

            /**
             * @brief Add a new tab
             * @param text The text of the tab that will be drawn on top of it
             * @param select True to immediately select tab, otherwise false
             * @return The index of the tab in the list
             *
             * @warning The index returned by this function may be invalid
             *          when a tab is removed
             */
            std::size_t add(const std::string& text, bool select = true);

            /**
             * @brief Insert a new tab between other tabs
             * @param index The index where the tab is inserted
             * @param text The text of the tab that will be drawn on top of it
             * @param select True to immediately select tab, otherwise false
             *
             * @a index of 0 means before the first tab and 1 means behind
             * the first tab
             */
            void insert(std::size_t index, const std::string& text, bool select = true);

            /**
             * @brief Get the text of a tab
             * @param index Index of the tab to get the text of
             * @return The text of the specified tab or an empty string if the
             *         index is invalid
             *
             * The first tab has an index of 0
             */
            std::string getText(std::size_t index) const;

            /**
             * @brief Change the text of a tab
             * @param index Index of the tab whose text is to be changed
             * @param text The new tab text
             * @return True if the text was successfully changed or false if
             *         the index is invalid
             */
            bool changeText(std::size_t index, const std::string& text);

            /**
             * @brief Select tab with a given text
             * @param text The text of the tab t select
             * @return True if the tab was selected or false if the tab with
             *         @a text doesn't exists or the tab is hidden or disabled
             *
             * If there are multiple tabs with the same text, then the first
             * one will be selected. When false is returned, the selected tab
             * will be deselected
             *
             * @see select(int)
             */
            bool select(const std::string& text);

            /**
             * @brief Select a tab with a given index
             * @param index Index of the tab to be selected
             * @return True if the tab was selected or false if the index is
             * invalid or the tab is hidden or disabled
             *
             * When false is returned, the selected tab will be deselected
             *
             * @see select(const std::string&)
             */
            bool select(std::size_t index);

            /**
             * @brief Deselect the selected tab
             */
            void deselect();

            /**
             * @brief Remove a tab with a given text
             * @param text The text on the tab to remove
             * @return True if the tab was removed or false if there is no
             *         tab with the given text
             *
             * @see remove(std::size_t)
             */
            bool remove(const std::string& text);

            /**
             * @brief Remove a tab with a given index
             * @param index The index of the tab to remove
             * @return True if the tab was removed or false if the index is
             *         invalid
             */
            bool remove(std::size_t index);

            /**
             * @brief Remove all tabs
             */
            void removeAll();

            /**
             * @brief Get the text that is drawn on the currently selected tab
             * @return The texts on the selected tab or an empty string if
             *         no tab is currently selected
             */
            std::string getSelected() const;

            /**
             * @brief Get the index of the currently selected tab
             * @return The index of the selected tab or -1 if not tab is
             *         currently selected
             *
             * @warning The index returned by this function may be invalid
             *          if a tab is removed
             */
            int getSelectedIndex() const;

            /**
             * @brief Hide or show a tab
             * @param index Index of the tab to hide or show
             * @param visible True to show or false to hide
             */
            void setTabVisible(std::size_t index, bool visible);

            /**
             * @brief Check if a tab is visible or not
             * @param index Index of the tab to be checked
             * @return True if the tab is visible or false if the tab is not
             *         visible or the index is invalid
             */
            bool isTabVisible(std::size_t index) const;

            /**
             * @brief Enable or disable a tab
             * @param index Index of the tab t enable or disable
             * @param enabled True to enable or false to disable
             */
            void setTabEnabled(std::size_t index, bool enabled);

            /**
             * @brief Check whether a tab is enabled or not
             * @param index The index of the tab to be checked
             * @return True if the tab is enabled, otherwise false
             */
            bool isTabEnabled(std::size_t index) const;

            /**
             * @brief Set the height of the tabs
             * @param height New height of the tabs
             *
             * When the tabs are auto-sizing, this function allows changing
             * the width of the tabs without setting a fixed width like calling
             * setSize would do
             *
             * @see setAutoSize
             */
            void setTabHeight(float height);

            /**
             * @brief Set the maximum tab width of the tabs
             * @param maximumWidth Maximum width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * If the text on the tab is longer than this width then it will
             * be cropped to fit inside the tab.
             *
             * By default, the maximum width is 0 which means that there is
             * no limitation
             *
             * @see setAutoSize
             */
            void setMaximumTabWidth(float maximumWidth);

            /**
             * @brief Get the maximum tab width of the tabs
             * @return The maximum tab width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * If the text on the tab is longer than this width then it will
             * be cropped to fit inside the tab.
             *
             * By default, the maximum width is 0 which means that there is no
             * limitation
             *
             * @see setAutoSize
             */
            float getMaximumTabWidth() const;

            /**
             * @brief Set the minimum width of the tabs
             * @param minimumWidth Minimum width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * Every tab is at least as wide as this minimum or twice the
             * distance to side
             *
             * @see setAutoSize
             */
            void setMinimumTabWidth(float minimumWidth);

            /**
             * @brief Get teh minimum tab width of the tabs
             * @return Minimum width of a single tab
             *
             * This property only has effect when the tabs are auto-sizing.
             * Every tab is at least as wide as this minimum or twice the
             * distance to side
             */
            float getMinimumTabWidth() const;

            /**
             * @brief Get the number of tabs
             * @return The number of tabs
             */
            std::size_t getTabsCount() const;

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             *
             * If the size is 0 then the text will be scaled to fit in the
             * tab
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the tab
             * @param width The width of the tab
             * @param height The height of the tab
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the tabs relative to the size of
             *        its parent
             * @param width The new width of the tabs
             * @param height The new height of the tabs
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * tabs->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the tab
             * @return Current size of the tab
             *
             * This function only returns the size of the tab (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the tab
             * @return The absolute size of the tab
             *
             * The absolute size includes the size of the tab, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the tabs
             * @param width New width of the tabs
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the tabs relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * tabs->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the tabs while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the tabs
             * @param height New height of the tabs
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the tabs relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * tabs->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the tabs while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the tabs
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the tabs
             * @return The cursor shown when hovering above the tabs
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the tab
             * @return The type of the tab
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the tabs with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the tabs currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the tabs
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the tabs with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the tabs currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the tabs
             * will be back in the state in which it was when this function
             * was called
             *
             * @see showWithEffect
             * @see isAnimationPlaying
             */
            void hideWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Check whether or not an animation is currently playing
             * @return True if an animation is playing, otherwise false
             *
             * @see showWithEffect
             * @see hideWithEffect
             */
            bool isAnimationPlaying() const override;

            /**
             * @brief Show or hide a tabs
             * @param visible True to show or false to hide
             *
             * If the tabs is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The tabs is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the tabs is visible or not
             * @return True if the tabs is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the tabs
             *
             * This function will hide the tabs if its currently
             * visible and vice versa
             * 
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the tab
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the tab, false if
             *         coordinates do not lie inside the tab
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the tab
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the tab is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the tab
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the tab is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the tabs relative to the
             *        size of its parent
             * @param x New x coordinate of the tabs
             * @param y New y coordinate of the tabs
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * tabs->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the tabs is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the tab
             * @return Current position of the tab
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the tab
             * @return The absolute position of the tab
             * 
             * Unlike getPosition, this function returns the absolute 
             * position of the top-left point of the tab instead 
             * of the relative position to its parent
             * 
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the tab
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the tab is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the tab
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the tab,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the tab
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the tab
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the tab
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the tab by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the tab,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the tab by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the tab,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the tab
             * @return Current scale of the tab
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the tab
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the tab defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the tab, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the tab is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the tab
             * @param origin New origin
             *
             * The origin of the tab defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the tab, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the tab is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the tab
             * @return Local origin of the tab
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the tab by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the tab,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the tab by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the tab,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget
             * @return The internal pointer to a third party widget
             *
             * @warning This function is intended for internal use only and
             * should never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

        private:
            /**
             * @brief Initialize events
             *
             * These events will notify event listeners about an internal state
             * change of the widget when that state changes
             */
            void initEvents();

        private:
            std::shared_ptr<tgui::Tabs> tabs_; //!< Pointer to to third party tabs
            TabsRenderer::sharedPtr renderer_; //!< Tab renderer
        };
    }
}

#endif //IME_TABS_H
