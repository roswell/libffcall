// Assembly language support for x86_64 CPU.
// Bruno Haible 2016-12-28

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
//   P2ALIGN(log,max)
//           Align to 2^log bytes, but insert at most max bytes.
//   DECLARE_FUNCTION(name)
//           Declare `name' to be a global function. When assembly language
//           code is compiled into a shared library, ELF linkers need to know
//           which symbols are functions.
//   FUNBEGIN(name)
//           Start the assembly language code for the C function `name'.
//   FUNEND(name,size_expression)
//           End the assembly language code for the C function 'name'.

#ifdef ASM_UNDERSCORE
// Mac OS X
#define C(entrypoint) _##entrypoint
#define L(label) L##label
#else
// Linux/ELF
#define C(entrypoint) entrypoint
#define L(label) .L##label
#endif

#if defined __sun
// Solaris
#define P2ALIGN(log,max) .align 1<<log
#else
// Mac OS X, Linux
#define P2ALIGN(log,max) .p2align log,,max
#endif

// When assembly language code is compiled into a shared library, ELF linkers
// need to know which symbols are functions.
#ifdef ASM_UNDERSCORE
// Mac OS X
#define DECLARE_FUNCTION(name)
#define FUNEND(name,size_expression)
#else
// ELF
#define DECLARE_FUNCTION(name) .type C(name),@function
#if defined __sun
// Solaris/ELF
#define FUNEND(name,size_expression) .size C(name), . - C(name)
#else
// Linux/ELF
#define FUNEND(name,size_expression) .size C(name),size_expression
#endif
#endif
#define FUNBEGIN(name) C(name##:)

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
