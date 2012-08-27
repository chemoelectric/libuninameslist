// FIXME: Include a test that the patches are complete -- that they
// cover the entire annotation.
//
// FIXME: Include a test that the patches do not overflow -- that they
// cover only the annotation and nothing past it.

#include <uninameslookup.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *
make_patch (uninameslookup_names_db db, unsigned int codepoint)
{
  char *patch = NULL;
  const char *name = uninameslookup_name (db, codepoint);
  const char *annot = uninameslookup_annot (db, codepoint);
  if (name != NULL && annot != NULL)
    {
      patch = (char *) malloc (strlen (name) + strlen (annot) + 100);
      (void) sprintf (patch, "%04X\t%s\n%s", codepoint, name, annot);
    }
  return patch;
}

int
main (int argc, char *argv[])
{
  int exit_code = 1;

  const char *db_file = argv[1];
  const char *nameslist_file = argv[2];
  //unsigned int random_codepoint_count;
  //(void) sscanf(argv[3], "%u", &random_codepoint_count);

  uninameslookup_names_db db = uninameslookup_names_db_open (db_file);
  if (db != NULL)
    {
      char nameslist[2000000];
      memset (nameslist, 0, sizeof nameslist);
      FILE *f = fopen (nameslist_file, "rb");
      (void) fread (nameslist, 1, sizeof nameslist, f);
      fclose (f);

      int failure_count = 0;

      // Test the codepoints up to 0x10FFFF.
      for (int codepoint = 0; codepoint <= 0x10FFFF; codepoint++)
        {
          char *patch = make_patch (db, codepoint);
          if (patch != NULL)
            {
              if (strstr (nameslist, patch) == NULL)
                {
                  (void) printf ("Failure: codepoint = %X\n", codepoint);
                  failure_count++;
                }
              free (patch);
            }
        }

      if (failure_count == 0)
        exit_code = 0;

      uninameslookup_names_db_close (db);
    }

  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
