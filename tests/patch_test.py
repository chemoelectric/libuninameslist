# FIXME: Include a test that the patches are complete -- that they
# cover the entire annotation.

# FIXME: Include a test that the patches do not overflow -- that they
# cover only the annotation and nothing past it.


import uninameslookup
import random, string, sys

def make_patch(db, codepoint):
    name = db.name(codepoint)
    annot = db.annot(codepoint)
    patch = None
    if name is not None and annot is not None:
        patch = "{:04X}\t{}\n{}".format(codepoint, name, annot)
    return patch

db_file = sys.argv[1]
nameslist_file = sys.argv[2]
random_codepoint_count = int(sys.argv[3])

random.seed()

db = uninameslookup.uninameslookup(db_file)
nameslist = file(nameslist_file).read()

failure_count = 0

# Test the codepoints up to 0x10FFFF.
codepoint = 0
while codepoint <= 0x10FFFF:
    patch = make_patch(db, codepoint)
    if patch is not None:
        if nameslist.find(patch) < 0:
            print("Failure: codepoint = " + str(codepoint))
            failure_count += 1
    codepoint += 1

# Test random codepoints.
i = 0
while i <= random_codepoint_count:
    codepoint = random.randint(0, 0xffffffff)
    #print codepoint
    patch = make_patch(db, codepoint)
    if patch is not None:
        if nameslist.find(patch) < 0:
            print("Failure: codepoint = " + str(codepoint))
            failure_count += 1
    i += 1

print("failure_count = " + str(failure_count))

exit_code = 0
if failure_count != 0:
    exit_code = 1

exit(exit_code)
