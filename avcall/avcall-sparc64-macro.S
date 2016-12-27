#include "asmsparc.h"
	.file	"avcall-sparc64.c"
.section	".text"
	.align 4
	.align 32
	.global __builtin_avcall
	DECLARE_FUNCTION(__builtin_avcall)
	.proc	04
__builtin_avcall:
	.register	%g2, $scratch
	.register	%g3, $scratch
	save	%sp, -192, %sp
	ldx	[%i0+40], %g1
	add	%i0, 64, %g2
	lduw	[%i0+60], %g3
	sub	%g1, %g2, %g1
	cmp	%g3, 0
	be,pt	%icc, .LL2
	 srlx	%g1, 3, %o7
	andcc	%g3, 1, %g0
	bne,pt	%xcc, .LL161
	 andcc	%g3, 2, %g0
	bne,pt	%xcc, .LL162
	 andcc	%g3, 4, %g0
.LL222:
	bne,pt	%xcc, .LL163
	 andcc	%g3, 8, %g0
.LL221:
	bne,pt	%xcc, .LL164
	 andcc	%g3, 16, %g0
.LL220:
	bne,pt	%xcc, .LL165
	 andcc	%g3, 32, %g0
.LL219:
	bne,pt	%xcc, .LL166
	 andcc	%g3, 64, %g0
.LL218:
	bne,pt	%xcc, .LL167
	 andcc	%g3, 128, %g0
.LL217:
	bne,pt	%xcc, .LL168
	 andcc	%g3, 256, %g0
.LL216:
	bne,pt	%xcc, .LL169
	 andcc	%g3, 512, %g0
.LL215:
	bne,pt	%xcc, .LL170
	 andcc	%g3, 1024, %g0
.LL226:
	bne,pt	%xcc, .LL171
	 andcc	%g3, 2048, %g0
.LL225:
	bne,pt	%xcc, .LL172
	 sethi	%hi(4096), %g1
.LL224:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL173
	 sethi	%hi(8192), %g1
.LL223:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL174
	 sethi	%hi(16384), %g1
.LL228:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL175
	 sethi	%hi(32768), %g1
.LL227:
	andcc	%g3, %g1, %g0
	bne,pt	%icc, .LL176
	 nop
.LL2:
	cmp	%o7, 6
.LL229:
	bg,pn	%icc, .LL213
	 add	%o7, -6, %g1
	ldx	[%i0], %g1
.LL212:
	ldx	[%i0+64], %o0
	ldx	[%i0+72], %o1
	ldx	[%i0+80], %o2
	ldx	[%i0+88], %o3
	ldx	[%i0+96], %o4
	call	%g1, 0
	 ldx	[%i0+104], %o5
	mov	%o0, %l1
	nop
	lduw	[%i0+24], %g1
	cmp	%g1, 1
	be,pn	%icc, .LL38
	 cmp	%g1, 0
	be,a,pt	%icc, .LL214
	 ldx	[%i0+16], %g1
	cmp	%g1, 2
	be,pn	%icc, .LL153
	 cmp	%g1, 3
	be,pn	%icc, .LL153
	 cmp	%g1, 4
	be,pn	%icc, .LL153
	 cmp	%g1, 5
	be,pn	%icc, .LL154
	 cmp	%g1, 6
	be,pn	%icc, .LL154
	 cmp	%g1, 7
	be,pn	%icc, .LL155
	 cmp	%g1, 8
	be,pn	%icc, .LL155
	 cmp	%g1, 9
	be,pn	%icc, .LL159
	 cmp	%g1, 10
	be,pn	%icc, .LL159
	 cmp	%g1, 11
	be,pn	%icc, .LL159
	 cmp	%g1, 12
	be,pn	%icc, .LL159
	 cmp	%g1, 13
	be,pn	%icc, .LL178
	 cmp	%g1, 14
	be,pn	%icc, .LL179
	 cmp	%g1, 15
	be,pn	%icc, .LL159
	 cmp	%g1, 16
	bne,pt	%icc, .LL38
	 nop
	lduw	[%i0+8], %g1
	andcc	%g1, 1, %g0
	be,pt	%xcc, .LL71
	 andcc	%g1, 512, %g0
	ldx	[%i0+32], %g1
	cmp	%g1, 1
	be,pn	%xcc, .LL180
	 cmp	%g1, 2
	be,pn	%xcc, .LL181
	 cmp	%g1, 4
	be,pn	%xcc, .LL182
	 cmp	%g1, 8
	be,pn	%xcc, .LL183
	 add	%g1, 7, %g1
	srlx	%g1, 3, %g1
	addcc	%g1, -1, %g4
	bneg,pn	%icc, .LL38
	 sra	%g4, 0, %g1
	ldx	[%i0+16], %i0
	sllx	%g1, 3, %g2
	add	%o0, %g2, %g3
.LL82:
	ldx	[%g3], %g1
	add	%g4, -1, %g4
	add	%g3, -8, %g3
	cmp	%g4, -1
	stx	%g1, [%g2+%i0]
	bne,pt	%icc, .LL82
	 add	%g2, -8, %g2
.LL38:
	return	%i7+8
	 mov	0, %o0
.LL159:
	ldx	[%i0+16], %g1
.LL214:
	stx	%l1, [%g1]
	return	%i7+8
	 mov	0, %o0
.LL176:
	ldd [%i0+184],%f30
	cmp	%o7, 6
	ble,a,pt %icc, .LL212
	 ldx	[%i0], %g1
	add	%o7, -6, %g1
.LL213:
	mov	6, %g4
	sra	%g1, 0, %g1
	mov	0, %g3
	sllx	%g1, 3, %g1
	add	%g1, 15, %g1
	and	%g1, -16, %g1
	sub	%sp, %g1, %sp
	add	%sp, 2238, %g2
	and	%g2, -16, %g5
.LL37:
	add	%g3, %i0, %g1
	add	%g4, 1, %g4
	ldx	[%g1+112], %g2
	cmp	%o7, %g4
	stx	%g2, [%g3+%g5]
	bne,pt	%icc, .LL37
	 add	%g3, 8, %g3
	ba,pt	%xcc, .LL212
	 ldx	[%i0], %g1
.LL168:
	ldd [%i0+120],%f14
	andcc	%g3, 256, %g0
	be,pt	%xcc, .LL215
	 andcc	%g3, 512, %g0
	ba,pt	%xcc, .LL169
	 nop
.LL167:
	ldd [%i0+112],%f12
	andcc	%g3, 128, %g0
	be,pt	%xcc, .LL216
	 andcc	%g3, 256, %g0
	ba,pt	%xcc, .LL168
	 nop
.LL166:
	ldd [%i0+104],%f10
	andcc	%g3, 64, %g0
	be,pt	%xcc, .LL217
	 andcc	%g3, 128, %g0
	ba,pt	%xcc, .LL167
	 nop
.LL165:
	ldd [%i0+96],%f8
	andcc	%g3, 32, %g0
	be,pt	%xcc, .LL218
	 andcc	%g3, 64, %g0
	ba,pt	%xcc, .LL166
	 nop
.LL164:
	ldd [%i0+88],%f6
	andcc	%g3, 16, %g0
	be,pt	%xcc, .LL219
	 andcc	%g3, 32, %g0
	ba,pt	%xcc, .LL165
	 nop
.LL163:
	ldd [%i0+80],%f4
	andcc	%g3, 8, %g0
	be,pt	%xcc, .LL220
	 andcc	%g3, 16, %g0
	ba,pt	%xcc, .LL164
	 nop
.LL162:
	ldd [%i0+72],%f2
	andcc	%g3, 4, %g0
	be,pt	%xcc, .LL221
	 andcc	%g3, 8, %g0
	ba,pt	%xcc, .LL163
	 nop
.LL161:
	ldd [%i0+64],%f0
	andcc	%g3, 2, %g0
	be,pt	%xcc, .LL222
	 andcc	%g3, 4, %g0
	ba,pt	%xcc, .LL162
	 nop
.LL172:
	ldd [%i0+152],%f22
	sethi	%hi(4096), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL223
	 sethi	%hi(8192), %g1
	ba,pt	%xcc, .LL173
	 nop
.LL171:
	ldd [%i0+144],%f20
	andcc	%g3, 2048, %g0
	be,pt	%xcc, .LL224
	 sethi	%hi(4096), %g1
	ba,pt	%xcc, .LL172
	 nop
.LL170:
	ldd [%i0+136],%f18
	andcc	%g3, 1024, %g0
	be,pt	%xcc, .LL225
	 andcc	%g3, 2048, %g0
	ba,pt	%xcc, .LL171
	 nop
.LL169:
	ldd [%i0+128],%f16
	andcc	%g3, 512, %g0
	be,pt	%xcc, .LL226
	 andcc	%g3, 1024, %g0
	ba,pt	%xcc, .LL170
	 nop
.LL174:
	ldd [%i0+168],%f26
	sethi	%hi(16384), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL227
	 sethi	%hi(32768), %g1
	ba,pt	%xcc, .LL175
	 nop
.LL173:
	ldd [%i0+160],%f24
	sethi	%hi(8192), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL228
	 sethi	%hi(16384), %g1
	ba,pt	%xcc, .LL174
	 nop
.LL175:
	ldd [%i0+176],%f28
	sethi	%hi(32768), %g1
	andcc	%g3, %g1, %g0
	be,pt	%icc, .LL229
	 cmp	%o7, 6
	ba,pt	%xcc, .LL176
	 nop
.LL153:
	ldx	[%i0+16], %g1
	stb	%l1, [%g1]
	return	%i7+8
	 mov	0, %o0
.LL154:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 sth	%l1, [%g1]
.LL155:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 st	%l1, [%g1]
.LL178:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 st	%f0, [%g1]
.LL179:
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 std	%f0, [%g1]
.LL71:
	be,pn	%xcc, .LL38
	 nop
	ldx	[%i0+32], %g2
	add	%g2, -1, %g1
	cmp	%g1, 31
	bgu,pn	%xcc, .LL38
	 cmp	%g2, 1
	be,pn	%xcc, .LL184
	 cmp	%g2, 2
	be,pn	%xcc, .LL185
	 cmp	%g2, 3
	be,pn	%xcc, .LL186
	 cmp	%g2, 4
	be,pn	%xcc, .LL187
	 cmp	%g2, 5
	be,pn	%xcc, .LL188
	 cmp	%g2, 6
	be,pn	%xcc, .LL189
	 cmp	%g2, 7
	be,pn	%xcc, .LL190
	 add	%g2, -8, %g1
	cmp	%g1, 24
	bgu,pn	%xcc, .LL38
	 srax	%o0, 56, %g1
	ldx	[%i0+16], %g2
	srax	%o0, 48, %g3
	stb	%g1, [%g2]
	srax	%o0, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o0, 32, %g5
	srax	%o0, 24, %o7
	stb	%g3, [%g1+1]
	srax	%o0, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o0, 8, %g3
	stb	%g4, [%g2+2]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+3]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+4]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+5]
	ldx	[%i0+16], %g2
	stb	%g3, [%g2+6]
	ldx	[%i0+16], %g1
	stb	%o0, [%g1+7]
	ldx	[%i0+32], %g1
	cmp	%g1, 8
	be,pn	%xcc, .LL38
	 cmp	%g1, 9
	be,pn	%xcc, .LL191
	 cmp	%g1, 10
	be,pn	%xcc, .LL192
	 cmp	%g1, 11
	be,pn	%xcc, .LL193
	 cmp	%g1, 12
	be,pn	%xcc, .LL194
	 cmp	%g1, 13
	be,pn	%xcc, .LL195
	 cmp	%g1, 14
	be,pn	%xcc, .LL196
	 cmp	%g1, 15
	be,pn	%xcc, .LL197
	 add	%g1, -16, %g1
	cmp	%g1, 16
	bgu,pn	%xcc, .LL38
	 srax	%o1, 56, %g1
	ldx	[%i0+16], %g2
	srax	%o1, 48, %g3
	stb	%g1, [%g2+8]
	srax	%o1, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o1, 32, %g5
	srax	%o1, 24, %o7
	stb	%g3, [%g1+9]
	srax	%o1, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o1, 8, %g3
	stb	%g4, [%g2+10]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+11]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+12]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+13]
	ldx	[%i0+16], %g2
	stb	%g3, [%g2+14]
	ldx	[%i0+16], %g1
	stb	%o1, [%g1+15]
	ldx	[%i0+32], %g1
	cmp	%g1, 16
	be,pn	%xcc, .LL38
	 cmp	%g1, 17
	be,pn	%xcc, .LL198
	 cmp	%g1, 18
	be,pn	%xcc, .LL199
	 cmp	%g1, 19
	be,pn	%xcc, .LL200
	 cmp	%g1, 20
	be,pn	%xcc, .LL201
	 cmp	%g1, 21
	be,pn	%xcc, .LL202
	 cmp	%g1, 22
	be,pn	%xcc, .LL203
	 cmp	%g1, 23
	be,pn	%xcc, .LL204
	 add	%g1, -24, %g1
	cmp	%g1, 8
	bgu,pn	%xcc, .LL38
	 srax	%o2, 56, %g1
	ldx	[%i0+16], %g2
	srax	%o2, 48, %g3
	stb	%g1, [%g2+16]
	srax	%o2, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o2, 32, %g5
	srax	%o2, 24, %o7
	stb	%g3, [%g1+17]
	srax	%o2, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o2, 8, %g3
	stb	%g4, [%g2+18]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+19]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+20]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+21]
	ldx	[%i0+16], %g2
	stb	%g3, [%g2+22]
	ldx	[%i0+16], %g1
	stb	%o2, [%g1+23]
	ldx	[%i0+32], %g1
	cmp	%g1, 24
	be,pn	%xcc, .LL38
	 cmp	%g1, 25
	be,pn	%xcc, .LL205
	 cmp	%g1, 26
	be,pn	%xcc, .LL206
	 cmp	%g1, 27
	be,pn	%xcc, .LL207
	 cmp	%g1, 28
	be,pn	%xcc, .LL208
	 cmp	%g1, 29
	be,pn	%xcc, .LL209
	 cmp	%g1, 30
	be,pn	%xcc, .LL210
	 cmp	%g1, 31
	be,pn	%xcc, .LL211
	 cmp	%g1, 32
	bne,pt	%xcc, .LL38
	 srax	%o3, 56, %g1
	ldx	[%i0+16], %g2
	srax	%o3, 48, %g3
	stb	%g1, [%g2+24]
	srax	%o3, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o3, 32, %g5
	srax	%o3, 24, %o7
	stb	%g3, [%g1+25]
	srax	%o3, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o3, 8, %g3
	stb	%g4, [%g2+26]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+27]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+28]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+29]
	ldx	[%i0+16], %g2
	stb	%g3, [%g2+30]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%o3, [%g1+31]
.LL180:
	ldx	[%i0+16], %g2
	ldub	[%o0], %g1
	ba,pt	%xcc, .LL38
	 stb	%g1, [%g2]
.LL181:
	ldx	[%i0+16], %g2
	lduh	[%o0], %g1
	ba,pt	%xcc, .LL38
	 sth	%g1, [%g2]
.LL183:
	ldx	[%i0+16], %g2
	ldx	[%o0], %g1
	ba,pt	%xcc, .LL38
	 stx	%g1, [%g2]
.LL182:
	ldx	[%i0+16], %g2
	lduw	[%o0], %g1
	ba,pt	%xcc, .LL38
	 st	%g1, [%g2]
.LL211:
	ldx	[%i0+16], %g2
	srax	%o3, 56, %g1
	srax	%o3, 48, %g3
	stb	%g1, [%g2+24]
	srax	%o3, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o3, 32, %g5
	srax	%o3, 24, %o7
	stb	%g3, [%g1+25]
	srax	%o3, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o3, 8, %g3
	stb	%g4, [%g2+26]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+27]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+28]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+29]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g3, [%g2+30]
.LL210:
	ldx	[%i0+16], %g2
	srax	%o3, 56, %g1
	srax	%o3, 48, %g3
	stb	%g1, [%g2+24]
	srax	%o3, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o3, 32, %g5
	srax	%o3, 24, %o7
	stb	%g3, [%g1+25]
	srax	%o3, 16, %l0
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+26]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+27]
	ldx	[%i0+16], %g1
	stb	%o7, [%g1+28]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%l0, [%g2+29]
.LL209:
	ldx	[%i0+16], %g2
	srax	%o3, 56, %g1
	srax	%o3, 48, %g3
	stb	%g1, [%g2+24]
	srax	%o3, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o3, 32, %g5
	srax	%o3, 24, %o7
	stb	%g3, [%g2+25]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+26]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+27]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%o7, [%g1+28]
.LL208:
	ldx	[%i0+16], %g2
	srax	%o3, 56, %g1
	srax	%o3, 48, %g3
	stb	%g1, [%g2+24]
	srax	%o3, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o3, 32, %g5
	stb	%g3, [%g2+25]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+26]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g5, [%g2+27]
.LL207:
	ldx	[%i0+16], %g2
	srax	%o3, 56, %g1
	srax	%o3, 48, %g3
	stb	%g1, [%g2+24]
	srax	%o3, 40, %g4
	ldx	[%i0+16], %g1
	stb	%g3, [%g1+25]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g2+26]
.LL206:
	ldx	[%i0+16], %g3
	srax	%o3, 56, %g2
	srax	%o3, 48, %g4
	stb	%g2, [%g3+24]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g1+25]
.LL205:
	ldx	[%i0+16], %g2
	srax	%o3, 56, %g1
	ba,pt	%xcc, .LL38
	 stb	%g1, [%g2+24]
.LL204:
	ldx	[%i0+16], %g2
	srax	%o2, 56, %g1
	srax	%o2, 48, %g3
	stb	%g1, [%g2+16]
	srax	%o2, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o2, 32, %g5
	srax	%o2, 24, %o7
	stb	%g3, [%g1+17]
	srax	%o2, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o2, 8, %g3
	stb	%g4, [%g2+18]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+19]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+20]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+21]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g3, [%g2+22]
.LL203:
	ldx	[%i0+16], %g2
	srax	%o2, 56, %g1
	srax	%o2, 48, %g3
	stb	%g1, [%g2+16]
	srax	%o2, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o2, 32, %g5
	srax	%o2, 24, %o7
	stb	%g3, [%g1+17]
	srax	%o2, 16, %l0
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+18]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+19]
	ldx	[%i0+16], %g1
	stb	%o7, [%g1+20]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%l0, [%g2+21]
.LL202:
	ldx	[%i0+16], %g2
	srax	%o2, 56, %g1
	srax	%o2, 48, %g3
	stb	%g1, [%g2+16]
	srax	%o2, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o2, 32, %g5
	srax	%o2, 24, %o7
	stb	%g3, [%g2+17]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+18]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+19]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%o7, [%g1+20]
.LL201:
	ldx	[%i0+16], %g2
	srax	%o2, 56, %g1
	srax	%o2, 48, %g3
	stb	%g1, [%g2+16]
	srax	%o2, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o2, 32, %g5
	stb	%g3, [%g2+17]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+18]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g5, [%g2+19]
.LL200:
	ldx	[%i0+16], %g2
	srax	%o2, 56, %g1
	srax	%o2, 48, %g3
	stb	%g1, [%g2+16]
	srax	%o2, 40, %g4
	ldx	[%i0+16], %g1
	stb	%g3, [%g1+17]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g2+18]
.LL199:
	ldx	[%i0+16], %g3
	srax	%o2, 56, %g2
	srax	%o2, 48, %g4
	stb	%g2, [%g3+16]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g1+17]
.LL198:
	ldx	[%i0+16], %g2
	srax	%o2, 56, %g1
	ba,pt	%xcc, .LL38
	 stb	%g1, [%g2+16]
.LL197:
	ldx	[%i0+16], %g2
	srax	%o1, 56, %g1
	srax	%o1, 48, %g3
	stb	%g1, [%g2+8]
	srax	%o1, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o1, 32, %g5
	srax	%o1, 24, %o7
	stb	%g3, [%g1+9]
	srax	%o1, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o1, 8, %g3
	stb	%g4, [%g2+10]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+11]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+12]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+13]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g3, [%g2+14]
.LL196:
	ldx	[%i0+16], %g2
	srax	%o1, 56, %g1
	srax	%o1, 48, %g3
	stb	%g1, [%g2+8]
	srax	%o1, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o1, 32, %g5
	srax	%o1, 24, %o7
	stb	%g3, [%g1+9]
	srax	%o1, 16, %l0
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+10]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+11]
	ldx	[%i0+16], %g1
	stb	%o7, [%g1+12]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%l0, [%g2+13]
.LL195:
	ldx	[%i0+16], %g2
	srax	%o1, 56, %g1
	srax	%o1, 48, %g3
	stb	%g1, [%g2+8]
	srax	%o1, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o1, 32, %g5
	srax	%o1, 24, %o7
	stb	%g3, [%g2+9]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+10]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+11]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%o7, [%g1+12]
.LL194:
	ldx	[%i0+16], %g2
	srax	%o1, 56, %g1
	srax	%o1, 48, %g3
	stb	%g1, [%g2+8]
	srax	%o1, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o1, 32, %g5
	stb	%g3, [%g2+9]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+10]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g5, [%g2+11]
.LL193:
	ldx	[%i0+16], %g2
	srax	%o1, 56, %g1
	srax	%o1, 48, %g3
	stb	%g1, [%g2+8]
	srax	%o1, 40, %g4
	ldx	[%i0+16], %g1
	stb	%g3, [%g1+9]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g2+10]
.LL192:
	ldx	[%i0+16], %g3
	srax	%o1, 56, %g2
	srax	%o1, 48, %g4
	stb	%g2, [%g3+8]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g1+9]
.LL191:
	ldx	[%i0+16], %g2
	srax	%o1, 56, %g1
	ba,pt	%xcc, .LL38
	 stb	%g1, [%g2+8]
.LL190:
	ldx	[%i0+16], %g2
	srax	%o0, 56, %g1
	srax	%o0, 48, %g3
	stb	%g1, [%g2]
	srax	%o0, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o0, 32, %g5
	srax	%o0, 24, %o7
	stb	%g3, [%g1+1]
	srax	%o0, 16, %l0
	ldx	[%i0+16], %g2
	srax	%o0, 8, %g3
	stb	%g4, [%g2+2]
	ldx	[%i0+16], %g1
	stb	%g5, [%g1+3]
	ldx	[%i0+16], %g2
	stb	%o7, [%g2+4]
	ldx	[%i0+16], %g1
	stb	%l0, [%g1+5]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g3, [%g2+6]
.LL189:
	ldx	[%i0+16], %g2
	srax	%o0, 56, %g1
	srax	%o0, 48, %g3
	stb	%g1, [%g2]
	srax	%o0, 40, %g4
	ldx	[%i0+16], %g1
	srax	%o0, 32, %g5
	srax	%o0, 24, %o7
	stb	%g3, [%g1+1]
	srax	%o0, 16, %l0
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+2]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+3]
	ldx	[%i0+16], %g1
	stb	%o7, [%g1+4]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%l0, [%g2+5]
.LL188:
	ldx	[%i0+16], %g2
	srax	%o0, 56, %g1
	srax	%o0, 48, %g3
	stb	%g1, [%g2]
	srax	%o0, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o0, 32, %g5
	srax	%o0, 24, %o7
	stb	%g3, [%g2+1]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+2]
	ldx	[%i0+16], %g2
	stb	%g5, [%g2+3]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%o7, [%g1+4]
.LL187:
	ldx	[%i0+16], %g2
	srax	%o0, 56, %g1
	srax	%o0, 48, %g3
	stb	%g1, [%g2]
	srax	%o0, 40, %g4
	ldx	[%i0+16], %g2
	srax	%o0, 32, %g5
	stb	%g3, [%g2+1]
	ldx	[%i0+16], %g1
	stb	%g4, [%g1+2]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g5, [%g2+3]
.LL186:
	ldx	[%i0+16], %g2
	srax	%o0, 56, %g1
	srax	%o0, 48, %g3
	stb	%g1, [%g2]
	srax	%o0, 40, %g4
	ldx	[%i0+16], %g1
	stb	%g3, [%g1+1]
	ldx	[%i0+16], %g2
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g2+2]
.LL185:
	ldx	[%i0+16], %g3
	srax	%o0, 56, %g2
	srax	%o0, 48, %g4
	stb	%g2, [%g3]
	ldx	[%i0+16], %g1
	ba,pt	%xcc, .LL38
	 stb	%g4, [%g1+1]
.LL184:
	ldx	[%i0+16], %g2
	srax	%o0, 56, %g1
	ba,pt	%xcc, .LL38
	 stb	%g1, [%g2]
	.size	__builtin_avcall, .-__builtin_avcall
	.ident	"GCC: (GNU) 4.1.3 20070620 prerelease (NetBSD nb1 20070620)"
