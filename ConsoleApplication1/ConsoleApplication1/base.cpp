#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <random>
#include <ctype.h>

using std::string;

string action[] = { "+", "-" };
std::default_random_engine rng;

struct Answer {
  std::vector<string> expression;
  int result;
};

int getRandInt(int nMin, int nMax)
{
  std::uniform_int_distribution<int> dist_min_max(nMin, nMax);
  return dist_min_max(rng);
}

string getAction() {
  return action[getRandInt(0, 1)];
}

int getNumber() {
  return getRandInt(1, 15);
}

int parseExpression(std::vector<string> &expr) {
  bool flag = false;
  int buf = NULL;
  int result = std::stoi(expr[0]);

  for (int index = 1; index < expr.size(); ++index) {
    if (expr[index] == "-") {
      flag = true;
      continue;
    }
    else if (expr[index] == "+") {
      flag = false;
      continue;
    }

    buf = std::stoi(expr[index]);

    if (flag) {
      result -= buf;
    }
    else {
      result += buf;
    }
  }

  return result;
}

void createExpression(std::vector<Answer> &teaser, int strong_level) {
  strong_level *= 2;

  if (strong_level % 2 == 0) {
    strong_level++;
  }

  for (int index = 0; index < teaser.size(); ++index) {
    for (int f_index = 0; f_index < strong_level; ++f_index) {
      if (f_index % 2 == 0) {
        teaser[index].expression.push_back(std::to_string(getNumber()));
      }
      else {
        teaser[index].expression.push_back(getAction());
      }
    }
  }

  for (int index = 0; index < teaser.size(); ++index) {
    teaser[index].result = parseExpression(teaser[index].expression);
  }
}

void run(std::vector<Answer> teaser) {
  int answer = NULL;

  for (int index = 0; index < teaser.size();) {
    std::cout << index + 1 << ")";
    for (auto sym : teaser[index].expression) {
      std::cout << sym;
    }
    std::cout << " = ";
    std::cin >> answer;
    if (answer == teaser[index].result) {
      std::cout << "OK!" << std::endl;
      index++;
    }
    else {
      std::cout << "Noo!" << std::endl;
    }
  }
}

int main() {
  int count_task, strong_level;
  std::cout << "Write count task: ";
  std::cin >> count_task;

  std::cout << "Write strong level: ";
  std::cin >> strong_level;

  std::vector<Answer> teaser(count_task);

  createExpression(teaser, strong_level);

  run(teaser);

  return 0;
}

