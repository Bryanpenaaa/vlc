# GNU Multiple Precision Arithmetic

<<<<<<< master
GMP_VERSION := 6.2.1
GMP_URL := https://gmplib.org/download/gmp/gmp-$(GMP_VERSION).tar.xz
=======
GMP_VERSION := 6.1.2
GMP_URL := https://gmplib.org/download/gmp-$(GMP_VERSION)/gmp-$(GMP_VERSION).tar.bz2
>>>>>>> origin/3.0.x

GMP_CONF :=

ifdef HAVE_CLANG
ifeq ($(ARCH),mipsel)
GMP_CONF += --disable-assembly
endif
ifeq ($(ARCH),mips64el)
GMP_CONF += --disable-assembly
endif
endif

ifdef HAVE_WIN32
ifeq ($(ARCH),arm)
GMP_CONF += --disable-assembly
endif
endif

<<<<<<< master
$(TARBALLS)/gmp-$(GMP_VERSION).tar.xz:
=======
$(TARBALLS)/gmp-$(GMP_VERSION).tar.bz2:
>>>>>>> origin/3.0.x
	$(call download_pkg,$(GMP_URL),gmp)

.sum-gmp: gmp-$(GMP_VERSION).tar.xz

gmp: gmp-$(GMP_VERSION).tar.xz .sum-gmp
	$(UNPACK)
<<<<<<< master
	$(APPLY) $(SRC)/gmp/gmp-fix-asm-detection.patch
	# do not try the cross compiler to detect the build compiler
	sed -i.orig 's/"$$CC" "$$CC $$CFLAGS $$CPPFLAGS" cc gcc c89 c99/cc gcc c89 c99/' $(UNPACK_DIR)/acinclude.m4
=======
	$(APPLY) $(SRC)/gmp/ppc64.patch
	$(APPLY) $(SRC)/gmp/win-arm64.patch
	$(APPLY) $(SRC)/gmp/arm64-Add-GSYM_PREFIX-to-function-calls-in-assembly.patch
ifdef HAVE_DARWIN_OS
	$(APPLY) $(SRC)/gmp/arm64-Change-adrp-add-relocations-to-darwin-style.patch
endif
	# do not try the cross compiler to detect the build compiler
	cd $(UNPACK_DIR) && sed -i.orig 's/"$$CC" "$$CC $$CFLAGS $$CPPFLAGS" cc gcc c89 c99/cc gcc c89 c99/' acinclude.m4
>>>>>>> origin/3.0.x
	$(MOVE)

# GMP requires either GPLv2 or LGPLv3
.gmp: gmp
ifndef GPL
	$(REQUIRE_GNUV3)
endif
	$(RECONF)
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(GMP_CONF)
	+$(MAKEBUILD)
	+$(MAKEBUILD) install
=======
	cd $< && $(HOSTVARS) ./configure $(HOSTCONF) $(GMP_CONF)
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
