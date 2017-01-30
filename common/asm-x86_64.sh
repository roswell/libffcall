#!/bin/sh
# Translate the assembler syntax of x86_64 assembler programs
# Usage: asm-x86_64.sh < linux-x86_64-asm-file > portable-asm-file
# The portable-asm-file has to be
#   1. preprocessed,
#   2. grep -v '^ *#line' | grep -v '^#'
#   3. sed -e 's,% ,%,g' -e 's,//.*$,,'

tmpscript1=sed$$tmp1
tmpscript2=sed$$tmp2
tmpscript3=sed$$tmp3
tmpremove='rm -f $tmpscript1 $tmpscript2 $tmpscript3'
trap "$tmpremove" 1 2 15

cat > $tmpscript1 << \EOF
# ----------- Remove gcc self-identification
/gcc2_compiled/d
/gnu_compiled_c/d
/\.ident/d
EOF

cat > $tmpscript2 << \EOF
# ----------- Global symbols depends on ASM_UNDERSCORE
s/^\([A-Za-z0-9_:]\+\)/C(\1)/
s/\.L\([A-Za-z0-9_:]\+\)/L(\1)/
s/\.globl \([A-Za-z0-9_]*\)/.globl C(\1)/
# ----------- Massage the beginning of functions
/\.type/{
s/\.type	\([A-Za-z0-9_]*\), *@function/DECLARE_FUNCTION(\1)/
}
# ----------- Massage the end of functions
s/\.size	\([A-Za-z0-9_]*\),\(.*\)/FUNEND(\1,\2)/
# ----------- Section of frame info for exception handlers
s/\.section	\.eh_frame,"a[w]*",@progbits/.section	EH_FRAME_SECTION/
# ----------- Disable the frame info for exception handlers on Solaris
# (as the Solaris linker expects a different format, see
# https://illumos.org/issues/3210)
# Likewise this section does not assemble on Mac OS X 10.5.
/EH_FRAME_SECTION/{
s/^/#if !(defined __sun || (defined __APPLE__ \&\& defined __MACH__))\
/
}
${
s/$/\
#endif/
}
EOF

cat > $tmpscript3 << \EOF
# ----------- Introduce macro syntax for assembler pseudo-ops
s/\.p2align \([^,]*\),,\(.*\)/P2ALIGN(\1,\2)/
s/^C(\([A-Za-z0-9_]*\):)/FUNBEGIN(\1)/
EOF

sed -f $tmpscript1 | \
sed -f $tmpscript2 | \
sed -f $tmpscript3

eval "$tmpremove"
