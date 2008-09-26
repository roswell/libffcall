	.file	"cache-arm.c"
	.text
	.align	2
	.global	__TR_clear_cache
	.type	__TR_clear_cache, %function
__TR_clear_cache:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 0, uses_anonymous_args = 0
	@ link register save eliminated.
	@ lr needed for prologue
#APP
	swi #10420226
	mov	pc, lr
	.size	__TR_clear_cache, .-__TR_clear_cache
	.ident	"GCC: (GNU) 3.4.0 (Debian 20040516)"
