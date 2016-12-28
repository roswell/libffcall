#!/bin/sh
# Translate the assembler syntax of x86_64 assembler programs
# Usage: asm-x86_64.sh < linux-x86_64-asm-file > portable-asm-file
# The portable-asm-file has to be
#   1. preprocessed,
#   2. grep -v '^ *#line' | grep -v '^#'
#   3. sed -e 's,% ,%,g' -e 's,//.*$,,'

tmpscript1=sed$$tmp1
tmpscript2=sed$$tmp2
tmpremove='rm -f $tmpscript1 $tmpscript2'
trap "$tmpremove" 1 2 15

cat > $tmpscript1 << \EOF
# ----------- Remove gcc self-identification
/gcc2_compiled/d
/gnu_compiled_c/d
/\.ident/d
EOF

cat > $tmpscript2 << \EOF
# ----------- Global symbols depends on ASM_UNDERSCORE
s/\.globl \([A-Za-z0-9_]*\)/.globl C(\1)/
# ----------- Massage the beginning of functions
/\.type/{
s/\.type	\([A-Za-z0-9_]*\),@function/DECLARE_FUNCTION(\1)\
FUNBEGIN(\1)/
n
d
}
# ----------- Massage the end of functions
s/\.size	\([A-Za-z0-9_]*\),\(.*\)/FUNEND(\1,\2)/
# ----------- Section of frame info for exception handlers
s/\.section	\.eh_frame,"aw",@progbits/.section	EH_FRAME_SECTION/
EOF

sed -f $tmpscript1 | \
sed -f $tmpscript2

eval "$tmpremove"
