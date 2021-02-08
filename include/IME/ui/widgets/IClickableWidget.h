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

#ifndef IME_ICLICKABLEWIDGET_H
#define IME_ICLICKABLEWIDGET_H

#include "IME/Config.h"
#include "IWidget.h"
#include <string>

namespace ime {
    namespace ui {
        /**
         * @brief Interface for clickable widgets
         */
        class IME_API IClickableWidget : public IWidget {
        public:
            using sharedPtr = std::shared_ptr<IClickableWidget>; //!< Shared widget pointer

            /**
             * @brief Enable or disable the widget
             * @param isEnable Set true to enable the widget, false to
             *        disable the widget
             *
             * The widget is enabled by default
             *
             * @note Disabling the widget cancels all the interaction events
             */
            virtual void setEnabled(bool isEnable) = 0;

            /**
              * @brief Check if widget is enabled or disabled
              * @return True if widget is enabled, false if widget is disabled
              */
            virtual bool isEnabled() const = 0;

            /**
             * @brief Disable widget if its currently enabled and vice versa
             */
            virtual void toggleEnabled() = 0;

            /**
             * @brief Focus or unfocus widget
             * @param isFocused True to focus or false to unfocus widget
             */
            virtual void setFocused(bool isFocused) = 0;

            /**
             * @brief Check if widget is focused or not
             * @return True if widget is focused. Otherwise, false
             */
            virtual bool isFocused() const = 0;
        };
    }
}

#endif // IME_ICLICKABLEWIDGET_H
