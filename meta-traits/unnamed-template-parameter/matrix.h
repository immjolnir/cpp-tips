// See https://stackoverflow.com/questions/35651531/c-how-to-use-unnamed-template-parameters-in-class-members
// Template parameter names are "local" to each template declaration. Nothing prevents you from assigning a name. Which
// you indeed must do if you need to refer to that parameter later (such as using it as an argument in the template-id
// of the class).

#pragma once

#include <cmath>
#include <type_traits>
#include <vector>

template <typename T, typename = typename std::enable_if<std::is_scalar<T>::value>::type>
class Matrix {
  public:
    Matrix(const size_t nrow, const size_t ncol);

    size_t rows() const { return nrow_; }

    size_t cols() const { return ncol_; }

  private:
    const size_t nrow_;
    const size_t ncol_;
    std::vector<T> data_;  // How to replace it with std::array?
};

// Reserve the last line for it
#include "impl/matrix.h"
