template <typename T, typename U, typename V>
bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item) {
    return unorderedMap.find(item) != unorderedMap.end();
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