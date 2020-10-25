

#ifndef STRUCTS_H
#define STRUCTS_H

namespace IME {
    /**
      * @brief Represents the whitespace around the borders
      *        of the GUI widget
      */
    struct Margin {
        float left = 0.0f;
        float top = 0.0f;
        float right = 0.0f;
        float bottom = 0.0f;
    };

    /**
     * @brief Represents the spacing between the
     *        text and the border of the GUI widget
     */
    struct Padding {
        float left = 0.0f;
        float top = 0.0f;
        float right = 0.0f;
        float bottom = 0.0f;
    };

    struct Borders {
        float left = 0.0f;
        float top = 0.0f;
        float right = 0.0f;
        float bottom = 0.0f;
    };
}

#endif
