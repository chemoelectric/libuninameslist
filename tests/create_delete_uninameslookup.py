import uninameslookup
import sys

exit_code = 0

try:
    db = uninameslookup.uninameslookup(sys.argv[1])
    del db
except:
    exit_code = 1

exit(exit_code)
