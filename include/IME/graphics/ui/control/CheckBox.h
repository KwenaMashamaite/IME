/**
 *
 */

#ifndef IME_CHECKBOX_H
#define IME_CHECKBOX_H

#include "ClickableUIElement.h"
#include "Label.h"
#include "IME/graphics/Sprite.h"

namespace IME {
    namespace Graphics::UI {
        class CheckBox : public ClickableUIElement {
        public:
            CheckBox();

            void setChecked(bool isChecked);

            void toggleChecked();

            bool isChecked() const;

            std::string getType() const override;

            void draw(Window &renderTarget) override;

        public:

        private:
            Sprite sprite_;
            Label text_;
            bool isChecked_;
        };
    }
}
#endif //IME_CHECKBOX_H
