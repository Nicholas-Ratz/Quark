# Quark Library

**Version:** 1.2.0
**Language:** C++ (C++98 and later)
**Type:** Header-only Plugin for Atom Framework

## Overview

The **Quark** library is a comprehensive, header-only C++ utility library designed as a plugin for the Atom framework. It provides portable, low-level abstractions for system detection, compiler-specific features, atomic operations, bit manipulation, and SIMD vectorization. Quark enables developers to write high-performance, cross-platform C++ code by encapsulating compiler and architecture-specific details behind unified, easy-to-use macros and utilities.

Documentation: All public headers in `Include/Quark/` now include Doxygen-style file comments (see `Include/Quark/Types.h`) to aid automated API documentation generation.

Generating docs (Doxygen):

```bash
# Create a default Doxyfile and adjust `INPUT` to `Include/Quark`
doxygen -g Doxyfile
# Edit `Doxyfile`: set `INPUT = Include/Quark` and `EXTRACT_ALL = YES`
doxygen Doxyfile
```

The generated HTML will appear in the `html/` directory by default.

## Key Features

### 1. **System Detection** (`System.h` + `System/*.h`)
Comprehensive environment detection macros that allow code to adapt to different platforms:

- **Architecture Detection** (`System/Arch.h`)
  - CPU architecture identification (x86, x86_64, ARM, etc.)
  - Pointer width and alignment information
  - Endianness detection

- **Compiler Detection** (`System/Compiler.h`)
  - Compiler identification (GCC, Clang, MSVC, etc.)
  - Compiler family classification (GCC-like, MSVC-like)
  - Version information for conditional compilation

- **C++ Standard Detection** (`System/Cpp.h`)
  - Language standard quark detection (C++98, C++11, C++14, C++17, C++20, etc.)
  - Feature availability queries (constexpr, threading, etc.)

- **Endianness Detection** (`System/Endian.h`)
  - Byte order identification (little-endian, big-endian)

- **Operating System Detection** (`System/Os.h`)
  - OS identification (Linux, Windows, macOS, BSD, etc.)

- **Sanitizer Detection** (`System/Sanitizer.h`)
  - Runtime sanitizer identification (ASAN, UBSAN, TSAN, MSAN, etc.)

- **SIMD Feature Detection** (`System/Simd.h`)
  - SIMD instruction set support (AVX, AVX2, SSE, SSE2, NEON, etc.)
  - Vector capability queries

### 2. **Feature Detection** (`Features.h`)
Portable compiler feature-probing helpers that normalize access to compiler capabilities:

- `ATOM_HAS_ATTRIBUTE(x)` - Check for compiler attributes
- `ATOM_HAS_BUILTIN(x)` - Check for compiler builtins
- `ATOM_HAS_FEATURE(x)` - Check for language/compiler features
- `ATOM_HAS_EXTENSION(x)` - Check for compiler extensions
- `ATOM_HAS_CPP_ATTRIBUTE(x)` - Check for standard C++ attributes
- `ATOM_HAS_INCLUDE(x)` - Check for header availability
- `ATOM_HAS_DECLSPEC(x)` - Check for declspec attributes

All feature checks provide conservative defaults (returning 0) when unavailable, allowing callers to implement portable fallbacks.

### 3. **Type Aliases** (`Types.h`)
Lightweight, portable type aliases for fixed-width and convenience use:

- **Fixed-width unsigned integers:** `u8`, `u16`, `u32`, `u64`
- **Fixed-width signed integers:** `i8`, `i16`, `i32`, `i64`
- **Fast integer types:** `i8f`, `i16f`, `i32f`, `i64f` (at least N bits, performance-oriented)
- **Fast integer types:** `i8l`, `i16l`, `i32l`, `i64l` (at least N bits, size-oriented)
- **Pointer-sized integers:** `vptr`, `usize`, `isize`, `uptr`, `iptr`
- **Floating-point types:** `f32`, `f64`, `f80`
- **Boolean and character:** `b8`, `b32`, `c8`, `c16`, `c32`, `wc`

These aliases improve code clarity and ensure portability across 32-bit and 64-bit platforms.

### 4. **Atomic Operations** (`Atomic.h`)
Safe concurrent access primitives with memory ordering guarantees:

- **Memory ordering constants:** `RELAXED`, `CONSUME`, `ACQUIRE`, `RELEASE`, `ACQ_REL`, `SEQ_CST`
- **Quark operations:**
  - `load<T>()` - Atomic load
  - `store<T>()` - Atomic store
  - `exchange<T>()` - Atomic exchange
  - `compareExchange<T>()` - Compare-and-swap (CAS)
  - `fetchAdd<T>()` - Atomic add-and-return
  - `fetchSub<T>()` - Atomic subtract-and-return
  - `fetchAnd<T>()` - Atomic bitwise AND
  - `fetchOr<T>()` - Atomic bitwise OR
  - `fetchXor<T>()` - Atomic bitwise XOR
  - `pause()` - Pause instruction for spin-wait loops

**Compiler-specific backends:**
- GCC/Clang: Uses `__atomic_*` builtins
- MSVC: Uses `_Interlocked*` intrinsics
- Generic: Falls back to C11 `<stdatomic.h>` or unsafe fallbacks

All operations located in `Quark::Atomic::` namespace.

### 5. **Attributes & Compiler Directives** (`Attributes.h`)
Unified macros for compiler-specific features and optimizations:

- **Standard C++ attributes:** `ATOM_NORETURN`, `ATOM_NODISCARD`, `ATOM_MAYBE_UNUSED`, `ATOM_FALLTHROUGH`
- **Control flow/exceptions:** `ATOM_NOEXCEPT`, `ATOM_ASSUME`, `ATOM_UNREACHABLE`
- **Deprecation:** `ATOM_DEPRECATED`, `ATOM_DEPRECATED_MSG`
- **Visibility/linkage:** `ATOM_EXPORT`, `ATOM_IMPORT`, `ATOM_LOCAL`, `ATOM_API`
- **Inlining:** `ATOM_FORCE_INLINE`, `ATOM_NO_INLINE`
- **Optimization hints:** `ATOM_LIKELY`, `ATOM_UNLIKELY`, `ATOM_HOT`, `ATOM_COLD`
- **Function properties:** `ATOM_PURE`, `ATOM_CONST`, `ATOM_MALLOC`, `ATOM_ALLOC_SIZE`, `ATOM_RETURNS_NONNULL`
- **Format checking:** `ATOM_FORMAT_PRINTF`, `ATOM_FORMAT_SCANF`
- **Memory/layout:** `ATOM_PACKED_BEGIN`, `ATOM_PACKED_END`, `ATOM_PACKED`, `ATOM_RESTRICT`, `ATOM_MAY_ALIAS`
- **Language feature shims:** `ATOM_CONSTEXPR`, `ATOM_THREAD_LOCAL`, `ATOM_ALIGNAS`, `ATOM_NULLPTR`
- **Diagnostics:** `ATOM_DEBUG_TRAP`, `ATOM_FUNC_NAME`, `ATOM_FUNC_SIG`, `ATOM_LINE`

**Compiler-specific backends:**
- GCC/Clang: Full support via `__attribute__` syntax
- MSVC: Support via declspec and pragmas
- Generic: Minimal fallbacks for unsupported compilers

### 6. **Utilities** (`Utils.h`)
Common utility macros and helpers:

- **Token concatenation:** `ATOM_CONCAT`, `ATOM_CONCAT3`
- **Unused variable suppression:** `ATOM_UNUSED`
- **Memory size helpers:** `ATOM_KB`, `ATOM_MB`, `ATOM_GB`, `ATOM_TB`
- **Type aliasing:** `ATOM_ALIAS` (uses C++11 `using` or C++98 `typedef`)
- **Buffer alignment:** `ATOM_ALIGNBUF`
- **Debug messaging:** `ATOM_DEBUG_MESSAGE`, `ATOM_DEBUG_MESSAGE_ARGS`
- **Assertions:** `ATOM_ASSERT`, `ATOM_ASSERT_MSG` (active in debug builds only)

## Directory Structure

```
Quark/
├── Include/
│   └── Quark/
│       ├── Types.h
│       ├── Utils.h
│       ├── Features.h
│       ├── System.h
│       ├── Standard.h
│       ├── Extensions.h
│       ├── Extensions/
│       │   ├── Attributes/
│       │   │   ├── GCC.h
│       │   │   ├── MSVC.h
│       │   │   └── Unknown.h
│       │   └── Keywords/
│       │       ├── GCC.h
│       │       ├── MSVC.h
│       │       └── Unknown.h
│       ├── Standard/
│       │   ├── Attributes/
│       │   │   ├── GCC.h
│       │   │   ├── MSVC.h
│       │   │   └── Unknown.h
│       │   └── Keywords/
│       │       ├── GCC.h
│       │       ├── MSVC.h
│       │       └── Unknown.h
│       └── System/
│           ├── Arch.h
│           ├── Compiler.h
│           ├── Cpp.h
│           ├── Endian.h
│           ├── Os.h
│           ├── Sanitizer.h
│           └── Simd.h
├── CMakeLists.txt
├── Testing.cpp
└── README.md
```

## Usage

### Basic Inclusion

```cpp
// Include everything
#include <Quark/System.h>
#include <Quark/Types.h>
#include <Quark/Attributes.h>
#include <Quark/Atomic.h>
#include <Quark/Utils.h>

// Or include specific headers as needed
#include <Quark/Features.h>  // Feature detection only
```

### Example: System Detection

```cpp
#include <Quark/System.h>

// Query platform at compile time
#if ATOM_COMPILER_GCC_LIKE
    // GCC/Clang-specific code
#elif ATOM_COMPILER_MSVC_LIKE
    // MSVC-specific code
#endif

#if ATOM_BUILD_DEBUG
    // Debug build
#elif ATOM_BUILD_RELEASE
    // Release build
#endif

// Endianness queries
#if ATOM_ENDIAN_BIG
    // Big-endian platform
#else
    // Little-endian platform
#endif

// SIMD capability queries
#if ATOM_SIMD_AVX2
    // AVX2 available
#elif ATOM_SIMD_SSE2
    // SSE2 available
#endif
```

### Example: Using Type Aliases

```cpp
#include <Quark/Types.h>

// Portable fixed-width types
Quark::u8 byte = 255;           // Exactly 8 bits
Quark::u32 color = 0xFF0000FF;  // Exactly 32 bits
Quark::i64 timestamp = 123456;  // Exactly 64 bits

// Platform-dependent but optimized
Quark::uptr address = (Quark::uptr)&some_var;  // Word-sized unsigned
Quark::f32 value = 3.14f;                      // 32-bit float
Quark::iptr offset = some_ptr - other_ptr;    // Signed pointer-sized integer
```

### Example: Atomic Operations

```cpp
#include <Quark/Atomic.h>

// Atomic flag for thread synchronization
volatile int ready = 0;

// Thread 1: Signal readiness
Quark::Atomic::store<int>(&ready, 1, Quark::Atomic::RELEASE);

// Thread 2: Wait for signal
while (Quark::Atomic::load<int>(&ready, Quark::Atomic::ACQUIRE) == 0) {
    Quark::Atomic::pause();  // Yield CPU
}
```

### Example: Compiler Attributes

```cpp
#include <Quark/Attributes.h>

// Force inlining for performance-critical code
ATOM_FORCE_INLINE int hot_path(int x) {
    return x * 2;
}

// Mark as pure (no side effects, only depends on arguments)
ATOM_PURE int compute_hash(const char* str);

// Mark obsolete function
ATOM_DEPRECATED void old_function() {
    // Implementation
}

// Add likely/unlikely hints for branch prediction
if (ATOM_LIKELY(size > 0)) {
    process_items();
}
```

### Example: Feature Detection

```cpp
#include <Quark/Features.h>

// Conditional code based on compiler capabilities
#if ATOM_HAS_ATTRIBUTE(__noreturn__)
    #define MY_NORETURN __attribute__((__noreturn__))
#else
    #define MY_NORETURN
#endif

// Check if particular builtin is available
#if ATOM_HAS_BUILTIN(__builtin_expect)
    #define PREDICT(cond, val) __builtin_expect(cond, val)
#else
    #define PREDICT(cond, val) (cond)
#endif
```

## Build Integration

### CMake

The library uses CMake with Atom framework integration. Key build commands:

```bash
# Debug build
cmake -B Build/Debug -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build Build/Debug

# Release build
cmake -B Build/Release -S . -DCMAKE_BUILD_TYPE=Release
cmake --build Build/Release

# Generate compile_commands.json
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON <build_dir>
```

### Compiler Support

- **Primary:** GCC, Clang
- **Secondary:** MSVC (with partial fallbacks)
- **Fallback:** Generic/portable C implementations for unsupported compilers

### C++ Standard

- **Minimum:** C++98
- **Recommended:** C++11 or later (for optimized implementations)
- Detects and adapts to higher standards (C++14, C++17, C++20, etc.)

## Architecture

Quark uses a **facade pattern** with compiler-specific backends:

1. **Public headers** (e.g., `Atomic.h`, `BitOperations.h`) act as stable facades
2. Each facade selects a backend at compile time based on `ATOM_COMPILER_*` macros
3. **Three-tier fallback strategy:**
   - GCC/Clang optimized implementation (best performance)
   - MSVC optimized implementation (good performance on Windows)
   - Generic portable C implementation (maximum compatibility)

This design ensures:
- **Portability:** Code works across compilers and platforms
- **Performance:** Compiler-specific optimizations are always used when available
- **Maintainability:** Platform-specific code is isolated and centralized
- **Reliability:** Conservative fallbacks prevent silent failures

## Building from Source

### Prerequisites
- CMake >= 3.21
- C++ compiler (GCC, Clang, or MSVC)
- Atom framework CMake modules (in `~/.atom/CMake`)

### Build Steps

```bash
# Clone or navigate to the Quark directory
cd Quark

# Create and configure build directory
mkdir -p Build/Debug
cd Build/Debug
cmake ../.. -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build .

# (Optional) Create release build
cd ../Release
cmake ../.. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

## Performance Considerations

- **Header-only:** No compilation overhead; all optimizations are inlined
- **Zero runtime cost:** Wrapper macros compile down to direct compiler calls/intrinsics
- **SIMD support:** Automatic selection of fastest available instruction set
- **Bit operations:** Compiler builtins ensure efficient codegen (single CPU instruction)
- **Atomic operations:** Lock-free on supporting platforms; memory barriers only where needed

## License & Attribution

Part of the **Atom framework** plugin ecosystem. Consult the Atom documentation and licensing for additional information.

## Common Patterns

### Compile-Time Platform Selection

```cpp
#include <Quark/System.h>

#if ATOM_COMPILER_GCC_LIKE
    // GCC/Clang specific
#elif ATOM_COMPILER_MSVC_LIKE
    // MSVC specific
#else
    #error "Unsupported compiler"
#endif
```

### Conditional Feature Use

```cpp
#include <Quark/Features.h>

#if ATOM_HAS_CPP_ATTRIBUTE(carries_dependency)
#    define ATOM_CARRIES_DEPENDENCY [[carries_dependency]]
#elif ATOM_HAS_ATTRIBUTE(carries_dependency)
#    define ATOM_CARRIES_DEPENDENCY __attribute__((carries_dependency))
#else
#    define ATOM_CARRIES_DEPENDENCY
#endif
```
