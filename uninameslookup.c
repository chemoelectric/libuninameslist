// Copyright 2012 Barry Schwartz
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// The name of the author may not be used to endorse or promote products
// derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#if ! defined (__cplusplus)
#if ! defined (__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#error C99 or C++ is required.
#endif
#endif

#include "config.h"
#include "uninameslookup.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct uninameslookup_names___db
{
  unsigned int version;
  unsigned int codepoint_count;
  unsigned int *codepoints;
  unsigned int *name_offsets;
  unsigned int *annot_offsets;
  char *strings;
} uninameslookup_names___db;

static const char *names_db_id_string = "libuninameslist names db       ";

static bool
string_matches (FILE * f, const char *s)
{
  const size_t s_len = strlen (s);
  char buffer[s_len + 1];
  size_t num_bytes = fread (buffer, 1, s_len + 1, f);
  return (num_bytes == s_len + 1 && memcmp (buffer, s, s_len + 1) == 0);
}

static bool
read_uint (FILE * f, unsigned int *i)
{
  unsigned char buffer[4];
  size_t num_bytes = fread (buffer, 1, 4, f);
  if (num_bytes == 4)
    *i =
      (unsigned int) buffer[0] | ((unsigned int) buffer[1] << 8) |
      ((unsigned int) buffer[2] << 16) | ((unsigned int) buffer[3] << 24);
  return (num_bytes == 4);
}

static bool
read_uint_array (FILE * f, unsigned int **i_array, size_t size)
{
  *i_array = (unsigned int *) malloc (size * sizeof (unsigned int));
  bool successful = (*i_array != NULL);
  size_t j = 0;
  while (successful && j < size)
    {
      successful = read_uint (f, &(*i_array)[j]);
      j++;
    }
  if (!successful)
    {
      free (*i_array);
      *i_array = NULL;
    }
  return successful;
}

static bool
read_strings (FILE * f, char **strings, size_t size)
{
  *strings = (char *) malloc (size);
  bool successful = (*strings != NULL);
  if (successful)
    {
      size_t num_bytes = fread (*strings, 1, size, f);
      successful = (num_bytes == size);
    }
  return successful;
}

static bool
read_names_db_tables (FILE * f, uninameslookup_names_db handle)
{
  unsigned int strings_size;

  bool successful = (read_uint (f, &handle->version) && handle->version == 1);
  if (successful)
    successful = read_uint (f, &handle->codepoint_count);
  if (successful)
    successful =
      read_uint_array (f, &handle->codepoints, handle->codepoint_count);
  if (successful)
    successful =
      read_uint_array (f, &handle->name_offsets, handle->codepoint_count);
  if (successful)
    successful =
      read_uint_array (f, &handle->annot_offsets, handle->codepoint_count);
  if (successful)
    successful = read_uint (f, &strings_size);
  if (successful)
    successful = read_strings (f, &handle->strings, strings_size);
  return successful;
}

uninameslookup_names_db
uninameslookup_names_db_open (const char *filename)
{
  uninameslookup_names_db handle = NULL;

  FILE *f = fopen (filename, "rb");
  if (f != NULL)
    {
      if (string_matches (f, names_db_id_string))
        {
          handle =
            (uninameslookup_names_db)
            malloc (sizeof (uninameslookup_names___db));
          if (handle != NULL)
            {
              handle->codepoints = NULL;
              handle->name_offsets = NULL;
              handle->annot_offsets = NULL;
              handle->strings = NULL;
              bool successful = read_names_db_tables (f, handle);
              if (!successful)
                {
                  uninameslookup_names_db_close (handle);
                  handle = NULL;
                }
            }
        }
      fclose (f);
    }

  return handle;
}

void
uninameslookup_names_db_close (uninameslookup_names_db handle)
{
  free (handle->codepoints);
  free (handle->name_offsets);
  free (handle->annot_offsets);
  free (handle->strings);
  free (handle);
}

static int
compare_codepoints (const void *codepoint1, const void *codepoint2)
{
  const unsigned int *cp1 = (const unsigned int *) codepoint1;
  const unsigned int *cp2 = (const unsigned int *) codepoint2;
  return ((*cp1 < *cp2) ? -1 : ((*cp1 == *cp2) ? 0 : 1));
}

static int
codepoint_index (uninameslookup_names_db handle, unsigned int codepoint)
{
  int index = -1;
  unsigned int *p = (unsigned int *) bsearch (&codepoint, handle->codepoints,
                                              handle->codepoint_count,
                                              sizeof (unsigned int),
                                              compare_codepoints);
  if (p != NULL)
    index = p - handle->codepoints;
  return index;
}

static inline unsigned int
name_offset_at_index (uninameslookup_names_db handle, int index)
{
  return handle->name_offsets[index];
}

static inline unsigned int
annot_offset_at_index (uninameslookup_names_db handle, int index)
{
  return handle->annot_offsets[index];
}

static inline const char *
name_at_index (uninameslookup_names_db handle, int index)
{
  return (const char *) (handle->strings +
                         name_offset_at_index (handle, index));
}

static inline const char *
annot_at_index (uninameslookup_names_db handle, int index)
{
  return (const char *) (handle->strings +
                         annot_offset_at_index (handle, index));
}

const char *
uninameslookup_name (uninameslookup_names_db handle, unsigned int codepoint)
{
  const char *name = NULL;
  int index = codepoint_index (handle, codepoint);
  if (0 <= index)
    name = name_at_index (handle, index);
  return name;
}

const char *
uninameslookup_annot (uninameslookup_names_db handle, unsigned int codepoint)
{
  const char *annot = NULL;
  int index = codepoint_index (handle, codepoint);
  if (0 <= index)
    annot = annot_at_index (handle, index);
  return annot;
}

// local variables:
// c-file-style: "gnu"
// end:

// Please run "indent --gnu-style uninameslookup.c" occasionally.

// Please also try compiling with CC=g++, to verify that the code is
// of high enough quality to be compiled as either C99 or C++.
