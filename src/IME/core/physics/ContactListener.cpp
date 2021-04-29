////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/core/physics/ContactListener.h"

namespace ime {
    int ContactListener::onContactBegin(Callback<Collider::Ptr, Collider::Ptr> callback) {
        return eventEmitter_.on("contactBegin", std::move(callback));
    }

    int ContactListener::onContactEnd(Callback<Collider::Ptr, Collider::Ptr> callback) {
        return eventEmitter_.on("contactEnd", std::move(callback));
    }

    int ContactListener::onPreSolve(Callback<Collider::Ptr, Collider::Ptr> callback) {
        return eventEmitter_.on("preSolve", std::move(callback));
    }

    int ContactListener::onPostSolve(Callback<Collider::Ptr, Collider::Ptr> callback) {
        return eventEmitter_.on("postSolve", std::move(callback));
    }

    bool ContactListener::unsubscribe(int callbackId) {
        if (eventEmitter_.removeEventListener("contactBegin", callbackId)
            || eventEmitter_.removeEventListener("contactEnd", callbackId)
            || eventEmitter_.removeEventListener("preSolve", callbackId)
            || eventEmitter_.removeEventListener("postSolve", callbackId))
        {
            return true;
        }

        return false;
    }
}