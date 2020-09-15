/**
 * @brief Interface for all game entities (players, projectiles, enemies etc...)
 */

#ifndef IENTITY_H
#define IENTITY_H

#include "IME/common/Dimensions.h"
#include "IME/common/Position.h"
#include "IME/core/event/EventEmitter.h"
#include "IEntityState.h"
#include <stack>
#include <string>
#include <memory>

namespace IME {
    class IEntity {
    public:
        /**
         * @brief Directions in which an entity can face
         */
        enum class Direction {
            None,
            Left,
            Right,
            Up,
            Down
        };

        /**
         * @brief Set the position of the entity
         * @param x New x coordinate of the entity
         * @param y New y coordinate of the entity
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the direction of the entity
         * @param dir new direction of the entity
         */
        void setDirection(Direction dir);

        /**
         * @brief Get the dimensions of the entity's bounding box
         * @return Dimensions of the entity's bounding box
         */
        Dimensions getBoundingRect() const;

        /**
         * @brief Set the alive state of the entity
         * @param isAlive True to set alive or false to kill
         */
        void setAlive(bool isAlive);

        /**
         * @brief Check if entity is alive or not
         * @return True if entity is alive, false if it's not alive
         */
         bool isAlive() const;

        /**
         * @brief Get the direction of the entity
         * @return Direction of the entity
         */
        Direction getDirection() const;

        /**
         * @brief Get the position of the entity
         * @return Position of the entity
         */
        Position getPosition() const;

        /**
         * @brief Get the type of the entity
         * @return The type of the entity
         */
        virtual std::string getType() = 0;

        /**
         * @brief Add an event listener to an entity event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is published
         * @return The event listeners identification number
         */
        template<typename ...Args>
        int onEvent(const std::string& event, Callback<Args...> callback);

        /**
         * @brief Remove an event listener form an entity event
         * @param event Event to remove event listener from
         * @param id Identification number of the event listener
         * @return True if the event listener was removed or false if no such
         *         event listener exists for the specified event
         */
        bool removeEventListener(const std::string& event, int id);

        /**
         * @brief Reset the entity
         */
        void reset();

        /**
         * @brief Update object
         *
         * This function will update the current state
         */
        void update();

        /**
         * @brief Add a state to the entity
         * @param state State to add
         *
         * This state will automatically become the active state upon being added
         */
        void pushState(std::shared_ptr<IEntityState> state);

        /**
         * @brief Remove the current state
         */
        void popState();

        /**
         * @brief Destructor
         */
        virtual ~IEntity() = default;

    protected:
        /**
         * @brief Publish an entity event
         * @param event Event to publish
         * @param args Arguments passed to event listeners
         */
        template<typename...Args>
        void publishEvent(const std::string& event, Args&&...args);

    private:
        //The entities state machine
        std::stack<std::shared_ptr<IEntityState>> states_;
        //The entities alive state
        bool isAlive_;
        //The entities bounding rectangle
        Dimensions boundingRect_;
        //The direction of the entity
        Direction direction_;
        //The position of the entity
        Position position_;
        //The event publisher of the entity
        EventEmitter eventEmitter_;
    };

    template<typename ...Args>
    inline int IEntity::onEvent(const std::string& event, Callback<Args...> callback) {
        return eventEmitter_.on(event, std::move(callback));
    }

    template<typename...Args>
    void IEntity::publishEvent(const std::string& event, Args&&...args) {
        eventEmitter_.emit(event, std::forward<Args>(args)...);
    }
}

#endif
