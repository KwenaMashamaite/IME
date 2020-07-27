#include "IME/core/EntityCollisionManager.h"
#include "IME/core/IEntity.h"

namespace IME {
    void EntityCollisionManager::onCollision(std::string &event,
        Callback<std::shared_ptr<IEntity>, std::shared_ptr<IEntity>> callback)
    {
        eventEmitter_.addEventListener(event, std::move(callback));
    }

    void EntityCollisionManager::update() {
        for (auto& [event, entities] : entities_){
            auto& [entityOne, entityTwo] = entities;
            if (entityOne->isCollideWith(*entityTwo))
                eventEmitter_.emit(event, entityOne, entityTwo); //Notify collision event listeners
        }
    }

    bool EntityCollisionManager::registerEntities(std::string &event,
       std::shared_ptr<IEntity> entityOne, std::shared_ptr<IEntity> entityTwo)
    {
        if (eventEmitter_.hasEvent(event))
            return false;
        return entities_.insert(std::pair(event, std::pair(entityOne, entityTwo))).second;
    }

    bool EntityCollisionManager::isCollisionBetween(
        std::shared_ptr<IEntity> entityOne, std::shared_ptr<IEntity> entityTwo) const
    {
        if (entityOne && entityTwo) {
            return entityOne->getPosition().x + entityOne->getBoundingRect().width >= entityTwo->getPosition().x
               && entityOne->getPosition().x <= entityTwo->getPosition().x + entityTwo->getBoundingRect().width
               && entityOne->getPosition().y + entityOne->getBoundingRect().height >= entityTwo->getPosition().y
               && entityOne->getPosition().y <= entityTwo->getPosition().y + entityTwo->getBoundingRect().height;
        }
        return false;
    }

    void EntityCollisionManager::onCollision(
        std::shared_ptr<IEntity> entityOn, std::shared_ptr<IEntity> entityTwo,
        Callback<std::shared_ptr<IEntity>, std::shared_ptr<IEntity>> callback) const
    {
        if (isCollisionBetween(entityOn, entityTwo) && callback)
            callback(entityOn, entityTwo);
    }

    void EntityCollisionManager::onCollision(std::shared_ptr<IEntity> entityOne,
         std::shared_ptr<IEntity> entityTwo, Callback<> callback) const
    {
        if (isCollisionBetween(entityOne, entityTwo) && callback)
            callback();
    }
}