/*
  int_utils.h: Utility functions for Galileo interruptions
  
  Copyright (c) 2020 Natalia Gubiani Rampon <ngrampon@inf.ufrgs.br>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#ifndef INT_UTILS_H
#define INT_UTILS_H

#ifdef __cplusplus
extern "C"
{
#endif

extern int write_int_edge(int gpio, const char edge[]);
extern int config_rising_edge(int gpio);
extern int config_falling_edge(int gpio);
extern int disable_interruption(int gpio);

#ifdef __cplusplus
};
#endif

#endif