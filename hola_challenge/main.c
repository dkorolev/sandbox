/* Via hola.org/hola_5min_challenge.html */

/* Copyright (C) Hola 2012, 2013
 *
 * Welcome to TheCodeIL.com Challenge!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "hola_str_lib.h"

int main(int argc, char *argv[])
{
  char *s = NULL;
  str_cpy(&s, "Hola Hola");
  str_cpy(&s, s+5);
  str_cat(&s, " World");
  str_printf(&s, "%s!", s);
  puts(s); /* result: "Hola World!" */
  str_free(&s);
  return 0;
}

