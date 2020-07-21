/*
  main.c: Program for the ENG10032 2020/1 First Exam
  
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

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <galileo2io.h>
#include <gpio_utils.h>
#include <int_utils.h>
#include <pwm_utils.h>
#include <ad_utils.h>

int main(int argc, char *argv[]) {

    char s[20];

    if(strncmp(s,"Galileo",sizeof s) != 0) {
        printf("You must be using a Galileo Gen1 Board to execute this program.\n");
        return -1;
    }

    

    return 0;
}