#include <iostream>
#include <random>
#include <vector>

#include "statistics.h"

void simulator() {
  // see https://en.cppreference.com/w/cpp/numeric/random/normal_distribution
  std::random_device rd{};
  std::mt19937 gen{rd()};

  // values near the mean are the most likely
  // standard deviation affects the dispersion of generated values from the mean
  std::normal_distribution<float> d{5, 2};

  std::vector<float> inputs;

  for (int i = 0; i < 10; ++i) {
    inputs.emplace_back(d(gen));
  }

  auto val = stats::meanStdDev(inputs);
  std::cout << val.first << ", " << val.second << std::endl;  // near 5, 2
}

int main() {
  {
    auto val = stats::meanStdDev<int>({600, 470, 170, 430, 300});  // 394, 147.323
    std::cout << val.first << ", " << val.second << std::endl;
  }
  {
    auto val0 = stats::meanStdDev<int>({2, 4, 4, 4, 5, 5, 7, 9});  // 5, 2
    std::cout << val0.first << ", " << val0.second << std::endl;
  }

  {
    // https://study.com/learn/lesson/coefficient-of-dispersion-formula-example-significance.html
    // 但这里用的是 中值，而不是平均值
    /*
     * The coefficient of dispersion measures how far away the median of a data point is. The
     * formula is given as: Coefficient of Dispersion = =∑ni=1|Xi−Xm|n.
     */

    auto coefficient_of_dispersion = [](float mean, float std_dev) { return std_dev / mean; };

    auto val0 = stats::meanStdDev<int>({5, 4, 9, 13, 21, 19, 26});
    std::cout << val0.first << ", " << val0.second << std::endl;
    std::cout << coefficient_of_dispersion(val0.first, val0.second) << std::endl;
  }
  simulator();
}