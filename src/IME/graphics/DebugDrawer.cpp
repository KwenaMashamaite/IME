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

// Parts of the code below was taken from
// https://github.com/MrPlow442/Box2D-SFML2-Debug-Draw/blob/master/Box2D-SFML%20Debug%20Draw/SFMLDebugDraw.cpp
// and modified to work with Box2d 2.4.1 and SFML 2.5.1

// Debug draw for Box2D 2.2.1 - 2.3.0 for SFML 2.0 - SFMLDebugDraw.cpp
// Copyright (C) 2013  Matija Lovrekovic
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <SFML/Graphics/Vertex.hpp>
#include "DebugDrawer.h"
#include "IME/graphics/shapes/CircleShape.h"
#include "IME/graphics/shapes/ConvexShape.h"
#include "IME/graphics/Window.h"
#include "../utility/Helpers.h"
#include "../graphics/WindowImpl.h"

namespace ime::priv {
    namespace {
        Colour convertToOwnColour(const b2Color &colour) {
            // Box2d colour has their rgba components in the range [0, 1] and our use the range [0, 255]
            return {static_cast<unsigned int>(colour.r * 255),
                    static_cast<unsigned int>(colour.g * 255),
                    static_cast<unsigned int>(colour.b * 255),
                    static_cast<unsigned int>(colour.a * 255)};
        }

        CircleShape createCircle(float radius, const b2Vec2& position, const b2Color& fillColour) {
            auto circle = CircleShape(utility::metresToPixels(radius));
            circle.setOrigin(circle.getLocalBounds().width / 2.0f, circle.getLocalBounds().height / 2.0f);
            circle.setPosition(utility::metresToPixels({position.x, position.y}));
            circle.setFillColour(convertToOwnColour(fillColour));
            circle.setOutlineThickness(-1.f);
            circle.setOutlineColour(convertToOwnColour(fillColour));
            return circle;
        }

        ConvexShape createPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &fillColour, const b2Color &outlineColour) {
            auto polygon = ConvexShape(vertexCount);
            for (auto i = 0; i < vertexCount; ++i)
                polygon.setPoint(i, {utility::metresToPixels(vertices[i].x),
                    utility::metresToPixels(vertices[i].y)});

            polygon.setFillColour(convertToOwnColour(fillColour));
            polygon.setOutlineThickness(-1.0f);
            polygon.setOutlineColour(convertToOwnColour(outlineColour));
            return polygon;
        }
    }

    DebugDrawer::DebugDrawer(Window &renderWindow) :
        window_{renderWindow}
    {}

    void DebugDrawer::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &colour) {
        window_.draw(createPolygon(vertices, vertexCount, {0, 0, 0, 0}, colour));
    }

    void DebugDrawer::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &colour) {
        window_.draw(createPolygon(vertices, vertexCount, {colour.r, colour.g, colour.b, 60.0f / 255.0f}, colour));
    }

    void DebugDrawer::DrawCircle(const b2Vec2 &center, float radius, const b2Color &colour) {
        auto circle = createCircle(radius, center, colour);
        circle.setOutlineThickness(-1.f);
        window_.draw(circle);
    }

    void DebugDrawer::DrawSolidCircle(const b2Vec2 &center, float radius, const b2Vec2 &axis, const b2Color &colour) {
        auto circle = createCircle(radius, center, {colour.r, colour.g, colour.b, 60.0f / 255.0f});
        circle.setOutlineThickness(1.f);
        circle.setOutlineColour(convertToOwnColour(colour));
        window_.draw(circle);

        b2Vec2 endPoint = center + radius * axis;
        DrawSegment(center, endPoint, colour);
    }

    void DebugDrawer::DrawSegment(const b2Vec2 &startPoint, const b2Vec2 &endPoint, const b2Color &colour) {
        sf::Vertex line[] = {
            sf::Vertex({utility::metresToPixels(startPoint.x), utility::metresToPixels(startPoint.y)}, utility::convertToSFMLColour(convertToOwnColour(colour))),
            sf::Vertex({utility::metresToPixels(endPoint.x), utility::metresToPixels(endPoint.y)}, utility::convertToSFMLColour(convertToOwnColour(colour))),
        };

        window_.getImpl()->getSFMLWindow().draw(line, 2, sf::Lines);
    }

    void DebugDrawer::DrawTransform(const b2Transform &transform) {
        auto lineLength = 0.4f;

        b2Vec2 xAxis = transform.p + lineLength * transform.q.GetXAxis();
        DrawSegment(transform.p, xAxis, {1, 0, 0, 1});

        b2Vec2 yAxis = transform.p + lineLength * transform.q.GetYAxis();
        DrawSegment(transform.p, yAxis, {0, 1, 0, 1});
    }

    void DebugDrawer::DrawPoint(const b2Vec2 &point, float, const b2Color &colour) {
        auto p = sf::Vertex({utility::metresToPixels(point.x), utility::metresToPixels(point.y)}, utility::convertToSFMLColour(convertToOwnColour(colour)));
        window_.getImpl()->getSFMLWindow().draw(&p, 1, sf::Points);
    }

    DebugDrawer::~DebugDrawer() = default;
}
