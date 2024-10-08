/* Instruction cache flushing for powerpc, not on AIX */

/*
 * Copyright 1997-2024 Bruno Haible <bruno@clisp.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

void __TR_clear_cache_3 (char* first_addr)
{
  /* Taken from egcs-1.1.2/gcc/config/rs6000/tramp.asm. */
  /* The number of asm statements here depends on the value of TRAMP_LENGTH
     for __powerpcsysv4__. */
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+4));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+8));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+12));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+16));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+20));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+24));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+28));
  asm volatile ("icbi 0,%0; dcbf 0,%0" : : "r" (first_addr+32));
  asm volatile ("sync; isync");
}
