#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> parseInput(const std::string &input);
int countXMAS(const std::vector<std::string> &input);
int checkPosition(const std::vector<std::string> &input, int x, int y);

int main() {
  auto parsedInput = parseInput("input.txt");
  auto result = countXMAS(parsedInput);
  std::cout << result << std::endl;
  parsedInput = parseInput("final_input.txt");
  result = countXMAS(parsedInput);
  std::cout << result << std::endl;
  return 0;
}

std::vector<std::string> parseInput(const std::string &file) {
  std::ifstream f(file);
  std::string line;
  std::vector<std::string> result{};
  while (std::getline(f, line)) {
    result.push_back(line);
  }
  return result;
}

int countXMAS(const std::vector<std::string> &input) {
  int result = 0;
  for (auto y = 0; y < input.size(); ++y) {
    for (auto x = 0; x < input[y].size(); ++x) {
      result += checkPosition(input, x, y);
    }
  }
  return result;
}

int checkPosition(const std::vector<std::string> &input, int x, int y) {
  static const std::string xmas{"XMAS"};
  if (input[y].c_str()[x] != 'A') {
    return 0;
  }
  int result = 0;
  std::pair<int, int> leftUp{-1, -1};
  std::pair<int, int> leftDown{-1, 1};
  std::pair<int, int> rightUp{1, -1};
  std::pair<int, int> rightDown{1, 1};
  std::vector<std::pair<int, int>> directions{leftUp, leftDown, rightUp,
                                              rightDown};
  int partial{0};
  for (const auto &direction : directions) {
    for (int i = -1; i < 2; i += 2) {
      auto nextPosX = x + direction.first * i;
      auto nextPosY = y + direction.second * i;
      if (nextPosX < 0 || nextPosX >= input[0].size() || nextPosY < 0 ||
          nextPosY >= input.size()) {
        break;
      }
      if (input[nextPosY].at(nextPosX) != xmas.at(i + 2)) {
        break;
      } else if (i == 1) {
        ++partial;
      }
    }
  }
  if (partial == 2) {
    ++result;
  }
  return result;
}
