/**
 * @brief Utility class for keeping a list of event handler identification numbers.
 *
 * This class allows event handlers id's to be remembered by name instead of
 * numbers. This also allows anonymous handlers to be removed from events
 * using their aliases.
 */

#ifndef HANDERIDHOLDER_H
#define HANDERIDHOLDER_H

#include <unordered_map>
#include <string>

namespace Utility {
    class HanderIdHolder {
    public:
        /**
         * @brief Add a handlers identification number by name
         * @param handlerName Event handler alias
         * @param handlerId Event handlers identification number
         */
        static void add(const std::string& handlerName, int handlerId);

        /**
         * @brief Get the identification number of a handler
         * @param handlerName Handler to obtain identification number for
         * @return Handlers identification number or -1 if the specified handler
         *         cannot be found
         */
        static int getIdFor(const std::string& handlerName);

    private:
        //Holds the identification numbers for event handlers
        inline static std::unordered_map<std::string, unsigned int> eventHandlerId_{};
    };
}

#endif