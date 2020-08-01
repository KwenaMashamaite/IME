#ifndef CONTAINER_H
#define CONTAINER_H

#include "common/Common.h"
#include <string>

using Common::Position;
using Common::Dimensions;

namespace Gui {
    class Container {
    public:
        /**
         * @brief Set the title
         * @param title Title to set
         */
        void setTitle(const std::string &title);

        void setTitleFont(const std::string& font);

        void setTitleTextSize(unsigned int textSize);

        void setTitleAlignment(TextAlignment);

        void insert(const std::string& name, std::unique_ptr<UIElement> uiElem);

        void remove(const uiElemName);

        void setPosition(int x, int y);

        void setPosition(const Position &position);

        void setDimension(const Dimensions dimensions);

        Position getPosition() const;

        Dimensions getDimensions() const;

    };
}
#endif
