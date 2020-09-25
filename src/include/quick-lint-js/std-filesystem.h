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

#ifndef QUICK_LINT_JS_STD_FILESYSTEM_H
#define QUICK_LINT_JS_STD_FILESYSTEM_H

#include <quick-lint-js/have.h>

#if QLJS_HAVE_FILESYSTEM_HEADER
#include <filesystem>
#elif QLJS_HAVE_EXPERIMENTAL_FILESYSTEM_HEADER
#include <experimental/filesystem>
#else
#error "Unsupported platform"
#endif

namespace quick_lint_js::filesystem {
#if QLJS_HAVE_FILESYSTEM_HEADER
using namespace std::filesystem;
#elif QLJS_HAVE_EXPERIMENTAL_FILESYSTEM_HEADER
using namespace std::experimental::filesystem;
#else
#error "Unsupported platform"
#endif
}

#endif
