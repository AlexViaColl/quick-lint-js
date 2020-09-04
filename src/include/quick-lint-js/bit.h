// quick-lint-js finds bugs in JavaScript programs.
// Copyright (C) 2020  Matthew Glazar
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef QUICK_LINT_JS_BIT_H
#define QUICK_LINT_JS_BIT_H

#include <cstdint>

namespace quick_lint_js {
// TODO(strager): Use std::countr_zero if available.
inline int countr_zero(std::uint32_t x) noexcept {
#if defined(__GNUC__)
  if (x == 0) {
    return 32;
  }
  return __builtin_ctz(x);
#else
  std::uint32_t i;
  for (i = 0; i < 32; ++i) {
    if ((x & (std::uint32_t(1) << i)) != 0) {
      break;
    }
  }
  return i;
#endif
}

// TODO(strager): Use std::countr_one if available.
inline int countr_one(std::uint32_t x) noexcept {
#if defined(__GNUC__)
  return countr_zero(~x);
#else
  std::uint32_t i;
  for (i = 0; i < 32; ++i) {
    if ((x & (std::uint32_t(1) << i)) == 0) {
      break;
    }
  }
  return i;
#endif
}
}

#endif
