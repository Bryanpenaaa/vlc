# libtasn1

LIBTASN1_VERSION := 4.19.0
LIBTASN1_URL := $(GNU)/libtasn1/libtasn1-$(LIBTASN1_VERSION).tar.gz

ifeq ($(call need_pkg,"libtasn1 >= 4.3"),)
PKGS_FOUND += libtasn1
endif

$(TARBALLS)/libtasn1-$(LIBTASN1_VERSION).tar.gz:
	$(call download_pkg,$(LIBTASN1_URL),libtasn1)

.sum-libtasn1: libtasn1-$(LIBTASN1_VERSION).tar.gz

libtasn1: libtasn1-$(LIBTASN1_VERSION).tar.gz .sum-libtasn1
	$(UNPACK)
<<<<<<< master
	$(APPLY) $(SRC)/libtasn1/0001-fcntl-do-not-call-GetHandleInformation-in-Winstore-a.patch
=======
	$(APPLY) $(SRC)/libtasn1/no-executables.patch
>>>>>>> origin/3.0.x
	$(MOVE)

LIBTASN1_CONF := --disable-doc

.libtasn1: libtasn1
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(LIBTASN1_CONF)
	+$(MAKEBUILD) bin_PROGRAMS=
	+$(MAKEBUILD) bin_PROGRAMS= install
=======
	$(RECONF)
	cd $< && $(HOSTVARS) ./configure $(HOSTCONF) --disable-doc
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
