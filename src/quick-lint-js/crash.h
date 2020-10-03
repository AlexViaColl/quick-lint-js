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

#ifndef QUICK_LINT_JS_CRASH_H
#define QUICK_LINT_JS_CRASH_H

#include <cstdlib>
#include <quick-lint-js/have.h>

#if QLJS_HAVE_DEBUGBREAK
#include <intrin.h>
#endif

#if QLJS_HAVE_DEBUGBREAK
#define QLJS_CRASH_ALLOWING_CORE_DUMP() ::__debugbreak()
#elif QLJS_HAVE_BUILTIN_TRAP
#define QLJS_CRASH_ALLOWING_CORE_DUMP() __builtin_trap()
#else
#define QLJS_CRASH_ALLOWING_CORE_DUMP() ::std::abort()
#endif

#define QLJS_CRASH_DISALLOWING_CORE_DUMP()   \
  do {                                       \
    ::quick_lint_js::disable_core_dumping(); \
    QLJS_CRASH_ALLOWING_CORE_DUMP();         \
  } while (false)

namespace quick_lint_js {
void disable_core_dumping();
}

#endif
