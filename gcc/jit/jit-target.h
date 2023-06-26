/* jit-target.h -- Data structure definitions for target-specific D behavior.
   Copyright (C) 2023 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 3, or (at your option) any
   later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_JIT_TARGET_H
#define GCC_JIT_TARGET_H

#define DEFHOOKPOD(NAME, DOC, TYPE, INIT) TYPE NAME;
#define DEFHOOK(NAME, DOC, TYPE, PARAMS, INIT) TYPE (* NAME) PARAMS;
#define DEFHOOK_UNDOC DEFHOOK
#define HOOKSTRUCT(FRAGMENT) FRAGMENT

#include "jit-target.def"

/* Each target can provide their own.  */
extern struct gcc_targetjitm targetjitm;

extern void jit_target_init ();
extern void jit_add_target_info (const char *key, const char *value);
extern bool jit_has_target_value (const char *key, const char *value);

#endif /* GCC_JIT_TARGET_H  */
