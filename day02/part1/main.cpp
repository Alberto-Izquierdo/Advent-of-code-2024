#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <cmath>

std::vector<std::vector<int>> parseInput();
bool isInputValid(const std::vector<int> &input);

int main() {
  auto parsedInput = parseInput();
  int count{0};
  for (const auto &line : parsedInput) {
    bool result = isInputValid(line);
    if (result) {
      ++count;
    }
  }
  std::cout << count << std::endl;
  return 0;
}

std::vector<std::vector<int>> parseInput() {
  std::ifstream f("final_input.txt");
  std::string line;
  std::vector<std::vector<int>> result{};
  while (std::getline(f, line)) {
    result.emplace_back();
    std::stringstream words(line);
    std::string word;
    while (words >> word) {
      result.back().emplace_back(std::stoi(word));
    }
  }
  return result;
}

bool isInputValid(const std::vector<int> &input) {
	bool increasing = input[1] > input[0];
	bool result = true;
	for (size_t i = 0; i < input.size() - 1; ++i) {
	  bool partialResult = increasing ? input[i + 1] > input[i] : input[i + 1] < input[i];
          auto diff = std::abs(input[i] - input[i + 1]);
	  result &= partialResult && diff < 4;
	  if (!result) {
	    break;
	  }
	}
	return result;
}
