#! /usr/bin/gawk -f
#
# This script uses GNU Awk features.

BEGIN {
    id_string = "libuninameslist"
    db_version = 1

    codepoint = -1
    codepoint_count = 0
}

/^[[:xdigit:]]+\t/ {
    match($0, /^([[:xdigit:]]+)\t(.*)/, field)
    codepoint = strtonum("0x" field[1])
    uniname[codepoint] = field[2]
    uniannot[codepoint] = ""
    uniannot_prefix = ""
    codepoint_count++
    next
}

/^[[:graph:]]/ {
    codepoint = -1
    next
}

0 <= codepoint {
    uniannot[codepoint] = uniannot[codepoint] uniannot_prefix $0
    uniannot_prefix = "\n"
    next
}

END {
    printf("%s%c", id_string, 0)
    print_uint(db_version)
    print_uint(codepoint_count)
    print_codepoint_array(uniname)
    name_offset = length(id_string) + 1 + 4*(2 + 3*codepoint_count)
    annot_offset = print_offsets(uniname, name_offset)
    print_offsets(uniannot, annot_offset)
    print_strings(uniname)
    print_strings(uniannot)
}

function print_codepoint_array(some_unilist)
{
    PROCINFO["sorted_in"] = "@ind_num_asc"
    for (codepoint in some_unilist)
        print_uint(codepoint)
}

function print_offsets(some_unilist, start_offset)
{
    PROCINFO["sorted_in"] = "@ind_num_asc"
    offset = start_offset
    for (codepoint in some_unilist) {
        len = length(some_unilist[codepoint])
        print_uint(offset)
        offset += len + 1
    }
    return offset
}

function print_strings(some_unilist)
{
    PROCINFO["sorted_in"] = "@ind_num_asc"
    for (codepoint in some_unilist)
        printf("%s%c", some_unilist[codepoint], 0)
}

function print_uint(n)
{
    n = n + 0
    byte0 = and(n, 0xff)
    byte1 = and(rshift(n,8), 0xff)
    byte2 = and(rshift(n,16), 0xff)
    byte3 = and(rshift(n,24), 0xff)
    printf("%c%c%c%c", byte0, byte1, byte2, byte3)
}
