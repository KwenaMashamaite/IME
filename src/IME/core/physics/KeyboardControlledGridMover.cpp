#include "IME/core/physics/KeyboardControlledGridMover.h"
#include "IME/core/entity/IMovable.h"
#include <utility>

namespace IME {
    KeyboardControlledGridMover::KeyboardControlledGridMover(TileMap &tileMap, std::shared_ptr<IME::Entity> target)
        : gridMover_(tileMap, target), trigger_(MovementTrigger::None), onTriggerHandlerId_{-1}
    {
        gridMover_.onDestinationReached([this](float, float) {
            if (auto& [changeDir, newDir] = newDir_; changeDir) { //If a direction switch was requested while a key was pressed
                changeDir = false;
                gridMover_.requestDirectionChange(newDir);
            }
        });
    }

    void KeyboardControlledGridMover::setTarget(KeyboardControlledGridMover::EntityPtr target) {
        gridMover_.setTarget(target);
    }

    KeyboardControlledGridMover::EntityPtr KeyboardControlledGridMover::getTarget() const {
        return gridMover_.getTarget();
    }

    void KeyboardControlledGridMover::setMovementTrigger(MovementTrigger trigger) {
        if (trigger_ != trigger) {
            trigger_ = trigger;
            if (trigger_ == MovementTrigger::None && onTriggerHandlerId_ != -1) {
                keyboard_.removeEventListener(Input::Keyboard::Event::KeyDown, onTriggerHandlerId_);
                keyboard_.removeEventListener(Input::Keyboard::Event::KeyUp, onTriggerHandlerId_);
                onTriggerHandlerId_ = -1;
                return;
            } else if (trigger_ == MovementTrigger::OnKeyDown)
                keyboard_.removeEventListener(Input::Keyboard::Event::KeyDown, onTriggerHandlerId_);
            else
                keyboard_.removeEventListener(Input::Keyboard::Event::KeyUp, onTriggerHandlerId_);
            attachInputEventListeners();
        }
    }

    MovementTrigger KeyboardControlledGridMover::getMovementTrigger() const {
        return trigger_;
    }

    void KeyboardControlledGridMover::setKeys(Input::Keyboard::Key leftKey, Input::Keyboard::Key rightKey,
        Input::Keyboard::Key upKey, Input::Keyboard::Key downKey)
    {
        movementKeys_.left = leftKey;
        movementKeys_.right = rightKey;
        movementKeys_.up = upKey;
        movementKeys_.down = downKey;
        attachInputEventListeners();
    }

    void KeyboardControlledGridMover::attachInputEventListeners() {
        static auto moveEntity = [this](Input::Keyboard::Key key) {moveTarget(key);};
        if (trigger_ == MovementTrigger::OnKeyDown)
            onTriggerHandlerId_ = keyboard_.onKeyDown(moveEntity);
        else if (trigger_ == MovementTrigger::OnKeyUp)
            onTriggerHandlerId_ = keyboard_.onKeyUp(moveEntity);
    }

    void KeyboardControlledGridMover::moveTarget(Input::Keyboard::Key key) {
        auto targetDirection = IME::Direction::None;
        if (key == movementKeys_.left)
            targetDirection = IME::Direction::Left;
        else if (key == movementKeys_.right)
            targetDirection = IME::Direction::Right;
        else if (key == movementKeys_.up)
            targetDirection = IME::Direction::Up;
        else if (key == movementKeys_.down)
            targetDirection = IME::Direction::Down;
        else
            return;

        if (targetDirection != gridMover_.getTarget()->getDirection() && gridMover_.isTargetMoving()) {
            newDir_.first = true;
            newDir_.second = targetDirection;
        } else
            gridMover_.requestDirectionChange(targetDirection);
    }

    bool KeyboardControlledGridMover::isTargetMoving() const {
        return gridMover_.isTargetMoving();
    }

    int KeyboardControlledGridMover::onGridBorderCollision(Callback<> callback) {
        return gridMover_.onGridBorderCollision(std::move(callback));
    }

    void KeyboardControlledGridMover::handleEvent(sf::Event event) {
        keyboard_.handleEvent(event);
    }

    void KeyboardControlledGridMover::update(float deltaTime) {
        gridMover_.update(deltaTime);
    }

    void KeyboardControlledGridMover::teleportTargetToDestination() {
        gridMover_.teleportTargetToDestination();
    }

    int KeyboardControlledGridMover::onDestinationReached(Callback<float, float> callback) {
        return gridMover_.onDestinationReached(std::move(callback));
    }

    int KeyboardControlledGridMover::onObstacleCollision(Callback<KeyboardControlledGridMover::EntityPtr,
            KeyboardControlledGridMover::EntityPtr> callback)
    {
        return gridMover_.onObstacleCollision(std::move(callback));
    }

    int KeyboardControlledGridMover::onCollectableCollision(Callback<KeyboardControlledGridMover::EntityPtr,
            KeyboardControlledGridMover::EntityPtr> callback)
    {
        return gridMover_.onCollectableCollision(std::move(callback));
    }

    int KeyboardControlledGridMover::onEnemyCollision(Callback<KeyboardControlledGridMover::EntityPtr,
            KeyboardControlledGridMover::EntityPtr> callback)
    {
        return gridMover_.onEnemyCollision(std::move(callback));
    }

    int KeyboardControlledGridMover::onPlayerCollision(Callback<KeyboardControlledGridMover::EntityPtr,
            KeyboardControlledGridMover::EntityPtr> callback)
    {
        return gridMover_.onPlayerCollision(std::move(callback));
    }
}
