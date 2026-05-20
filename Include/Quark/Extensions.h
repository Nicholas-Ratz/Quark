#ifndef ATOM_QRK_EXTENSIONS_H
#define ATOM_QRK_EXTENSIONS_H

/**
 * @file Extensions.h
 * @brief Facade for compiler-specific extension macros (attributes & keywords).
 *
 * Chooses a compiler-specific `Extensions/Attributes/` and
 * `Extensions/Keywords/` implementation based on detected compiler family.
 */

#include "System/Compiler.h"

// IWYU pragma: begin_exports
#if ATOM_COMPILER_GCC_LIKE
#    include "Extensions/Attributes/GCC.h"
#    include "Extensions/Keywords/GCC.h"
#elif ATOM_COMPILER_MSVC_LIKE
#    include "Extensions/Attributes/MSVC.h"
#    include "Extensions/Keywords/MSVC.h"
#else
#    include "Extensions/Attributes/Unknown.h"
#    include "Extensions/Keywords/Unknown.h"

#endif
// IWYU pragma: end_exports

#endif
