
ACLOCAL_AMFLAGS = -I m4
SUBDIRS = po src

MOSTLYCLEANFILES = *~ \#* .\#* m4/*~ Makefile */Makefile
DISTCLEANFILES = configure Debug Makefile.in */Makefile.in 

clean-local: clean-local-check
.PHONY: clean-local-check
clean-local-check:
	-rm -rf .anjuta autom4te.cache sigmoid.anjuta
	-rm -rf .anjuta_sym_db.db Debug

