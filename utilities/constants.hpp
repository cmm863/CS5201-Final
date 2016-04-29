//
// Created by Connor McBride on 4/21/16.
//

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>

namespace constants
{
  // File paths
  const std::string TRIDIAGONAL_INPUT_FILE = "test_inputs/trid_input.in";
  const std::string DIAGONAL_INPUT_FILE = "test_inputs/diag_input.in";
  const std::string LOWER_TRIANGULAR_INPUT_FILE = "test_inputs/lower_tri_input.in";
  const std::string UPPER_TRIANGULAR_INPUT_FILE = "test_inputs/upper_tri_input.in";
  const std::string SYMMETRIC_INPUT_FILE = "test_inputs/symm_input.in";

  // Titles
  const std::string TRIDIAGONAL_TEST_TITLE = "=== Tridiagonal Matrix Test ===";
  const std::string DIAGONAL_TEST_TITLE = "=== Diagonal Matrix Test ===";
  const std::string LOWER_TRIANGULAR_TEST_TITLE = "=== Lower Triangular Matrix Test ===";
  const std::string UPPER_TRIANGULAR_TEST_TITLE = "=== Upper Triangular Matrix Test ===";
  const std::string SYMMETRIC_TEST_TITLE = "=== Symmetric Matrix Test ===";
}

#endif //CONSTANTS_HPP
