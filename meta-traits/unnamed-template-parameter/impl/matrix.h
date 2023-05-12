#pragma once

template <typename AnotherName, typename INeedTheName>
inline Matrix<AnotherName, INeedTheName>::Matrix(size_t nrow, size_t ncol)
  : nrow_(nrow), ncol_(ncol), data_(nrow_ * ncol) {}
