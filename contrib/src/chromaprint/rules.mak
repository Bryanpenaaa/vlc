# chromaprint

CHROMAPRINT_VERSION := 1.4.2
CHROMAPRINT_URL := $(GITHUB)/acoustid/chromaprint/releases/download/v$(CHROMAPRINT_VERSION)/chromaprint-$(CHROMAPRINT_VERSION).tar.gz

PKGS += chromaprint
ifeq ($(call need_pkg,"libchromaprint"),)
PKGS_FOUND += chromaprint
endif

$(TARBALLS)/chromaprint-$(CHROMAPRINT_VERSION).tar.gz:
	$(call download_pkg,$(CHROMAPRINT_URL),chromaprint)

.sum-chromaprint: chromaprint-$(CHROMAPRINT_VERSION).tar.gz

chromaprint: chromaprint-$(CHROMAPRINT_VERSION).tar.gz .sum-chromaprint
	$(UNPACK)
	$(APPLY) $(SRC)/chromaprint/linklibs.patch
<<<<<<< master
	$(APPLY) $(SRC)/chromaprint/0002-add-the-C-runtime-to-the-packages-to-link-to.patch
=======
>>>>>>> origin/3.0.x
	$(MOVE)

DEPS_chromaprint = ffmpeg $(DEPS_ffmpeg)

<<<<<<< master
.chromaprint: chromaprint toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
.chromaprint: chromaprint .ffmpeg toolchain.cmake
	cd $< && $(HOSTVARS_PIC) $(CMAKE)
	cd $< && $(CMAKEBUILD) . --target install
>>>>>>> origin/3.0.x
	touch $@
