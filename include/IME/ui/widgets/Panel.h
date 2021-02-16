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
#include "IME/ui/widgets/WidgetContainer.h"
#include "IME/ui/renderers/PanelRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A widget container that has a background colour and
         *        optional borders
         */
        class IME_API Panel : public WidgetContainer {
        public:
            using sharedPtr = std::shared_ptr<Panel>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Panel>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            Panel(Panel&&);

            /**
             * @brief Move assignment operator
             */
            Panel& operator=(Panel&&);

            /**
             * @brief Create a new Panel widget
             * @param width Width of the panel relative to the size of its
             *        parent
             * @param height Height of the panel relative to the size of its
             *        parent
             * @return The new Panel
             *
             * * The relative size is specified in percentages as shown:
             *
             * @code
             * Panel::create({"50%", "20%"});
             * @endcode
             * 
             * By default, the new panel is the same size as its parent
             */
            static sharedPtr create(const std::string& width = "100%",
                const std::string& height = "100%");

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
            PanelRenderer::sharedPtr getRenderer();
            const PanelRenderer::sharedPtr getRenderer() const;

            /**
             * @brief Get the type of the panel
             * @return The type of the panel
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Panel();

        private:
            /**
             * @brief Constructor
             * @param width Width of the panel relative to the size of its
             *        parent
             * @param height Height of the panel relative to the size of its
             *        parent
             *
             * The relative size is specified in percentages as shown:
             *
             * @code
             * Panel({"50%", "20%"});
             * @endcode
             *
             * By default, the panel is the same size as its parent
             */
            explicit Panel(const std::string& width = "100%", const std::string& height = "100%");
        };
    }
}

#endif //IME_PANEL_H
