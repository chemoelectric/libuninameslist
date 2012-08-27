#include <uninameslookup.h>

int
main (int argc, char *argv[])
{
  int exit_code = 0;
  try
  {
    uninameslookup db1 (argv[1]);
    uninameslookup *db2 = new uninameslookup (argv[1]);
    delete db2;
  }
  catch (const char *e)
  {
    exit_code = 1;
  }
  return exit_code;
}

// local variables:
// c-file-style: "gnu"
// end:
