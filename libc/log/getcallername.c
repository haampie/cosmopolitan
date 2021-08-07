/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2021 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/alg/bisectcarleft.internal.h"
#include "libc/log/log.h"
#include "libc/nexgen32e/stackframe.h"
#include "libc/runtime/symbols.internal.h"

/**
 * Returns name of funciton that called caller function.
 */
const char *GetCallerName(const struct StackFrame *bp) {
  struct SymbolTable *st;
  if (!bp && (bp = __builtin_frame_address(0))) bp = bp->next;
  if (bp && (st = GetSymbolTable()) && st->count &&
      ((intptr_t)bp->addr >= (intptr_t)&_base &&
       (intptr_t)bp->addr <= (intptr_t)&_end)) {
    return st->name_base +
           st->symbols[bisectcarleft((const int32_t(*)[2])st->symbols,
                                     st->count, bp->addr - st->addr_base - 1)]
               .name_rva;
  } else {
    return 0;
  }
}