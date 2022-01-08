////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/utility/Utils.h"
#include "IME/ui/widgets/Widget.h"
#include <TGUI/Widget.hpp>

namespace ime {
    namespace utility {
        float lerp(float min, float max, float ratio) {
            return (max - min) * ratio + min;
        }

        int generateRandomNum(int min, int max) {
            return createRandomNumGenerator(min, max)();
        }
    
        Colour generateRandomColour() {
            static auto gen_random_num_between_0_and_255 = createRandomNumGenerator(0, 255);
            return {static_cast<unsigned int>(gen_random_num_between_0_and_255()),
                    static_cast<unsigned int>(gen_random_num_between_0_and_255()),
                    static_cast<unsigned int>(gen_random_num_between_0_and_255())};
        }
    } // namespace utility

    std::string bindLeft(ui::Widget* widget){
        return tgui::bindLeft(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindTop(ui::Widget* widget) {
        return tgui::bindTop(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindWidth(ui::Widget* widget) {
        return tgui::bindWidth(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindHeight(ui::Widget* widget) {
        return tgui::bindHeight(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindRight(ui::Widget* widget) {
        return tgui::bindRight(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindBottom(ui::Widget* widget) {
        return tgui::bindBottom(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindPosition(ui::Widget* widget) {
        return tgui::bindPosition(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindSize(ui::Widget* widget) {
        return tgui::bindSize(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr())).toString().toStdString();
    }

    std::string bindMin(const std::string& value1, const std::string& value2) {
        return tgui::bindMin(value1.c_str(), value2.c_str()).toString().toStdString();
    }

    std::string bindMax(const std::string& value1, const std::string& value2) {
        return tgui::bindMax(value1.c_str(), value2.c_str()).toString().toStdString();
    }
}
