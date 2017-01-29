// Assembly language support for sparc CPU.
// Bruno Haible 1999-05-29

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
//   DECLARE_FUNCTION(name)
//           Declare `name' to be a global function. When assembly language
//           code is compiled into a shared library, ELF linkers need to know
//           which symbols are functions.
//   FUNBEGIN(name)
//           Start the assembly language code for the C function `name'.
//   FUNEND(name)
//           End the assembly language code for the C function 'name'.

#ifdef ASM_UNDERSCORE
// SunOS4, Linux/a.out
#define C(entrypoint) _##entrypoint
#define L(label) L##label
#else
// Solaris, Linux/ELF
#define C(entrypoint) entrypoint
#define L(label) .L##label
#endif

// When assembly language code is compiled into a shared library, ELF linkers
// need to know which symbols are functions.
#if defined(__NetBSD__) || defined(__OpenBSD__)
#define DECLARE_FUNCTION(name) .type C(name),@function
#define FUNEND(name) .size C(name),.-C(name)
#elif defined(__svr4__) || defined(__ELF__)
// Solaris, Linux/ELF
// Some preprocessors keep the backslash in place, some don't.
// Some complain about the # being not in front of an ANSI C macro.
// Therefore we use a dollar, which will be sed-converted to # later.
#define DECLARE_FUNCTION(name) .type C(name),$function
#define FUNEND(name) .size C(name),.-C(name)
#else
// SunOS4, Linux/a.out
#define DECLARE_FUNCTION(name)
#define FUNEND(name)
#endif
#define FUNBEGIN(name) C(name##:)
