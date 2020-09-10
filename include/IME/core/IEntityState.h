/**
 * @brief
 */

#ifndef IENTITYSTATE_H
#define IENTITYSTATE_H

#include <memory>

namespace IME {
    class IEntity;

    class IEntityState {
    public:
        IEntityState(std::shared_ptr<IEntity> target) : target_(std::move(target)){}
        virtual void init() = 0;
        virtual void update() = 0;
        virtual void reset() = 0;

    private:
        std::shared_ptr<IEntity> target_;
    };
}

#endif
