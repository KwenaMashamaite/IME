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

#ifndef IME_TABSCONTAINER_H
#define IME_TABSCONTAINER_H

#include "IME/Config.h"
#include "IWidget.h"
#include "Panel.h"
#include "IME/ui/renderers/TabsRenderer.h"
#include <TGUI/Widgets/TabContainer.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A widget which acts as a container for Tabs widget
         *
         * This widget can hold multiple panels which are displayed
         * one panel at a time. The widget uses Tabs to switch
         * between panels
         *
         * If you are looking for Tabs without a panel, check out the
         * Tabs class
         */
        class IME_API TabsContainer : public IWidget {
        public:
            using sharedPtr = std::shared_ptr<TabsContainer>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const TabsContainer>; //!< const shared widget pointer

            /**
             * @brief Constructor
             * @param width Width of the container relative to the size of its 
             *        parent
             * @param height Height of the container relative to the size of its
             *        parent
             * 
             * The relative size is specified in percentages as shown:
             * 
             * @code
             * TabsContainer({"50%", "20%"});
             * @endcode
             * 
             * By default, the container is the same size as its parent
             */
            explicit TabsContainer(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Create a new TabsContainer widget
             * @param width Width of the panel relative to the size of its 
             *        parent
             * @param height Height of the panel relative to the size of its
             *        parent
             * @return The new TabsContainer
             * 
             * * The relative size is specified in percentages as shown:
             * 
             * @code
             * TabsContainer::create({"50%", "20%"});
             * @endcode
             * 
             * By default, the new panel is the same size as its parent
             */
            static sharedPtr create(const std::string& width = "100%",
                const std::string& height = "100%");

            /**
             * @brief Create a copy of another container
             * @param other The container to copy
             * @param shareRenderer True if the new container should have the
             *          same renderer as the copied container
             * @return The new container widget
             *
             * When the containers share a renderer, changes in a render
             * property of one of the containers automatically reflect on
             * the other container, otherwise each container has its own renderer
             * and changes in render properties are isolated to the specific
             * container.
             *
             * @note when the containers don't share a render, the renderer of
             * the new container widget will initially have the properties of
             * the copied container such that the two look the same after this
             * function returns
             *
             * By default, the containers share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the tabs renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the container is displayed.
             *
             * @note The container has a default renderer
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<TabsRenderer> renderer);

            /**
             * @brief Get the tabs renderer
             * @return The tabs renderer
             *
             * The renderer gives access to functions that determine how the
             * container is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            std::shared_ptr<TabsRenderer> getRenderer();

            /**
             * @brief Set the height of the tabs part of the widget
             * @param height New height of the tabs part of the widget
             */
            void setTabsHeight(float height);

            /**
             * @brief Add a panel
             * @param panel Panel to be added
             * @param text Text for the container
             * @param select True to immediately select the panel, otherwise
             *        false
             *
             * The panel is added after the panel that was added during
             * the last call to this function
             *
             * By default, the panel is selected after being added
             */
            void addPanel(std::shared_ptr<Panel> panel, const std::string& text, bool select = true);

            /**
             * @brief Insert a panel between other panels
             * @param panel Panel to be added
             * @param text Text for the container
             * @param index Index where the panel should be inserted
             * @param select True to immediately select the panel, otherwise
             *               false
             * @return True if the panel was inserted or false if the given
             *         index is out of bounds
             *
             * By default, the panel is selected after successful insertion
             * 
             * @warning This function os experimental
             */
            bool insertPanel(std::shared_ptr<Panel> panel, const std::string& text,
                std::size_t index, bool select = true);

            /**
             * @brief Remove a panel from the container
             * @param panel Panel to remove
             */
            void removePanel(std::shared_ptr<Panel> panel);

            /**
             * @brief Select a panel
             * @param index Index of the panel to select
             */
            void select(std::size_t index);

            /**
             * @brief Get the number of panel in the container
             * @return The current number of panels in the container
             */
            std::size_t getPanelCount() const;

            /**
             * @brief Get the index of a given panel
             * @param panel Panel to get the index for
             * @return The index of the panel or -1 if the panel does not
             *         exist in the container
             */
            int getIndex(std::shared_ptr<Panel> panel);

            /**
             * @brief Get the currently selected panel
             * @return The panel that is selected or a nullptr if no panel
             *         is selected
             */
            std::shared_ptr<Panel> getSelected();

            /**
             * @brief Get the index of the currently selected panel
             * @return The index of the selected panel or -1 if not panel
             *         is selected
             */
            int getSelectedIndex() const;

            /**
             * @brief Get a panel with a given index
             * @param index The index of the panel to retrieve
             * @return Panel with the given index or a nullptr if the index
             *         is out of bounds
             */
            std::shared_ptr<Panel> getPanel(int index);

            /**
             * @brief Get the text of a container
             * @param index Index of the container to get the index of
             * @return The text on the container or an empty string if the index
             *         is out of bounds
             *
             * The index of the first container is 0
             */
            std::string getTabText(std::size_t index) const;

            /**
             * @brief Set the text of a container
             * @param index The index of the container whose text is to be ste
             * @param text The new text of the container
             * @return True if the text was successfully changed or false
             *         if the index is out of bounds
             *
             * The index of the first container is 0
             */
            bool changeTabText(std::size_t index, const tgui::String& text);

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             *
             * If the size is 0 then the text will be scaled to fit in the
             * container
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the container
             * @param width The width of the container
             * @param height The height of the container
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the container relative to the size of
             *        its parent
             * @param width The new width of the container
             * @param height The new height of the container
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * container->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the container
             * @return Current size of the container
             *
             * This function only returns the size of the container (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the container
             * @return The absolute size of the container
             *
             * The absolute size includes the size of the container, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the container
             * @param width New width of the container
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the container relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * container->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the container while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the container
             * @param height New height of the container
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the container relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * container->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the container while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Get the type of the container
             * @return The type of the container
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the container with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the container currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the container
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the container with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the container currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the container
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
             * @brief Show or hide a container
             * @param visible True to show or false to hide
             *
             * If the container is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The container is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the container is visible or not
             * @return True if the container is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the container
             *
             * This function will hide the container if its currently
             * visible and vice versa
             * 
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the container
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the container, false if
             *         coordinates do not lie inside the container
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the container
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the container is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the container
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the container is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the container relative to the
             *        size of its parent
             * @param x New x coordinate of the container
             * @param y New y coordinate of the container
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * container->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the container is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the container
             * @return Current position of the container
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the container
             * @return The absolute position of the container
             * 
             * Unlike getPosition, this function returns the absolute 
             * position of the top-left point of the container instead 
             * of the relative position to its parent
             * 
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the container
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the container is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the container
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the container,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the container
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the container
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the container
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the container by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the container,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the container by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the container,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the container
             * @return Current scale of the container
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the container
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the container defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the container, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the container is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the container
             * @param origin New origin
             *
             * The origin of the container defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the container, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the container is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the container
             * @return Local origin of the container
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the container by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the container,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the container by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the container,
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
            std::shared_ptr<tgui::TabContainer> tabContainer_; //!< Pointer to third party container
            std::unordered_map<std::size_t, std::shared_ptr<Panel>> panels_;
            std::shared_ptr<TabsRenderer> renderer_; //!< Tabs renderer
        };
    }
}

#endif //IME_TABSCONTAINER_H
