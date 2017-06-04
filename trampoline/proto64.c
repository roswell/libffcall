/* Sample prototype for a trampoline. */

/*
 * Copyright 1995-1996 Bruno Haible <bruno@clisp.org>
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#define function  (int (*) ()) 0xbabebec0dea0ffabL
#define variable  *(void**)    0x1234567813578765L
#define data      (void*)      0x7355471143622155L

int tramp ()
{ variable = data;
  return (*function)();
}

int jump ()
{ goto *function; }

