# libmicrodns

LIBMICRODNS_VERSION := 0.1.2
<<<<<<< master
LIBMICRODNS_URL := $(GITHUB)/videolabs/libmicrodns/releases/download/$(LIBMICRODNS_VERSION)/microdns-$(LIBMICRODNS_VERSION).tar.xz
=======
LIBMICRODNS_URL := https://github.com/videolabs/libmicrodns/releases/download/$(LIBMICRODNS_VERSION)/microdns-$(LIBMICRODNS_VERSION).tar.xz
>>>>>>> origin/3.0.x

ifndef HAVE_DARWIN_OS
ifdef BUILD_NETWORK
PKGS += microdns
endif
endif
ifeq ($(call need_pkg,"microdns >= 0.1.2"),)
PKGS_FOUND += microdns
endif

$(TARBALLS)/microdns-$(LIBMICRODNS_VERSION).tar.xz:
	$(call download_pkg,$(LIBMICRODNS_URL),microdns)

.sum-microdns: $(TARBALLS)/microdns-$(LIBMICRODNS_VERSION).tar.xz

microdns: microdns-$(LIBMICRODNS_VERSION).tar.xz .sum-microdns
	$(UNPACK)
	$(MOVE)

.microdns: microdns crossfile.meson
<<<<<<< master
	$(MESONCLEAN)
	$(HOSTVARS_MESON) $(MESON) -Dauto_features=disabled
	+$(MESONBUILD)
=======
	cd $< && rm -rf ./build
	cd $< && $(HOSTVARS_MESON) $(MESON) -Dauto_features=disabled build
	cd $< && cd build && ninja install
>>>>>>> origin/3.0.x
	touch $@
