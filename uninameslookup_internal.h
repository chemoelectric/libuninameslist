#ifndef _UNINAMESLOOKUP_INTERNAL_H
#define _UNINAMESLOOKUP_INTERNAL_H 1

//#define _(String) (String)
//#define N_(String) String
//#define textdomain(Domain)
//#define bindtextdomain(Package, Directory)

#include <libintl.h>
#define _(String) gettext (String)
#define gettext_noop(String) String
#define N_(String) gettext_noop (String)

#endif /* _UNINAMESLOOKUP_INTERNAL_H */
