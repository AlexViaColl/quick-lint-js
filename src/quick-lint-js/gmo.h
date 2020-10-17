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

#ifndef QUICK_LINT_JS_GMO_H
#define QUICK_LINT_JS_GMO_H

#include <cstdint>
#include <string_view>

namespace quick_lint_js {
enum class endian {
  little,
  big,
};

// gmo_file gives access to data within a GNU MO file.
//
// A GNU MO file stores translations. It is generated by GNU gettext's msgfmt
// command.
//
// TODO(strager): Make this parser robust. gmo_file currently trusts the input
// and assumes it is valid.
class gmo_file {
 public:
  using offset_type = std::uint32_t;
  using word_type = std::uint32_t;

  explicit gmo_file(const void *data) noexcept;

  word_type string_count() const noexcept;

  std::string_view original_string_at(word_type index) const noexcept;
  std::string_view translated_string_at(word_type index) const noexcept;

  std::string_view find_translation(std::string_view original) const noexcept;

  static word_type hash_string(std::string_view) noexcept;

 private:
  endian get_endian() const noexcept;

  const std::uint8_t *data_;
};
}

#endif
