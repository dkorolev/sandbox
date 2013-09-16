/*
HOLA coding challenge small strings library.

HEADER NOTE: The problem statement reads:

   At the top of the page, you see 4 includes - indicating the functions 
   that can be used to implement str_cpy() and str_cat():
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include <stdarg.h>

   Although this does imply standard library string functions can be used,
   the code below does not make use of library functions except malloc()/free().

Interface:

  void str_cpy(char** pstr, const char* s);
    Copies string s into (*pstr).
    In debug mode will perror() and exit() if pstr or s is NULL.
    Allocates memory using malloc() for (*pstr) if (*pstr) is NULL.
    Does not free the memory if (*pstr) is not NULL, it's up to the user
    to call str_free(pstr).

  void str_cat(char** pstr, const char* s);
    Concatenates s with (*pstr).
    Assumes sufficient memory for (*pstr) has been allocated.
    In debug mode will perror() and exit() if pstr or (*pstr) or s is NULL.

  void str_printf(char** pstr, const char* fmt, const char* param);
    A very simplistic printf() implementation, without using stdarg features.
    In debug mode will perror() and exit() if pstr or fmt or param is NULL.
    Allocates memory using malloc() for (*pstr) if necessary.
    Supports one and only one "%s" in the input string.
    "%s" gets replaced by the param string, "%*" becomes the '%' sign.

  void str_free(char** pstr);
    Frees the string if it has been allocated.
    In debug mode will perror() and exit() if pstr is NULL.
    Does nothing if (*pstr) has already been a NULL pointer.

Debug mode is triggered by -DHOLA_DEBUG.
In debug mode the code would perror() and then exit()
when pstr is a NULL pointer and on a few more function-specific checks.
Also, str_printf() will fail when attempting to create too long of a string.

The str_cpy() and str_printf() functions will allocate memory
when null (*pstr) is passed. The allocation is done via malloc().

No memory reallocation is performed.
The caller is responsible for the buffers to have sufficient space.

IMPORTANT NOTE 1: The code is not safe wrt the intersecting buffers.
                  It uses simple while (*dst++ = *src++) loop.

IMPORTANT NOTE 2: str_printf() is single-threaded and not reentrant.
                  In fact, it uses an internal static buffer of fixed size.
*/

#ifndef HOLA_STR_LIB_H
#define HOLA_STR_LIB_H

#define MAX_PRINTF_OUTPUT_LENGTH 1000

#ifdef HOLA_DEBUG
  #include <stdio.h>
  #include <stdlib.h>
  #define HOLA_STR_FAILURE (-1)
#endif

void str_cpy(char** pstr, const char* s)
{
  char* dst;

#ifdef HOLA_DEBUG
  if (!pstr)
  {
    perror("NULL pointer to pointer passed to str_cpy as pstr.\n");
    exit(HOLA_STR_FAILURE);
  }
  if (!s)
  {
    perror("NULL pointer passed to str_cpy as s.\n");
    exit(HOLA_STR_FAILURE);
  }
#endif
  
  if (!*pstr)
  {
    const char* s_0 = s;
    while (*s_0) ++s_0;
    dst = malloc(s_0 - s + 1);
    *pstr = dst;
  }
  else
  {
    dst = *pstr;
  }
  while (*dst++ = *s++);
}

void str_cat(char** pstr, const char* s)
{
#ifdef HOLA_DEBUG
  char* p;
  if (!pstr)
  {
    perror("NULL pointer to pointer passed to str_cat as pstr.\n");
    exit(HOLA_STR_FAILURE);
  }
  if (!*pstr)
  {
    /* str_cat() does not allocate memory. str_cpy() should be unsed instead. */
    perror("Pointer to a NULL pointer passed to str_cat as pstr.\n");
    exit(HOLA_STR_FAILURE);
  }
  if (!s)
  {
    perror("NULL pointer to pointer passed to str_cat as s.\n");
    exit(HOLA_STR_FAILURE);
  }
#else
  char* p = *pstr;
#endif

  while (*p) ++p;
  while (*p++ = *s++);
}

void str_printf(char** pstr, const char* fmt, const char* param)
{
  static char result[MAX_PRINTF_OUTPUT_LENGTH];
  char* dst = result;

#ifdef HOLA_DEBUG
  const char* dst_end = result + MAX_PRINTF_OUTPUT_LENGTH;
#endif

  const char* tmp;

#ifdef HOLA_DEBUG
  if (!pstr)
  {
    perror("NULL pointer to pointer passed to str_printf as pstr.\n");
    exit(HOLA_STR_FAILURE);
  }
  if (!fmt)
  {
    perror("NULL pointer passed to str_printf as fmt.\n");
    exit(HOLA_STR_FAILURE);
  }
  if (!param)
  {
    perror("NULL pointer passed to str_printf as param.\n");
    exit(HOLA_STR_FAILURE);
  }
#endif

  while (*fmt)
  {
    if (*fmt == '%')
    {
      ++fmt;
      if (*fmt == 's')
      {
        ++fmt;
        tmp = param;
#ifdef HOLA_DEBUG
        while (*dst++ = *tmp++)
        {
          if (dst == dst_end)
          {
            perror("Resulting string exceeds MAX_PRINTF_OUTPUT_LENGTH.");
            exit(HOLA_STR_FAILURE);
          }
        }
#else
        while (*dst++ = *tmp++);
#endif
        --dst;
      }
      else
      {
        ++fmt;
        *dst++ = '%';
#ifdef HOLA_DEBUG
        if (dst == dst_end)
        {
          perror("Resulting string exceeds MAX_PRINTF_OUTPUT_LENGTH.");
          exit(HOLA_STR_FAILURE);
        }
#endif
      }
    }
    else
    {
      *dst++ = *fmt++;
#ifdef HOLA_DEBUG
      if (dst == dst_end)
      {
        perror("Resulting string exceeds MAX_PRINTF_OUTPUT_LENGTH.");
        exit(HOLA_STR_FAILURE);
      }
#endif
    }
  }
  *dst = '\0';
  str_cpy(pstr, result);
}

void str_free(char** pstr)
{
#ifdef HOLA_DEBUG
  if (!pstr)
  {
    perror("NULL pointer to pointer passed to str_free.\n");
    exit(HOLA_STR_FAILURE);
  }
#endif
  free(*pstr);
}

#endif  /* #ifndef HOLA_STR_LIB_H */
