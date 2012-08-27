#include <uninameslookup.h>
#include <stdio.h>

int
main (int argc, char *argv[])
{
  int exit_code = 1;
  uninameslookup_names_db db = uninameslookup_names_db_open (argv[1]);
  if (db != NULL)
    {
      exit_code = 0;
      uninameslookup_names_db_close (db);
    };
  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
