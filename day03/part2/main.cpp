#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

std::string parseInput(const std::string &input);
std::vector<std::pair<int, int>> getOperators(std::string input);
int multiply(const std::vector<std::pair<int, int>> &input);

int main() {
  auto parsedInput = parseInput("input.txt");
  auto operators = getOperators(parsedInput);
  auto result = multiply(operators);
  std::cout << result << std::endl;
  parsedInput = parseInput("final_input.txt");
  operators = getOperators(parsedInput);
  result = multiply(operators);
  std::cout << result << std::endl;
  return 0;
}

std::string parseInput(const std::string &file) {
  std::ifstream f(file);
  std::string line;
  std::string result{};
  while (std::getline(f, line)) {
    result += line;
  }
  return result;
}

std::vector<std::pair<int, int>> getOperators(std::string input) {
  std::vector<std::pair<int, int>> result{};
  std::regex r{R"((mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\)))"};
  std::smatch m;
  bool enabled = true;
  while (std::regex_search(input, m, r)) {
    if (m[0] == "do()") {
      enabled = true;
    } else if (m[0] == "don't()") {
      enabled = false;
    } else if (enabled) {
      auto a = m[2];
      auto b = m[3];
      result.emplace_back(std::stoi(a), std::stoi(b));
    }
    input = m.suffix().str();
  }
  return result;
}

int multiply(const std::vector<std::pair<int, int>> &input) {
  int result{0};
  for (const auto &pair : input) {
    result += pair.first * pair.second;
  }
  return result;
}
