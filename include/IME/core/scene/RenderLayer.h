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

#ifndef IME_RENDERLAYER_H
#define IME_RENDERLAYER_H

#include "IME/Config.h"
#include "IME/core/object/Object.h"
#include <memory>
#include <map>

namespace ime {
    class Drawable;
    class GameObject;

    /// @internal
    namespace priv {
        class RenderTarget;
    }

    /**
     * @brief A layer for drawable entities
     *
     * Typically you add objects that should be drawn together to the
     * same layer. The order in which render layers are rendered is
     * specified in the RenderLayerContainer. Objects in the same layer
     * can also be sorted. For example, you may have a background layer
     * which has mountains, trees and valleys. However you don't want the
     * objects to be drawn non-deterministically. You can specify which
     * objects are drawn over which and which objects are drawn under which
     * by specifying the render order of the object when adding it to the
     * layer. Objects with the lowest render order are drawn first whilst
     * objects with the highest render order are drawn last. When objects
     * have the same render order, the object that was added first to the
     * layer will be rendered first.
     *
     * By default, all objects have the same render order, as a result, they
     * are drawn in the order in which they were added to the layer
     *
     * A layer is not instantiated directly but rather using a
     * RenderLayerContainer
     */
    class IME_API RenderLayer : public Object {
    public:
        using Ptr = std::shared_ptr<RenderLayer>; //!< Shared render layer pointer

        /**
         * @brief Copy constructor
         */
        RenderLayer(const RenderLayer&) = delete;

        /**
         * @brief Copy assignment operator
         */
        RenderLayer& operator=(const RenderLayer&) = delete;

        /**
         * @brief Move constructor
         */
        RenderLayer(RenderLayer&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        RenderLayer& operator=(RenderLayer&&) noexcept = default;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set whether or not the layer should be drawn by the scene
         * @param render True to have the layer drawn by the scene otherwise
         *               false
         *
         * By default the layer is drawable
         */
        void setDrawable(bool render);

        /**
         * @brief Check whether or not the layer is drawn by the scene
         * @return True if drawn by the scene, otherwise false
         *
         * @see setDrawable
         */
        bool isDrawable() const;

        /**
         * @brief Toggle the draw state of the layer
         *
         * This function will set the layer to drawable if its currently not
         * drawable and vice versa
         *
         * @see setDrawable
         */
        void toggleDrawable();

        /**
         * @brief Get the index of the layer in the RenderLayerContainer
         * @return The index of the layer in the RenderLayerContainer
         *
         * The index indicates the render order of the layer. The bigger the
         * index the further away the layer is from the foreground. The layer
         * with the an index of 0 is always the foreground layer and all other
         * layers are rendered behind it
         */
        unsigned int getIndex() const;

        /**
         * @brief Get the name of the layer
         * @return The name of the layer
         */
        const std::string& getName() const;

        /**
         * @brief Add a drawable to the layer
         * @param drawable The drawable to be added
         * @param renderOrder The layer level render order of the drawable
         *
         * The render order determines which game objects get rendered
         * first and which game objects get rendered last in the layer.
         * Therefore the order in which drawables are added to the layer
         * does not necessarily matter. Drawables with the smallest render
         * order are be rendered first. Note that multiple drawables can
         * have the same render order, in such a case the drawables will be
         * drawn in the order in which they were added to the layer
         *
         * By default, all drawables have the same render order of 0
         *
         * @warning Th render layer keeps a reference to the drawable,
         * therefore, it must remain alive for as long as it is used by the
         * render layer
         */
        void add(const Drawable& drawable, int renderOrder = 0);

        /**
         * @brief Check if the render layer has a given drawable or not
         * @param drawable The drawable to be checked
         * @return True if the render layer has the drawable, otherwise false
         *
         * When a render layer "has" a drawable, it means that the drawable
         * is rendered by that layer to the render window
         */
        bool has(const Drawable& drawable) const;

        /**
         * @brief Remove a drawable from the render layer
         * @param drawable The drawable to be removed
         * @return True if the drawable was removed, otherwise false
         *
         * When a drawable is removed from the render layer, it will no longer
         * be rendered by the scene, hence it won't appear on the game window
         */
        bool remove(const Drawable& drawable);

        /**
         * @brief Remove all drawables from the render layer
         */
        void removeAll();

        /**
         * @brief Get the number of drawables rendered by the layer
         * @return The number of drawables rendered by the layer
         */
        std::size_t getCount() const;

        /**
         * @internal
         * @brief Render all the objects in this layer
         * @param window The render window to render objects on
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void render(priv::RenderTarget& window) const;

        /**
         * @brief Destructor
         */
        ~RenderLayer() override;

    private:
        /**
         * @brief Constructor
         * @param index Index of the layer
         * @param name The name of the layer
         */
        RenderLayer(unsigned int index, const std::string& name);

        /**
         * @brief Change the index of the layer
         * @param index The new index of the layer
         */
        void setIndex(unsigned int index);

        /**
         * @brief Remove destruction handlers registered on the drawable
         */
        void removeDestructionHandlers();

    private:
        unsigned int index_;               //!< The index of the layer in the render layer container
        std::string name_;                 //!< The name of the layer
        bool shouldRender_;                //!< A flag indicating whether the layer should be rendered or not
        friend class RenderLayerContainer; //!< Needs access to constructor

        using DrawableRef = std::reference_wrapper<const Drawable>;
        using DrawableIdPair = std::pair<DrawableRef, int>;
        std::multimap<int, DrawableIdPair> drawables_; //!< Stores a drawable along with its render order
    };
}

#endif //IME_RENDERLAYER_H
