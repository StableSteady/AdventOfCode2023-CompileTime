#include <iostream>
#include <ranges>
#include <string_view>

constexpr std::string_view input = R"(1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet)";

constexpr bool isDigit(const char c) {
    return c <= '9' and c >= '0';
}

constexpr auto digit = [](const char c) { return isDigit(c); };
constexpr auto toInt = [](const char c) { return static_cast<int>(c - '0'); };

consteval int solve() {
    int sum = 0;
    for (const auto& s : input | std::views::split('\n')) {
        auto digits = s | std::views::filter(digit) | std::views::transform(toInt);
        sum += digits.front() * 10 + digits.back();
    }
    return sum;
}

int main() {
    std::cout << solve();
}