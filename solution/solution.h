#ifndef SOLUTION_H
#define SOLUTION_H

#include <initializer_list>
#include <string>
#include <vector>

class solution
{
public:
    solution() = default;
    solution(const std::vector<int>& input, int target);
    solution(std::vector<int>&& input, int target);
    solution(std::initializer_list<int> input, int target);
    ~solution() = default;

    std::vector<std::string> get_result();

    bool valid_input();
    void dfs(int current, std::string& str, int index);

    solution(const solution&) = delete;
    solution& operator=(const solution&) = delete;

private:
    std::vector<int> m_input;
    std::vector<std::string> m_result;
    int m_target;
};

#endif  // SOLUTION_H
