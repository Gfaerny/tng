#pragma once
#include <stdio.h>

void TNG_MSG_NOARG_ERROR() {printf ("tng: Error , you get not argument.add flag --help for more info \n");}
void TNG_MSG_HELPARG () {printf ("tng\nUsage : tng [FILENAME]... [OPTION]...\nConfigable crossplatform cli filemaker\n   -c, --nano config file  \n   -h, --help       display this help and exit\n");}

