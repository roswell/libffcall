void func (void) {}

/*
cross alpha-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-alpha.o
cross arm-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-arm.o
cross armv7l-linux-gnueabihf gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-armv7.o
cross hppa-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-hppa.o
cross i386-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-i386.o
cross ia64-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-ia64.o
cross loongarch64-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-loongarch64.o
cross m68k-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-m68k.o
cross mips64-linux gcc -mabi=32 -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-mips32.o
cross mips64-linux gcc -mabi=n32 -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-mipsn32.o
cross mips64-linux gcc -mabi=64 -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-mips64.o
cross powerpc-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-powerpc.o
cross powerpc64le-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-powerpc64le.o
cross riscv32-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-riscv32.o
cross riscv64-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-riscv64.o
cross s390-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-s390.o
cross sparc-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-sparc.o
cross sparc64-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-sparc64.o
cross x86_64-linux gcc -O6 -fomit-frame-pointer voidfunc.c -c -o voidfunc-x86_64.o
*/
