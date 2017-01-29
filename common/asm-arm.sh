#!/bin/sh
# Translate the assembler syntax of arm assembler programs
# Usage: asm-arm.sh < riscix-asm-file > portable-asm-file
# The portable-asm-file has to be
#   1. preprocessed,
#   2. grep -v '^ *#line' | grep -v '^#'
#   3. sed -e 's,% ,%,g' -e 's,//,@,g' -e 's,\$,#,g'

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
# ----------- Hide comments, to avoid trouble in preprocessing
s,@,//,g
# ----------- Turn # into $, to avoid trouble in preprocessing
s,#,\$,g
# ----------- Global symbols depends on ASM_UNDERSCORE
s/^\([A-Za-z0-9_:]\+\)/C(\1)/
s/\.L\([A-Za-z0-9_:]\+\)/L(\1)/
s/\.global[ 	]\([A-Za-z0-9_]*\)/.global C(\1)/
# ----------- Introduce macro syntax for assembler pseudo-ops
/\.file\([ 	]\+\)/d
s/^C(\([A-Za-z0-9_]*\):)/FUNBEGIN(\1)/
# ----------- Massage the beginning of functions
/\.type/{
s/\.type[ 	]\([A-Za-z0-9_]*\), *function/DECLARE_FUNCTION(\1)/
}
# ----------- Massage the end of functions
s/\.size[ 	]\([A-Za-z0-9_]*\),\(.*\)/FUNEND(\1)/
EOF

sed -f $tmpscript1 | \
sed -f $tmpscript2

eval "$tmpremove"
