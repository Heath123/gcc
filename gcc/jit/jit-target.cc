/* jit-target.cc -- Target interface for the jit front end.
   Copyright (C) 2023 Free Software Foundation, Inc.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"

#include "tree.h"
#include "memmodel.h"
#include "fold-const.h"
#include "diagnostic.h"
#include "stor-layout.h"
#include "tm.h"
#include "tm_p.h"
#include "target.h"
#include "calls.h"

#include "jit-target.h"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

static std::unordered_map<const char *, std::unordered_set<const char *>> jit_target_info;

/* Initialize all variables of the Target structure.  */

void
jit_target_init ()
{
  /* Initialize target info tables, the keys required by the language are added
     last, so that the OS and CPU handlers can override.  */
  targetjitm.jit_register_cpu_target_info ();
  targetjitm.jit_register_os_target_info ();
}

/* Add all target info in HANDLERS to JIT_TARGET_INFO for use by
   jit_has_target_value().  */

void
jit_add_target_info (const char *key, const char *value)
{
  if (jit_target_info.find (key) == jit_target_info.end())
    jit_target_info.insert ({key, {value}});
  else
    jit_target_info[key].insert(value);
}

bool jit_has_target_value (const char *key, const char *value)
{
  if (jit_target_info.find (key) == jit_target_info.end())
    return false;

  auto& set = jit_target_info[key];
  for (auto val : set)
  {
    // TODO: add a proper hash function to avoid iterating on the set here.
    if (strcmp (val, value) == 0)
      return true;
  }
  return false;
}
