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

#include <algorithm>
#include <ostream>
#include <quick-lint-js/location.h>
#include <quick-lint-js/narrow-cast.h>

namespace quick_lint_js {
std::ostream &operator<<(std::ostream &out, const source_position &p) {
  out << "source_position{" << p.line_number << ',' << p.column_number << ','
      << p.offset << '}';
  return out;
}

source_position source_range::begin() const noexcept { return this->begin_; }

source_position source_range::end() const noexcept { return this->end_; }

bool operator==(source_code_span x, std::string_view y) noexcept {
  return x.string_view() == y;
}

bool operator!=(source_code_span x, std::string_view y) noexcept {
  return !(x == y);
}

locator::locator(const char *input) noexcept : input_(input) {}

source_range locator::range(source_code_span span) const {
  source_position begin = this->position(span.begin());
  source_position end = this->position(span.end());
  return source_range(begin, end);
}

source_position locator::position(const char *source) const noexcept {
  if (this->offset_of_lines_.empty()) {
    this->cache_offsets_of_lines();
  }
  assert(!this->offset_of_lines_.empty());

  source_position::offset_type offset =
      narrow_cast<source_position::offset_type>(source - this->input_);
  auto offset_of_line_it = std::lower_bound(
      this->offset_of_lines_.begin() + 1, this->offset_of_lines_.end(), offset);

  int line_number =
      narrow_cast<int>(offset_of_line_it - this->offset_of_lines_.begin());
  const char *beginning_of_line = &this->input_[*(offset_of_line_it - 1)];
  int column_number = narrow_cast<int>(source - beginning_of_line) + 1;
  return source_position{line_number, column_number, offset};
}

void locator::cache_offsets_of_lines() const {
  this->offset_of_lines_.push_back(0);
  for (const char *c = this->input_; *c != '\0'; ++c) {
    if (*c == '\n') {
      const char *beginning_of_line = c + 1;
      this->offset_of_lines_.push_back(
          narrow_cast<source_position::offset_type>(beginning_of_line -
                                                    this->input_));
    }
  }
}
}  // namespace quick_lint_js
