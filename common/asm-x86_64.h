// Assembly language support for x86_64 CPU.
// Bruno Haible 2016-12-28

// Copyright (C) 1997-2017 Bruno Haible <bruno@clisp.org>
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
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
//           prepends a dot. Note that when defining a label, the `:' must
//           be inside the parentheses, not outside, because otherwise some
//           ANSI C preprocessor inserts a space between the label and the `:',
//           and some assemblers don't like this.
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
//   FUNEND(name,size_expression)
//           End the assembly language code for the C function 'name'.

#ifdef _MSC_VER
// MSVC
#define C(entrypoint) entrypoint
#define L(label) $L##label
#else
#ifdef ASM_UNDERSCORE
// Mac OS X
#define C(entrypoint) _##entrypoint
#define L(label) L##label
#else
// Linux/ELF, Solaris/ELF, Windows with GNU as
#define C(entrypoint) entrypoint
#define L(label) .L##label
#endif
#endif

#ifdef _MSC_VER
// MS assembler
#else
// GNU assembler version 2
#endif

#ifdef _MSC_VER
// No pseudo-ops available in MS inline assembler.
#define TEXT()
#else
#define TEXT() .text
#endif

#ifdef _MSC_VER
// No pseudo-ops available in MS inline assembler.
#define P2ALIGN(log,max)
#else
#if defined __sun
// Solaris
#define P2ALIGN(log,max) .align 1<<log
#else
// Mac OS X, Linux, Windows with GNU as
#define P2ALIGN(log,max) .p2align log,,max
#endif
#endif

#ifdef _MSC_VER
#define GLOBL(name)
#else
#define GLOBL(name) .globl name
#endif

// Define the DECLARE_FUNCTION(name) macro.
#ifdef _MSC_VER
// MSVC
#define DECLARE_FUNCTION(name)
#else
#if (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__)
// Windows with GNU as
#define DECLARE_FUNCTION(name) .def C(name); .scl 2; .type 32; .endef
#else
#ifdef ASM_UNDERSCORE
// Mac OS X
#define DECLARE_FUNCTION(name)
#else
// ELF
#define DECLARE_FUNCTION(name) .type C(name),@function
#endif
#endif
#endif

// Define the FUNBEGIN(name) and FUNEND() macros.
#ifdef _MSC_VER
// The "naked" attribute avoids the compiler generated prologue and epilogue.
#define FUNBEGIN(name) __declspec(naked) void name () { __asm {
#define FUNEND(name,size_expression)                  }       }
#else
#define FUNBEGIN(name) C(name):
#if (defined _WIN32 || defined __WIN32__ || defined __CYGWIN__) || defined(ASM_UNDERSCORE)
// Windows with GNU as, Mac OS X
#define FUNEND(name,size_expression)
#else
// ELF
#if defined __sun
// Solaris/ELF
#define FUNEND(name,size_expression) .size C(name), . - C(name)
#else
// Linux/ELF
#define FUNEND(name,size_expression) .size C(name),size_expression
#endif
#endif
#endif

// Section of frame info for exception handlers
#if defined __APPLE__ && defined __MACH__
// Mac OS X
#define EH_FRAME_SECTION __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
#else
#if defined __sun
// Solaris/ELF
#define EH_FRAME_SECTION .eh_frame,"aL",link=.text,@unwind
#else
// Linux/ELF
#define EH_FRAME_SECTION .eh_frame,"aw",@progbits
#endif
#endif
