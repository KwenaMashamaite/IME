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

#ifndef IME_DEBUGDRAWER_H
#define IME_DEBUGDRAWER_H

#include <box2d/b2_draw.h>

namespace ime {
    namespace priv {
        class RenderTarget;

        /**
        * @brief Debug draws physics entities (bodies, joints, AABB's etc...)
        */
        class DebugDrawer : public b2Draw {
        public:
            /**
            * @brief Construct the debug drawer
            * @param renderWindow The window to render on
            */
            explicit DebugDrawer(RenderTarget& renderWindow);

            /**
            * @brief Draw a polygon
            * @param vertices The vertices of the polygon
            * @param vertexCount The number of vertices of the polygon
            * @param colour The colour of the polygon
            */
            void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &colour) override;

            /**
            * @brief Draw a solid polygon
            * @param vertices The vertices of the polygon
            * @param vertexCount The number of vertices of the polygon
            * @param colour The colour of the polygon
            */
            void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &colour) override;

            /**
            * @brief Draw a circle
            * @param center The centre of the circle
            * @param radius Th radius of teh circle
            * @param colour The colour of the circle
            */
            void DrawCircle(const b2Vec2 &center, float radius, const b2Color &colour) override;

            /**
            * @brief Draw a solid circle
            * @param center The centre of the circle
            * @param radius The radius of the circle
            * @param axis
            * @param colour The colour of the circle
            */
            void DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &colour) override;

            /**
            * @brief Draw a line segment
            * @param startPoint The starting point of the line
            * @param endPoint The ending pit of the line
            * @param colour The colour of the line
            */
            void DrawSegment(const b2Vec2 &startPoint, const b2Vec2 &endPoint, const b2Color &colour) override;

            /**
            * @brief Draw a transform
            * @param transform The transform to be draw
            */
            void DrawTransform(const b2Transform &transform) override;

            /**
            * @brief Draw a point
            * @param point Point to be drawn
            * @param size The size of the point
            * @param color The colour of the point
            */
            void DrawPoint(const b2Vec2 &point, float size, const b2Color &colour) override;

            /**
            * @brief Destructor
            */
            ~DebugDrawer() override;

        private:
            RenderTarget& window_; //!< Debug render window
        };
    }
}


#endif //IME_DEBUGDRAWER_H
