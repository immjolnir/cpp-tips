#pragma once

#include <algorithm>
#include <cmath>
#include <numeric>
#include <utility>
#include <vector>

namespace stats {
/**
 * See https://www.geeksforgeeks.org/mathematics-mean-variance-and-standard-deviation/
 * Variance is the sum of squares of differences between all numbers and means.
 *
 * Standard Deviation is square root of variance. It is a measure of the extent to which data varies
 * from the mean.
 *
 */
template <typename T>
std::pair<double, double> meanStdDev(const std::vector<T>& inputs) {
  if (inputs.empty()) {
    return {};
  }

  double mean = std::accumulate(inputs.begin(), inputs.end(), 0.0f) / inputs.size();

  double variance = 0;
  std::for_each(inputs.begin(), inputs.end(),
                [&variance, mean](T n) { variance += (n - mean) * (n - mean); });
  variance /= inputs.size() - 1; // Should it minus a 1?

  double standard_deviation = std::sqrt(variance);
  return {mean, standard_deviation};
}

}  // namespace stats
