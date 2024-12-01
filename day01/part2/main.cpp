#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::pair<std::vector<int>, std::unordered_map<int, int>> parseInput();

int main() {
  auto parsedInput = parseInput();
  int result = 0;
  for (auto currentNumber: parsedInput.first) {
    result += currentNumber * parsedInput.second[currentNumber];
  }
  std::cout << result << std::endl;
  return 0;
}

std::pair<std::vector<int>, std::unordered_map<int, int>> parseInput() {
  std::ifstream f("final_input.txt");
  std::string line;
  std::pair<std::vector<int>, std::unordered_map<int, int>> result{};
  while (std::getline(f, line)) {
    std::stringstream words(line);
    std::string number1Str;
    std::string number2Str;
    words >> number1Str;
    words >> number2Str;
    auto number1 = std::stoi(number1Str);
    auto number2 = std::stoi(number2Str);
    result.first.push_back(number1);
    result.second[number2]++;
  }
  return result;
}
