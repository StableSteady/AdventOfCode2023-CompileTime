#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <optional>
#include <ranges>
#include <string>
#include <string_view>
#include <utility>

constexpr int MIN_LEN = 3;
constexpr int MAX_LEN = 5;

constexpr bool isDigit(const char c) {
    return c <= '9' and c >= '0';
}

struct Map {
    std::array<const char*, 10> arr{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
    constexpr int operator[](std::string_view word) {
        auto it = std::find(arr.begin(), arr.end(), word);
        return (it == std::end(arr)) ? -1 : std::distance(arr.begin(), it);
    };
    constexpr bool contains(std::string_view word) {
        return (std::find(arr.begin(), arr.end(), word) != std::end(arr));
    }
};

constexpr auto notNull = [](const std::optional<int>& optional) { return optional != std::nullopt; };
constexpr auto optionalToInt = [](const std::optional<int>& optional) { return optional.value(); };

consteval int solve() {
    std::string input = "two1nine\neightwothree\nabcone2threexyz\nxtwone3four\n4nineeightseven2\nzoneight234\n7pqrstsixteen\n";
    int sum = 0;
    Map wordToDigit;
    for (const auto& subrange : input | std::views::split('\n')) {
        std::string_view s(subrange);
        auto toOptionalInt = [&s, &wordToDigit](const std::tuple<std::ptrdiff_t, char>& t) -> std::optional<int> {
            const auto& [index, ch] = t;
            if (isDigit(ch)) {
                return static_cast<int>(ch - '0');
            } else {
                for (int i = MIN_LEN; i <= MAX_LEN and std::cmp_less_equal(index + i, s.size()); i++) {
                    std::string word(s);
                    word = word.substr(index, i);
                    if (wordToDigit.contains(word)) {
                        return wordToDigit[word];
                    }
                }
                return std::nullopt;
            }
            };
        auto digits = s | std::views::enumerate | std::views::transform(toOptionalInt) | std::views::filter(notNull) | std::views::transform(optionalToInt);
        if (!digits.empty())
            sum += digits.front() * 10 + digits.back();
    }
    return sum;
}

int main() {
    std::cout << solve();
}