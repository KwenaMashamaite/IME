#ifndef IME_NONCOPYABLE_H
#define IME_NONCOPYABLE_H

namespace IME {
    namespace Utility {
        class NonCopyable {
        public:
            /**
             * @brief Copy constructor
             */
            NonCopyable(const NonCopyable&) = delete;

            /**
             * @brief Assignment operator
             */
            NonCopyable& operator=(const NonCopyable&) = delete;

        protected:
            /**
             * @brief Default constructor
             */
            NonCopyable() = default;

            /**
             * @brief Destructor
             */
            ~NonCopyable() = default;
        };
    }
}

#endif
