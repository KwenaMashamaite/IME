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

#include "IME/Config.h"
#include "IME/ui/widgets/WidgetContainer.h"
#include "IME/ui/renderers/ScrollablePanelRenderer.h"

namespace ime {
    namespace ui {
        /**
         * @brief A widget container that has a background colour optional
         *        borders and is scrollable
         */
        class IME_API ScrollablePanel : public WidgetContainer {
        public:
            using sharedPtr = std::shared_ptr<ScrollablePanel>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const ScrollablePanel>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            ScrollablePanel(ScrollablePanel&&);

            /**
             * @brief Move assignment operator
             */
            ScrollablePanel& operator=(ScrollablePanel&&);

            /**
             * @brief Create a new Panel widget
             * @param width Width of the panel relative to the size of its
             *        parent
             * @param height Height of the panel relative to the size of its
             *        parent
             * @param contentSize Size of the content area for which the
             *              scrollbars will appear if larger than the size
             * @return The new Panel
             *
             * When @a contentSize is set to (0,0), the content size is
             * determined by the child widgets of the panel.
             *
             * The relative size is specified in percentages as shown:
             *
             * @code
             * Panel::create({"50%", "20%"});
             * @endcode
             *
             * By default, the new panel is the same size as its parent
             */
            static sharedPtr create(const std::string& width = "100%",
                const std::string& height = "100%", Vector2f contentSize = {0, 0});

            /**
             * @brief Create a copy of another panel
             * @param other The panel to copy
             * @param shareRenderer True if the new panel should have the
             *          same renderer as the copied panel
             * @return The new panel widget
             *
             * When the panels share a renderer, changes in a render
             * property of one of the panels automatically reflect on
             * the other panel, otherwise each panel has its own renderer
             * and changes in render properties are isolated to the specific
             * panel.
             *
             * @note when the panels don't share a render, the renderer of
             * the new panel widget will initially have the properties of
             * the copied panel such that the two look the same after this
             * function returns
             *
             * By default, the panels share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Get the panels renderer
             * @return The panels renderer
             *
             * The renderer gives access to functions that determine how the
             * panel is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            ScrollablePanelRenderer::sharedPtr getRenderer();
            const ScrollablePanelRenderer::sharedPtr getRenderer() const;

            /**
             * @brief Set the size available for child widgets
             * @param size The inner size of the container
             *
             * If the content size is larger than the size of the panel then
             * scrollbars will be displayed. When the content size is (0,0),
             * which is the default, then the content size is determined by
             * the child widgets
             */
            void setContentSize(Vector2f size);

            /**
             * @brief Get the size available for child widgets
             * @return The inner size of the container
             */
            Vector2f getContentSize() const;

            /**
             * @brief Get the amount of pixels the child widgets have been
             *        shifted by in order to display the scrollbars
             * @return The offset pixels
             */
            Vector2f getContentOffset() const;

            /**
             * @brief Get the width of the scrollbars
             * @return The width of the scrollbars
             */
            float getScrollbarWidth() const;

            /**
             * @brief Change the vertical scroll step
             * @param scrollAmount The scroll step
             *
             * The vertical scroll step is how much the scroll bar moves up or
             * down when the panel is scrolled or when one of the vertical
             * scrollbar arrows is pressed
             */
            void setVerticalScrollStep(unsigned int step);

            /**
             * @brief Get the vertical scroll step
             * @return The vertical scroll step
             *
             * @see setVerticalScrollStep
             */
            unsigned int getVerticalScrollStep() const;

            /**
             * @brief Change the horizontal scroll step
             * @param scrollAmount The new horizontal scroll step
             *
             * The horizontal scroll step is how much the scroll bar moves
             * left or right when the panel is scrolled or when one of the
             * horizontal scrollbar arrows is pressed
             */
            void setHorizontalScrollStep(unsigned int step);

            /**
             * @brief Get the horizontal scroll step
             * @return The horizontal scroll step
             *
             * @see setHorizontalScrollStep
             */
            unsigned int getHorizontalScrollStep() const;

            /**
             * @brief Set the thumb position of the vertical scrollbar
             * @param value The new position of the vertical thumb
             */
            void setVerticalThumbValue(unsigned int value);

            /**
             * @brief Get the thumb position of the vertical scrollbar
             * @return The thumb position of the vertical scrollbar
             */
            unsigned int getVerticalThumbValue() const;

            /**
             * @brief Set the thumb position of the horizontal scrollbar
             * @param value The new position of the horizontal thumb
             */
            void setHorizontalThumbValue(unsigned int value);

            /**
             * @brief Get the thumb position of the horizontal scrollbar
             * @return The thumb position of the horizontal scrollbar
             */
            unsigned int getHorizontalThumbValue() const;

            /**
             * @brief Get the type of the panel
             * @return The type of the panel
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~ScrollablePanel();

        private:
            /**
             * @brief Constructor
             * @param width Width of the panel relative to the size of its
             *              parent
             * @param height Height of the panel relative to the size of its
             *               parent
             * @param contentSize Size of the content area for which the
             *              scrollbars will appear if larger than the size
             *
             * When @a contentSize is set to (0,0), the content size is
             * determined by the child widgets of the panel.
             *
             * The relative size is specified in percentages as shown:
             *
             * @code
             * Panel({"50%", "20%"});
             * @endcode
             *
             * By default, the panel is the same size as its parent
             */
            explicit ScrollablePanel(const std::string& width = "100%",
                const std::string& height = "100%", Vector2f contentSize = {0, 0});

        private:
            class Impl;
            std::unique_ptr<Impl> pimpl_;
        };
    }
}

