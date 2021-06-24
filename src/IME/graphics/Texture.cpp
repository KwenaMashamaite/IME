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

#include "IME/graphics/Texture.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/graphics/RenderTarget.h"
#include "IME/graphics/RenderTargetImpl.h"
#include <SFML/Graphics/Texture.hpp>

namespace ime {
    struct Texture::Impl {
        Impl() :
            texture_{std::make_shared<sf::Texture>()},
            image_{nullptr}
        {}

        Impl(const std::string &filename, const UIntRect &area) :
            filename_{filename},
            texture_{std::make_shared<sf::Texture>()},
            image_{nullptr}
        {
            loadFromFile(filename, area);
        }

        Impl(const Impl& other) :
            filename_{other.filename_}
        {
            // Its expensive to copy sf::Texture, so instead we increase the
            // reference counter of other.texture_
            texture_ = other.texture_;

            if (texture_) {
                // A ime::Texture created and updated with the contents of priv::ime::RenderTarget's
                // will have a valid texture but the image_ member will be nullptr and the filename_
                // member will be an empty string. Otherwise if it was loaded from a file, all three
                // members will have valid values. So we suppress the exception because its not the
                // callers fault if the image cannot be loaded and it also not an error as mentioned
                // above
                try {
                    image_ = &ResourceManager::getInstance()->getImage(other.filename_);
                } catch (const ime::FileNotFound&) {
                    image_ = nullptr;
                }
            }
        }

        Impl& operator=(const Impl&) = default;
        Impl(Impl&&) noexcept = default;
        Impl& operator=(Impl&&) noexcept = default;

        bool create(unsigned int width, unsigned int height) {
            return texture_->create(width, height);
        }

        void loadFromFile(const std::string &filename, const UIntRect &area) {
            image_ = &ResourceManager::getInstance()->getImage(filename);

            auto sfArea = sf::IntRect {
                static_cast<int>(area.left), static_cast<int>(area.top),
                static_cast<int>(area.width),static_cast<int>(area.height)
            };

            texture_->loadFromImage(*image_, sfArea);
        }

        bool saveToFile(const std::string &filename) {
            return texture_->copyToImage().saveToFile(filename);
        }

        Vector2u getSize() const {
            return {texture_->getSize().x, texture_->getSize().y};
        }

        void setSmooth(bool smooth) {
            texture_->setSmooth(smooth);
        }

        bool isSmooth() const {
            return texture_->isSmooth();
        }

        void setRepeated(bool repeated) {
            texture_->setRepeated(repeated);
        }

        bool isRepeated() const {
            return texture_->isRepeated();
        }

        static unsigned int getMaximumSize() {
            return sf::Texture::getMaximumSize();
        }

        const std::string& getFilename() const {
            return filename_;
        }

        void update(const priv::RenderTarget &renderTarget, unsigned int x, unsigned y) {
            if (x == 0 && y == 0)
                texture_->update(renderTarget.getImpl()->getSFMLWindow());
            else
                texture_->update(renderTarget.getImpl()->getSFMLWindow(), x, y);
        }

        const sf::Texture& getSFMLTexture() const {
            return *texture_;
        }

        ~Impl() {
            image_ = nullptr;
        }

    private:
        std::string filename_;                  //!< Name of the image file on the disk
        std::shared_ptr<sf::Texture> texture_;  //!< Third party texture
        const sf::Image* image_;                //!< Constructs the texture
    }; // class Impl

    Texture::Texture() :
        pImpl_{std::make_unique<Impl>()}
    {}

    Texture::Texture(const std::string &filename, const UIntRect &area) :
        pImpl_{std::make_unique<Impl>(filename, area)}
    {}

    Texture::Texture(const Texture& other) :
        pImpl_{std::make_unique<Impl>(*other.pImpl_)}
    {}

    Texture &Texture::operator=(const Texture& rhs) {
        if (this != &rhs) {
            pImpl_ = std::make_unique<Impl>(*rhs.pImpl_);
        }

        return *this;
    }

    Texture::Texture(Texture&& rhs) noexcept :
        pImpl_{std::move(rhs.pImpl_)}
    {}

    Texture& Texture::operator=(Texture&& rhs) noexcept {
        if (this != &rhs) {
            pImpl_ = std::move(rhs.pImpl_);
        }

        return *this;
    }

    bool Texture::create(unsigned int width, unsigned int height) {
        return pImpl_->create(width, height);
    }

    bool Texture::create(const Vector2u &size) {
        return create(size.x, size.y);
    }

    void Texture::loadFromFile(const std::string &filename, const UIntRect &area) {
        pImpl_->loadFromFile(filename, area);
    }

    bool Texture::saveToFile(const std::string &filename) {
        return pImpl_->saveToFile(filename);
    }

    Vector2u Texture::getSize() const {
        return pImpl_->getSize();
    }

    void Texture::setSmooth(bool smooth) {
        pImpl_->setSmooth(smooth);
    }

    bool Texture::isSmooth() const {
        return pImpl_->isSmooth();
    }

    void Texture::setRepeated(bool repeated) {
        pImpl_->setRepeated(repeated);
    }

    bool Texture::isRepeated() const {
        return pImpl_->isRepeated();
    }

    unsigned int Texture::getMaximumSize() {
        return Impl::getMaximumSize();
    }

    const std::string &Texture::getFilename() const {
        return pImpl_->getFilename();
    }

    void Texture::update(const priv::RenderTarget &renderTarget, unsigned int x, unsigned int y) {
        pImpl_->update(renderTarget, x, y);
    }

    const sf::Texture &Texture::getInternalTexture() const {
        return pImpl_->getSFMLTexture();
    }

    Texture::~Texture() = default;
}
