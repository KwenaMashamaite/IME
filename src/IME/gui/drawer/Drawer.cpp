#include "IME/gui/drawer/Drawer.h"
#include "IME/core/resources/ResourceManager.h"
#include <algorithm>
#include <SFML/Graphics.hpp>

namespace IME::Gui {
    Drawer::Drawer(Window &renderTarget) : renderTarget_(renderTarget)
    {}

    void Drawer::drawEntity(const EntityAnimatorPair &entityAnimatorPair) {
        auto entity = entityAnimatorPair.first;
        auto entityAnimator = entityAnimatorPair.second;
        if (entity && entity->isAlive()) {
            auto entitySprite = entityAnimator.getCurrentAnimSprite();
            auto entityOrientationAngle = [&entity]() {
                switch (entity->getDirection()) {
                    case IEntity::Direction::Left:return -90.0f;
                    case IEntity::Direction::Right:return 90.0f;
                    case IEntity::Direction::Up:return 0.0f;
                    case IEntity::Direction::Down:return 180.0f;
                }
            }();

            if (entityOrientationAngle == 0.0f)
                entitySprite.setOrigin(0.0f, entitySprite.getGlobalBounds().height);
            else
                entitySprite.setOrigin(entitySprite.getGlobalBounds().width,
                    entitySprite.getGlobalBounds().height);

            entitySprite.rotate(entityOrientationAngle);
            entitySprite.setPosition(entity->getPosition().x, entity->getPosition().y);
            renderTarget_.draw(entitySprite);
        }
    }

    void Drawer::drawEntities(const std::initializer_list<EntityAnimatorPair> &entityAnimatorPairs) {
        std::for_each(entityAnimatorPairs.begin(), entityAnimatorPairs.end(),
            [this](const EntityAnimatorPair &entityAnimatorPair){
                drawEntity(entityAnimatorPair);
            }
        );
    }

    void Drawer::drawBackground(const std::string &backgroundTexture) {
        auto background = sf::Sprite(ResourceManager::getTexture(backgroundTexture),
            sf::IntRect(0, 0,
                renderTarget_.getDimensions().width,
                renderTarget_.getDimensions().height)
            );
        renderTarget_.draw(background);
    }
}