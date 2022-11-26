#!/bin/sh
# Translate the assembler syntax of arm64 assembler programs
# Usage: asm-arm64.sh < linux-arm64-asm-file > portable-asm-file
# The portable-asm-file has to be
#   1. preprocessed,
#   2. grep -v '^ *#line' | grep -v '^#'
#   3. sed -e 's,% ,%,g' -e 's,//,@,g' -e 's,\$,#,g'

# Copyright (C) 1999-2022 Bruno Haible <bruno@clisp.org>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

tmpscript1=sed$$tmp1
tmpscript2=sed$$tmp2
tmpscript3=sed$$tmp3
tmpremove='rm -f $tmpscript1 $tmpscript2 $tmpscript3'
trap "$tmpremove" HUP INT TERM

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
s/^\([A-Za-z0-9_]\+\)/C(\1)/
s/\.L\([A-Za-z0-9_]\+\)/L(\1)/
s/\.global[ 	]\([A-Za-z0-9_]*\)/.global C(\1)/
# ----------- Introduce macro syntax for assembler pseudo-ops
/\.file\([ 	]\+\)/d
/\.section\([ 	]\+\).*GNU-stack/d
s/^C(\([A-Za-z0-9_]*\)):/FUNBEGIN(\1)/
# ----------- Massage the beginning of functions
/\.type/{
s/\.type[ 	]\([A-Za-z0-9_]*\), *%function/DECLARE_FUNCTION(\1)/
}
# ----------- Massage the end of functions
s/\.size[ 	]\([A-Za-z0-9_]*\),\(.*\)/FUNEND(\1)/
EOF

cat > $tmpscript3 << \EOF
# ----------- Introduce macro syntax for PIC addressing of functions
s/^	adrp	\([a-z0-9]*\), *\([A-Za-z0-9_]*\)/	adrp	\1, PAGE(C(\2))/
s/[$]:lo12:\([A-Za-z0-9_]*\)/PAGEOFF(C(\1))/
s/:lo12:\([A-Za-z0-9_]*\)/PAGEOFF(C(\1))/
# ----------- Introduce macro syntax for PIC addressing of variables
s/PAGE(C(\(vacall_function\)))/GOTPAGE(C(\1))/
s/	ldr	\([a-z0-9]*\), \[\(.*\)PAGEOFF(C(\(vacall_function\)))\].*/	ldr	\1, [\2GOTPAGEOFF(C(\3))]\n	GOTINDIR(\1)/
EOF

sed -f $tmpscript1 | \
sed -f $tmpscript2 | \
sed -f $tmpscript3

eval "$tmpremove"
