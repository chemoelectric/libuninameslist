/*
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
*/

#ifndef _UNINAMESLOOKUP_H
#define _UNINAMESLOOKUP_H

#ifdef __cplusplus
extern "C"
{
#endif

  /* A names db handle. */
  typedef struct uninameslookup_names___db *uninameslookup_names_db;

  /* Open a names db. */
  uninameslookup_names_db uninameslookup_names_db_open (const char *filename);

  /* Close a names db. */
  void uninameslookup_names_db_close (uninameslookup_names_db handle);

  /* Retrieve the name of a Unicode codepoint. */
  const char *uninameslookup_name (uninameslookup_names_db handle,
                                   unsigned int codepoint);

  /* Retrieve the annotation of a Unicode codepoint. */
  const char *uninameslookup_annot (uninameslookup_names_db handle,
                                    unsigned int codepoint);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

class uninameslookup
{
private:

  uninameslookup_names_db db;

public:

  inline uninameslookup (const char *filename)
  {
    db = uninameslookup_names_db_open (filename);
    if (!db)
      // FIXME: Is this what really should be thrown here? It may
      // change in the future.
      throw "uninameslookup constructor failed";
  }

  inline ~ uninameslookup ()
  {
    uninameslookup_names_db_close (db);
  }

  inline const char *name (unsigned int codepoint)
  {
    return uninameslookup_name (db, codepoint);
  }

  inline const char *annot (unsigned int codepoint)
  {
    return uninameslookup_annot (db, codepoint);
  }
};

#endif /* __cplusplus */

#endif /* _UNINAMESLOOKUP_H */

/* local variables:    */
/* c-file-style: "gnu" */
/* end:                */

/* Please run "indent --gnu-style uninameslookup.h" occasionally. */
