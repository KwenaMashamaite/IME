/**
 * @brief Intrface for entiites that can own and use weapons
 */

#ifndef IWEAPONWIELDER_H
#define IWEAPONWIELDER_H

#include <memory>

namespace SI {
    class IWeapon; //Forward declaration


    class IWeaponOwner {
    public:
        /**
         * @brief Give an entity a weapon
         * @param weapon Weapon to give to entity
         *
         * If the entity does not currently poses a weapon, the newly added
         * weapon becomes the default weapon, otherwise the weapon is added
         * to the entity's collection of weapons
         */
        virtual void addWeapon(std::unique_ptr<IWeapon> weapon) = 0;

        /**
         * @brief Use default weapon
         */
        virtual void use() = 0;
    };
}

#endif
