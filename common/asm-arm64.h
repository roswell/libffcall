// Assembly language support for arm64 CPU.
// Bruno Haible 1999-05-29

// Copyright (C) 1999-2026 Bruno Haible <bruno@clisp.org>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// In order not to have to maintain several copies of the assembly language
// code, we use some macros which expand into the correct syntax.
// These macros are:
//   C(name)
//           This expands to the name of the C variable or function `name'.
//           On Unix BSD systems, this prepends an underscore.
//   L(label)
//           This expands to the name of a local label, having the name `label'.
//           On Unix ELF systems, where there is no underscore, names beginning
//           with an alphabetic character are automatically exported, so this
//           prepends a dot.
//   LDEF(label)
//           Defines a local label.
//   IMPORT_DATA(name)
//           Declare 'name' to be a global symbol, defined in a different
//           compilation unit.
//   GOTPAGE(variable)
//           This expands to a second argument for the 'adrp' instruction.
//   GOTPAGEOFF(variable)
//           This expands to an offset, to be used with GOTPAGE(variable).
//   GOTINDIR(register)
//           This expands to an indirect load instruction, on platforms which
//           use a "large" memory model.
//   PAGE(function)
//           This expands to a second argument for the 'adrp' instruction.
//   PAGEOFF(function)
//           This expands to an offset, to be used with PAGE(function).
//   TEXT()
//           Switch to the code section.
//   P2ALIGN(log,max)
//           Align to 2^log bytes, but insert at most max bytes.
//   GLOBL(name)
//           Declare `name' to be a global symbol.
//   DECLARE_FUNCTION(name)
//           Declare `name' to be a global function. When assembly language
//           code is compiled into a shared library, ELF linkers need to know
//           which symbols are functions.
//   FUNBEGIN(name)
//           Start the assembly language code for the C function `name'.
//   FUNEND(name)
//           End the assembly language code for the C function 'name'.
//   FILEEND()
//           End the entire file.

#ifdef ASM_UNDERSCORE
#define C(entrypoint) _##entrypoint
#define L(label) L##label
#define LDEF(label) L##label:
#else
#define C(entrypoint) entrypoint
#ifdef _MSC_VER
// MS assembler
#define L(label) |L##label|
#define LDEF(label) |L##label|
#else
#define L(label) .L##label
#define LDEF(label) .L##label:
#endif
#endif

#ifdef _MSC_VER
// MS assembler
#define IMPORT_DATA(name) IMPORT |name|
#else
#define IMPORT_DATA(name)
#endif

#ifdef _MSC_VER
// MS assembler
#define GOTPAGE(variable) variable
#define GOTPAGEOFF(variable) variable
#define GOTINDIR(register)
#define PAGE(function) function
#define PAGEOFF(function) function
#else
#if defined __APPLE__ && defined __MACH__
#define GOTPAGE(variable) variable@GOTPAGE
#define GOTPAGEOFF(variable) variable@GOTPAGEOFF
#define GOTINDIR(register) ldr register,[register]
#define PAGE(function) function@PAGE
#define PAGEOFF(function) function@PAGEOFF
#else
#define GOTPAGE(variable) variable
#define GOTPAGEOFF(variable) $:lo12:variable
#define GOTINDIR(register)
#define PAGE(function) function
#define PAGEOFF(function) $:lo12:function
#endif
#endif

#ifdef _MSC_VER
// MS assembler
#define TEXT() AREA |.text$mn|,CODE,ARM64
#else
#define TEXT() .text
#endif

#ifdef _MSC_VER
// MS assembler
// There is no equivalent for "p2align 4,,7".
#define P2ALIGN(log,max)
#else
// Mac OS X, Linux, Windows with GNU as or LLVM as
#define P2ALIGN(log,max) .p2align log,,max
#endif

#ifdef _WIN32
#ifdef _MSC_VER
// MS assembler
#define GLOBL(name) EXPORT |name| [FUNC]
#else
// LLVM assembler
#define GLOBL(name)
#endif
#else
#define GLOBL(name) .global name
#endif

// When assembly language code is compiled into a shared library, ELF linkers
// need to know which symbols are functions.
#ifdef _WIN32
#ifdef _MSC_VER
// MS assembler
#define DECLARE_FUNCTION(name)
#define FUNBEGIN(name) |C(name)| PROC
#define FUNEND(name) ENDP
#else
// LLVM assembler
// .scl 2      sets the symbol class to C_EXT (external).
// .type 32    sets the symbol type to DT_FCN (function).
#define DECLARE_FUNCTION(name) .def name; .scl 2; .type 32; .endef
#define FUNBEGIN(name) C(name):
#define FUNEND(name)
#endif
#else
#if defined(__ELF__) || !(defined(ASM_UNDERSCORE) || (defined __APPLE__ && defined __MACH__))
#define DECLARE_FUNCTION(name) .type C(name),%function
#define FUNEND(name) .size C(name),.-C(name)
#else
#define DECLARE_FUNCTION(name)
#define FUNEND(name)
#endif
#define FUNBEGIN(name) C(name):
#endif

#ifdef _MSC_VER
// MS assembler
#define FILEEND() END
#else
#define FILEEND()
#endif
