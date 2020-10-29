#include "IME/core/physics/KeyboardControlledGridMover.h"
#include "IME/core/entity/IMovable.h"
#include <utility>

namespace IME {
    KeyboardControlledGridMover::KeyboardControlledGridMover(
            std::shared_ptr<GridMover> gridMover, std::shared_ptr<IME::Entity> target, Trigger trigger)
        : gridMover_(std::move(gridMover)), target_(std::move(target)), trigger_(trigger), onTriggerHandlerId_(-1)
    {
        gridMover_->onDestinationReached([this](float, float) {
            if (newDir_.first) { //If a direction switch was requested while a key was pressed
                newDir_.first = false;
                gridMover_->requestDirectionChange(newDir_.second);
            }
        });
    }

    void KeyboardControlledGridMover::setKeys(Input::Keyboard::Key leftKey, Input::Keyboard::Key rightKey,
        Input::Keyboard::Key upKey, Input::Keyboard::Key downKey)
    {
        if (onTriggerHandlerId_ != -1) { //Keys already set
            if (trigger_ == Trigger::OnKeyDown)
                keyboard_.removeEventListener(Input::Keyboard::Event::KeyDown, onTriggerHandlerId_);
            else
                keyboard_.removeEventListener(Input::Keyboard::Event::KeyUp, onTriggerHandlerId_);
            onTriggerHandlerId_ = -1;
        }

        auto moveEntity = [=](Input::Keyboard::Key key) {
            auto targetDirection = IME::Direction::None;
            if (key == leftKey)
                targetDirection = IME::Direction::Left;
            else if (key == rightKey)
                targetDirection = IME::Direction::Right;
            else if (key == upKey)
                targetDirection = IME::Direction::Up;
            else if (key == downKey)
                targetDirection = IME::Direction::Down;

            if (targetDirection != target_->getDirection() && targetDirection != IME::Direction::None
                && std::dynamic_pointer_cast<IMovable>(target_)->isMoving()) {
                newDir_.first = true;
                newDir_.second = targetDirection;
            } else if (targetDirection != IME::Direction::None) {
                gridMover_->requestDirectionChange(targetDirection);
            }
        };

        if (trigger_ == Trigger::OnKeyDown)
            onTriggerHandlerId_ = keyboard_.onKeyDown(moveEntity);
        else
            onTriggerHandlerId_ = keyboard_.onKeyUp(moveEntity);
    }

    void KeyboardControlledGridMover::handleEvent(sf::Event event) {
        keyboard_.handleEvent(event);
    }

    void KeyboardControlledGridMover::update(float deltaTime) {
        gridMover_->update(deltaTime);
    }

    void KeyboardControlledGridMover::teleportTargetToDestination() {
        gridMover_->teleportTargetToDestination();
    }
}
