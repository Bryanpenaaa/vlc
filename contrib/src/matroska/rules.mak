# matroska

<<<<<<< master
MATROSKA_VERSION := 1.7.0
=======
MATROSKA_VERSION := 1.6.3
>>>>>>> origin/3.0.x
MATROSKA_URL := http://dl.matroska.org/downloads/libmatroska/libmatroska-$(MATROSKA_VERSION).tar.xz

PKGS += matroska

ifeq ($(call need_pkg,"libmatroska"),)
PKGS_FOUND += matroska
endif

DEPS_matroska = ebml $(DEPS_ebml)

$(TARBALLS)/libmatroska-$(MATROSKA_VERSION).tar.xz:
	$(call download_pkg,$(MATROSKA_URL),matroska)

.sum-matroska: libmatroska-$(MATROSKA_VERSION).tar.xz

matroska: libmatroska-$(MATROSKA_VERSION).tar.xz .sum-matroska
	$(UNPACK)
	$(call pkg_static,"libmatroska.pc.in")
	$(MOVE)

.matroska: matroska toolchain.cmake
<<<<<<< master
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
	cd $< && $(HOSTVARS_PIC) $(CMAKE)
	cd $< && $(CMAKEBUILD) . --target install
>>>>>>> origin/3.0.x
	touch $@
