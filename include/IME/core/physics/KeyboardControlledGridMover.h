/**
 * @brief Class that performs grid based movement on an entity using the keyboard
 *        as a movement trigger
 */

#ifndef KEYBOARDCONTROLLED_H
#define KEYBOARDCONTROLLED_H

#include "IME/core/input/Keyboard.h"
#include "IME/core/entity/Entity.h"
#include "GridMover.h"

namespace IME {
    enum class Trigger {
        OnKeyDown, //Continues to fire while key is held down
        OnKeyUp    //Only triggers when a key is released
    };

    class KeyboardControlledGridMover {
    public:
        /**
         * @brief Constructor
         * @param gridMover
         * @param trigger Set to onKeyDown to move entity whilst a key is held
         *        down or set to onKeyUp to move the entity only when a key is
         *
         * By default the movement is triggered when a set key (@see setKeys())
         * is released
         */
        KeyboardControlledGridMover(std::shared_ptr<GridMover> gridMover,
            std::shared_ptr<Entity> target,
            Trigger trigger = Trigger::OnKeyUp);

        /**
         * @brief Set the keys to move the entity in all four directions
         * @param leftKey Key to move entity left on trigger
         * @param rightKey Key to move entity right on trigger
         * @param upKey Key to move entity up on trigger
         * @param downKey Key to move entity down on trigger
         *
         * There are no set keys by default
         */
        void setKeys(Input::Keyboard::Key leftKey, Input::Keyboard::Key rightKey,
             Input::Keyboard::Key upKey, Input::Keyboard::Key downKey);

        /**
         * @brief Handle an event
         * @param event Event to handle
         */
        void handleEvent(sf::Event event);

        /**
         * @brief Update the target entities movement in the grid
         * @param deltaTime Time passed since entity movement was last updated
         */
        void update(float deltaTime);

        /**
         * @brief Teleport target destination
         */
        void teleportTargetToDestination();

    private:
        //Moves entity in the grid
        std::shared_ptr<GridMover> gridMover_;
        //Target moved in the grid
        std::shared_ptr<Entity> target_;
        //Movement trigger flag
        Trigger trigger_;
        //Handler id
        int onTriggerHandlerId_;
        //Input detector
        Input::Keyboard keyboard_;
        //
        std::pair<bool, Direction> newDir_;
    };
}

#endif
