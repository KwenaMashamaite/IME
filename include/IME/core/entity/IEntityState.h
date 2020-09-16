/**
 * @brief Base class for entity states
 */

#ifndef IENTITYSTATE_H
#define IENTITYSTATE_H

#include <memory>

namespace IME {
    class Entity;

    class IEntityState {
    public:
        /**
         * @brief Construct object
         * @param target Target object for state object
         */
        IEntityState(std::shared_ptr<Entity> target) : target_(std::move(target)){}

        /**
         * @brief Update state
         */
        virtual void update() = 0;

        /**
         * @brief Reset state
         */
        virtual void reset() = 0;

        /**
         * @brief Called when state is switched to for the first time
         */
        virtual void onEnter() = 0;

        /**
         * @brief Called before state is destroyed
         */
        virtual void onExit() = 0;

        /**
         * @brief Called when the state is exited but not destroyed
         *
         * This happens when another state added while this stae is active
         */
        virtual void onPause() = 0;

        /**
         * @brief Called when state is resumed after being paused
         */
        virtual void onResume() = 0;

        /**
         * @brief Get the target object
         * @return The target object
         */
        std::shared_ptr<Entity> getTarget() const {
            return target_;
        }

    private:
        //Target object
        std::shared_ptr<Entity> target_;
    };
}

#endif
