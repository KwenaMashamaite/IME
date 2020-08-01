#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "IME/event/EventEmitter.h"
#include <memory>

namespace IME {
    class IEntity;

    class EntityCollisionManager{
    public:
        using sharedEntityPtr = std::shared_ptr<IEntity>;

        /**
         * @brief Register entities to a collision event
         * @param event Name of the collision event
         * @param entityOne
         * @param entityTwo
         * @return True if the two entities were successfully registered or false
         *         if another collision with the same name already exists
         *
         * The collision event name must be unique so that entities
         */
        bool registerEntities(std::string& event, std::shared_ptr<IEntity> entityOne, std::shared_ptr<IEntity> entityTwo);

        bool isCollisionBetween(std::shared_ptr<IEntity> entityOn, std::shared_ptr<IEntity> entityTwo) const;

        void onCollision(std::shared_ptr<IEntity> entityOne, std::shared_ptr<IEntity> entityTwo,
             Callback<> callback) const;

        void onCollision(std::shared_ptr<IEntity> entityOn, std::shared_ptr<IEntity> entityTwo,
             Callback<std::shared_ptr<IEntity>, std::shared_ptr<IEntity>> callback) const;

        /**
         * @brief Check if any of the registered entities have collided
         *
         * If a collision is detected, event listeners for that collision will
         * be notified @see onCollision(std::string, Callback). This function
         * needs to be called as soon as all physics updates have been completed.
         * Calling the function at a later time may result in late collision
         * detection or missed collisions
         */
        void update();

        /**
         * @brief Add an event listener to a collision event
         * @param event Name of the collision event to add event listener to
         * @param callback Function to execute when the specified collision occurs
         *
         * @note Entities of interest must be registered prior to subscribing
         * to a collision event @see registerEntities() . The collision manager
         * will automatically detect if a collision has occurred and invoke the
         * callback with the entities that have collided with each other. The
         * arguments will be provided in the order in which they were registered
         * in:
         *
         * @example
         *  @code collisionMngr.registerEntities("playerEnemyCollision", player, enemy);
         *  The callback will be invoked like so: callback(player, enemy) or vice
         *  versa if the order was reversed in registerEntities()
         */
        void onCollision(std::string& event, Callback<std::shared_ptr<IEntity>, std::shared_ptr<IEntity>> callback);

    private:
        using EntityPair = std::pair<std::shared_ptr<IEntity>, std::shared_ptr<IEntity>>;
        //
        std::unordered_map<std::string, EntityPair> entities_;
        //Event publisher for collision events
        EventEmitter eventEmitter_;
    };
}

#endif
