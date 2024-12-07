#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

struct ParsedInput
{
  std::unordered_map<int, std::unordered_set<int>> m_order{};
  std::unordered_set<int> m_updatableElements{};
  std::vector<std::vector<int>> m_updates{};
};

ParsedInput parseInput(const std::string &file);
int processInput(const ParsedInput &input);

int main()
{
  auto input = parseInput("input.txt");
  auto result = processInput(input);
  std::cout << result << std::endl;
  input = parseInput("final_input.txt");
  result = processInput(input);
  std::cout << result << std::endl;
  return 0;
}

int processInput(const ParsedInput &input)
{
  int result{0};
  for (const auto &update : input.m_updates)
  {
    bool foundError = false;
    for (int i = 0; i < update.size(); ++i)
    {
      const auto left = update[i];
      if (input.m_updatableElements.find(left) != input.m_updatableElements.end())
      {
        if (input.m_order.find(left) == input.m_order.end())
        {
          foundError = true;
          break;
        }
        const auto &right = input.m_order.find(left)->second;
        for (int j = i + 1; j < update.size(); ++j)
        {
          if (input.m_updatableElements.find(update[j]) != input.m_updatableElements.end())
          {
            if (right.find(update[j]) == right.end())
            {
              foundError = true;
              break;
            }
          }
        }
        if (foundError)
        {
          break;
        }
      }
    }
    if (!foundError)
    {
      result += update[update.size() / 2];
    }
  }
  return result;
}

ParsedInput parseInput(const std::string &file)
{
  std::ifstream f(file);
  std::string line;
  ParsedInput result{};
  while (std::getline(f, line) && !line.empty())
  {
    auto pos = line.find('|');
    auto n1 = std::stoi(line.substr(0, pos));
    auto n2 = std::stoi(line.substr(pos + 1, std::string::npos));
    result.m_updatableElements.insert(n1);
    result.m_updatableElements.insert(n2);
    result.m_order[n1].insert(n2);
  }
  while (std::getline(f, line))
  {
    result.m_updates.emplace_back();
    auto pos = line.find(',');
    while (pos != std::string::npos)
    {
      auto sub = line.substr(0, pos);
      auto number = std::stoi(sub);
      result.m_updates.back().push_back(number);
      line = line.substr(pos + 1, std::string::npos);
      pos = line.find(',');
    }
    auto number = std::stoi(line.substr(1, std::string::npos));
    result.m_updates.back().push_back(number);
  }
  return result;
}