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

#include "IME/core/grid/Grid2DRenderer.h"

namespace ime {
    Grid2DRenderer::Grid2DRenderer() :
        tileColour_{36, 37, 38},
        collidableTileColour_{120, 80, 39},
        gridLinesColour_{Colour::Grey},
        isVisible_{true}
    {}

    void Grid2DRenderer::setBackgroundTexture(const std::string &filename) {
        emit(Property{"backgroundTexture", filename});
    }

    void Grid2DRenderer::setTileColour(const Colour &colour) {
        if (tileColour_ != colour) {
            tileColour_ = colour;
            emit(Property{"tileColour", tileColour_});
        }
    }

    Colour Grid2DRenderer::getTileColour() const {
        return tileColour_;
    }

    void Grid2DRenderer::setCollidableTileColour(const Colour &colour) {
        if (collidableTileColour_ != colour) {
            collidableTileColour_ = colour;
            emit(Property{"collidableTileColour", collidableTileColour_});
        }
    }

    Colour Grid2DRenderer::getCollidableTileColour() const {
        return collidableTileColour_;
    }

    void Grid2DRenderer::setGridLineColour(const Colour &colour) {
        if (gridLinesColour_ != colour) {
            gridLinesColour_ = colour;
            emit(Property{"gridLineColour", gridLinesColour_});
        }
    }

    Colour Grid2DRenderer::getGridLineColour() const {
        return gridLinesColour_;
    }

    void Grid2DRenderer::setVisible(bool visible) {
        if (isVisible_ != visible) {
            isVisible_ = visible;
            emit(Property{"visible", isVisible_});
        }
    }

    bool Grid2DRenderer::isVisible() const {
        return isVisible_;
    }

    void Grid2DRenderer::toggleVisibility() {
        setVisible(!isVisible_);
    }

    void Grid2DRenderer::emit(const Property &property) {
        if (onPropertyChange_)
            onPropertyChange_(property);
    }

    void Grid2DRenderer::onPropertyChange(const Callback &callback) {
        onPropertyChange_ = callback;
    }
}
