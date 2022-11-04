#include "solution.h"

solution::solution(const std::vector<int>& input, int target) : m_input(input), m_target(target) {}

solution::solution(std::vector<int>&& input, int target) : m_input(std::move(input)), m_target(target) {}

solution::solution(std::initializer_list<int> input, int target) : m_input(input), m_target(target) {}

std::vector<std::string> solution::get_result()
{
    if (!valid_input()) { return {}; }

    std::string s;
    s.append(std::to_string(m_input[0]));
    dfs(m_input[0], s, 1);
    return m_result;
}

bool solution::valid_input()
{
    if (m_input.size() != 4) { return false; }
    if (m_target != 24) { return false; }
    return true;
}

void solution::dfs(int current, std::string& str, int index)
{
    if (current == 24 && index == 4) { m_result.emplace_back(str); }

    if (index >= 4) { return; }

    for (int i = 0; i < 4; ++i)
    {
        switch (i)
        {
            case 0:
            {
                str.append(1, '+');
                str.append(std::to_string(m_input[index]));
                dfs(current + m_input[index], str, index + 1);
                break;
            }
            case 1:
            {
                str.append(1, '-');
                str.append(std::to_string(m_input[index]));
                dfs(current - m_input[index], str, index + 1);
                break;
            }
            case 2:
            {
                str.append(1, '*');
                str.append(std::to_string(m_input[index]));
                dfs(current * m_input[index], str, index + 1);
                break;
            }
            case 3:
            {
                //除0直接跳过。
                if (m_input[index] == 0)
                {
                    dfs(current, str, index + 1);
                    break;
                }
                //不使用浮点运算，直接舍去小数点后的数值。
                str.append(1, '/');
                str.append(std::to_string(m_input[index]));
                dfs(current / m_input[index], str, index + 1);
                break;
            }
        }
        str.pop_back();
        str.pop_back();
    }
}