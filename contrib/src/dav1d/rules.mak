# libdav1d

DAV1D_VERSION := 1.0.0
DAV1D_URL := $(VIDEOLAN)/dav1d/$(DAV1D_VERSION)/dav1d-$(DAV1D_VERSION).tar.xz
<<<<<<< HEAD
DAV1D_HASH := bf5ae021edff111d3954b32fef09debcc4981738
DAV1D_VERSION := $(DAV1D_HASH)
DAV1D_GITURL := https://code.videolan.org/videolan/dav1d.git
=======
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

PKGS += dav1d
ifeq ($(call need_pkg,"dav1d"),)
PKGS_FOUND += dav1d
endif

DAV1D_CONF = -D enable_tests=false -D enable_tools=false

$(TARBALLS)/dav1d-$(DAV1D_VERSION).tar.xz:
<<<<<<< HEAD
	# $(call download_pkg,$(DAV1D_URL),dav1d)
	$(call download_git,$(DAV1D_GITURL),,$(DAV1D_HASH))

.sum-dav1d: dav1d-$(DAV1D_VERSION).tar.xz
	$(call check_githash,$(DAV1D_VERSION))
	touch $@
=======
	$(call download_pkg,$(DAV1D_URL),dav1d)
#	$(call download_git,$(DAV1D_GITURL),,$(DAV1D_HASH))

.sum-dav1d: dav1d-$(DAV1D_VERSION).tar.xz
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4

dav1d: dav1d-$(DAV1D_VERSION).tar.xz .sum-dav1d
	$(UNPACK)
	$(MOVE)

.dav1d: dav1d crossfile.meson
<<<<<<< HEAD
	$(MESONCLEAN)
	$(HOSTVARS_MESON) $(MESON) $(DAV1D_CONF)
	+$(MESONBUILD)
=======
	cd $< && rm -rf ./build
	cd $< && $(HOSTVARS_MESON) $(MESON) $(DAV1D_CONF) build
	cd $< && cd build && ninja install
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
	touch $@
