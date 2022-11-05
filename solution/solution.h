#ifndef SOLUTION_H
#define SOLUTION_H

#include <initializer_list>
#include <string>
#include <vector>

#include "fraction.h"

namespace solve
{
class solution
{
public:
    solution() = default;
    solution(const std::vector<solve::fraction>& input, int target = 24);
    solution(std::vector<solve::fraction>&& input, int target = 24);

    template <typename... Args>
    solution(int target, Args&&... args) : m_target(target)
    {
        (m_input.emplace_back(std::forward<Args>(args)), ...);
    }

    ~solution() = default;

    // std::string get_result();

    bool judge();

    bool valid_input();
    bool backtrace(std::vector<solve::fraction>& input);

    solution(const solution&) = delete;
    solution& operator=(const solution&) = delete;

private:
    std::vector<solve::fraction> m_input;
    // std::string m_result;
    int m_target;
};
}  // namespace solve

#endif  // SOLUTION_H
