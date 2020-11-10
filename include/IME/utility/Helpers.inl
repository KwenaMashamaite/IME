////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

template <typename T, typename U, typename V>
bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item) {
    return unorderedMap.find(item) != unorderedMap.end();
}

template <typename T, typename U, typename V>
bool eraseIn(std::unordered_map<T, U>& unorderedMap, const V& item) {
    if (findIn(unorderedMap, item)) {
        unorderedMap.erase(item);
        return true;
    }
    return false;
}

template <typename T, typename U>
std::pair<bool, int> findIn(const std::vector<T> vector, const U& item) {
    if (auto found = std::find(vector.begin(), vector.end(), item); found != vector.end())
        return {true, std::distance(vector.begin(), found)};
    return {false, -1};
}

template <typename T, typename U>
bool eraseIn(std::vector<T>& vector, const U& element) {
    if (auto [found, index] = findIn(vector, element); found) {
        vector.erase(vector.begin() + index);
        return true;
    }
    return false;
}

auto createRandomNumGenerator(int min, int max) {
    return [distribution = std::uniform_int_distribution(min, max),
            randomEngine = std::mt19937{std::random_device{}()}]() mutable {
        return distribution(randomEngine);
    };
}