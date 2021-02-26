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

#ifndef IME_SEPARATOR_H
#define IME_SEPARATOR_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/renderers/SeparatorRenderer.h"

namespace ime {
    namespace ui {
        /**
         * @brief A rectangle that can be used as a line to visually
         *        separate widgets from each other
         *
         * @note This widget just draws a line. It does not support dragging
         * to e.g enlarge or shrink a panel
         */
        class IME_API Separator : public Widget {
        public:
            using Ptr = std::shared_ptr<Separator>; //!< Shared widget pointer
            using ConstPtr = std::shared_ptr<const Separator>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            Separator(Separator&&);

            /**
             * @brief Move assignment operator
             */
            Separator& operator=(Separator&&);

            /**
             * @brief Create a new separator widget
             * @return The new separator separator
             */
            static Separator::Ptr create();

            /**
             * @brief Create a copy of another separator
             * @param other The separator to copy
             * @param shareRenderer True if the new separator should have the
             *          same renderer as the copied separator
             * @return The new separator widget
             *
             * When the separators share a renderer, changes in a render
             * property of one of the separators automatically reflect on
             * the other separator, otherwise each separator has its own renderer
             * and changes in render properties are isolated to the specific
             * separator.
             *
             * @note when the separators don't share a render, the renderer of
             * the new separator widget will initially have the properties of
             * the copied separator such that the two look the same after this
             * function returns
             *
             * By default, the separators share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static Separator::Ptr copy(Separator::ConstPtr other, bool shareRenderer = true);

            /**
             * @brief Get the separators renderer
             * @return The separators renderer
             *
             * The renderer gives access to functions that determine how the
             * separator is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            SeparatorRenderer::Ptr getRenderer();
            const SeparatorRenderer::Ptr getRenderer() const;

            /**
             * @brief Get the type of the separator
             * @return The type of the separator
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Separator();

        private:
            /**
            * @brief Constructor
            */
            Separator();
        };
    }
}

#endif //IME_SEPARATOR_H
