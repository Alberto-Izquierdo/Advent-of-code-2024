#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

std::pair<std::vector<int>, std::vector<int>> parseInput();

int main() {
  auto parsedInput = parseInput();
  std::sort(parsedInput.first.begin(), parsedInput.first.end());
  std::sort(parsedInput.second.begin(), parsedInput.second.end());
  int totalDistance = 0;
  for (auto i = 0; i < parsedInput.first.size(); ++i) {
    auto distance = std::abs(parsedInput.first[i] - parsedInput.second[i]);
    totalDistance += distance;
  }
  std::cout << totalDistance << std::endl;
  return 0;
}

std::pair<std::vector<int>, std::vector<int>> parseInput() {
  std::ifstream f("final_input.txt");
  std::string line;
  std::pair<std::vector<int>, std::vector<int>> result{};
  while (std::getline(f, line)) {
    std::stringstream words(line);
    std::string number1Str;
    std::string number2Str;
    words >> number1Str;
    words >> number2Str;
    auto number1 = std::stoi(number1Str);
    auto number2 = std::stoi(number2Str);
    result.first.push_back(number1);
    result.second.push_back(number2);
  }
  return result;
}
