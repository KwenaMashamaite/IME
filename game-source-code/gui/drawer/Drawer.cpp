#include "Drawer.h"
#include "entity/Entity.h"
#include "resources/ResourceManager.h"
#include <algorithm>
#include <SFML/Graphics.hpp>

Gui::Drawer::Drawer(Gui::Window &renderTarget) : renderTarget_(renderTarget)
{}

void Gui::Drawer::drawEntity(const std::shared_ptr<Entity> &entity) {
    if(entity && entity->isAlive()) {
        auto entitySprite = sf::Sprite(ResourceManager::getTexture(entity->getTexture()));
        entitySprite.setOrigin(entitySprite.getGlobalBounds().width,
            entitySprite.getGlobalBounds().height);

        switch (entity->getDirection()) {
            case IEntity::Direction::Left:
                entitySprite.rotate(-90.0f);
                break;
            case IEntity::Direction::Right:
                entitySprite.rotate(90.0f);
                break;
            case IEntity::Direction::Up:
                entitySprite.setOrigin(0.0f, entitySprite.getGlobalBounds().height);
                break;
            case IEntity::Direction::Down:
                entitySprite.rotate(180.0f);
                break;
        }

        entitySprite.setPosition(entity->getPosition().x, entity->getPosition().y);
        renderTarget_.draw(entitySprite);
    }
}

void Gui::Drawer::drawEntities(const std::initializer_list<std::shared_ptr<Entity>> &entities) {
    std::for_each(entities.begin(), entities.end(),
        [this](const std::shared_ptr<Entity> &entity){
            drawEntity(entity);
        }
    );
}

void Gui::Drawer::drawBackground(const std::string &backgroundTexture) {
    auto background = sf::Sprite(ResourceManager::getTexture(backgroundTexture),
    	sf::IntRect(0, 0, 
            renderTarget_.getDimensions().width, 
            renderTarget_.getDimensions().height)
        );
    renderTarget_.draw(background);
}
