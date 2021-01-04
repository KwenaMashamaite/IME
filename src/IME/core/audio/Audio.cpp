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

#include "IME/core/audio/Audio.h"

namespace IME::Audio {
    Audio::Audio()
        : isMuted_(false),
          volumeBeforeMute_(100.0f)
    {}

    void Audio::adjustVolume(float offset) {
        if (auto currentVolume = getVolume(); currentVolume + offset > 100.0f)
            setVolume(100.0f);
        else if (currentVolume + offset < 0.0f)
            setVolume(0.0f);
        else
            setVolume(currentVolume + offset);
    }

    void Audio::setMute(bool mute) {
        if (mute && !isMuted_) {
            isMuted_ = true;
            volumeBeforeMute_ = getVolume();
            setVolume(0.0f);
            emit("muted");
        } else if (!mute && isMuted_) {
            isMuted_ = false;
            setVolume(volumeBeforeMute_);
            emit("unmuted");
        }
    }

    bool Audio::isMuted() const {
        return isMuted_;
    }

    void Audio::restart() {
        seek(0.0f);
    }
}
