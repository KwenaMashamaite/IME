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

#include <IME/ui/widgets/IWidget.h>
#include "IME/utility/Utils.h"

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
    }

    std::string bindLeft(std::shared_ptr<ui::IWidget> widget){
        return tgui::bindLeft(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindTop(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindTop(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindWidth(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindWidth(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindHeight(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindHeight(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindRight(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindRight(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindBottom(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindBottom(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindPosition(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindPosition(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindSize(std::shared_ptr<ui::IWidget> widget) {
        return tgui::bindSize(widget->getInternalPtr()).toString().toAnsiString();
    }

    std::string bindMin(const std::string& value1, const std::string& value2) {
        return tgui::bindMin(value1.c_str(), value2.c_str()).toString().toAnsiString();
    }

    std::string bindMax(const std::string& value1, const std::string& value2) {
        return tgui::bindMax(value1.c_str(), value2.c_str()).toString().toAnsiString();
    }
}
