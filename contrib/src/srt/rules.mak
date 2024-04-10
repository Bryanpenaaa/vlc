# srt

SRT_VERSION := 1.4.4
SRT_URL := $(GITHUB)/Haivision/srt/archive/v$(SRT_VERSION).tar.gz

ifdef BUILD_NETWORK
PKGS += srt
endif

<<<<<<< master
ifeq ($(call need_pkg,"srt >= 1.3.2"),)
=======
ifeq ($(call need_pkg,"srt >= 1.3.1"),)
>>>>>>> origin/3.0.x
PKGS_FOUND += srt
endif

DEPS_srt = gnutls $(DEPS_gnutls)
ifdef HAVE_WIN32
<<<<<<< master
DEPS_srt += winpthreads $(DEPS_winpthreads)
endif


=======
DEPS_srt += pthreads $(DEPS_pthreads)
endif

>>>>>>> origin/3.0.x
$(TARBALLS)/srt-$(SRT_VERSION).tar.gz:
	$(call download_pkg,$(SRT_URL),srt)

.sum-srt: srt-$(SRT_VERSION).tar.gz

srt: srt-$(SRT_VERSION).tar.gz .sum-srt
	$(UNPACK)
<<<<<<< master
	$(APPLY) $(SRC)/srt/0001-core-remove-MSG_TRUNC-logging.patch
	$(APPLY) $(SRC)/srt/0001-build-always-use-GNUInstallDirs.patch
	$(call pkg_static,"scripts/srt.pc.in")
	mv srt-$(SRT_VERSION) $@ && touch $@

SRT_CONF := -DENABLE_SHARED=OFF -DUSE_ENCLIB=gnutls -DENABLE_CXX11=OFF -DENABLE_APPS=OFF

.srt: srt toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(SRT_CONF)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
	$(APPLY) $(SRC)/srt/0001-core-ifdef-MSG_TRUNC-nixes-fix.patch
	$(call pkg_static,"scripts/srt.pc.in")
	mv srt-$(SRT_VERSION) $@ && touch $@

.srt: srt toolchain.cmake
	cd $< && $(HOSTVARS_PIC) $(CMAKE) \
		-DENABLE_SHARED=OFF -DUSE_GNUTLS=ON -DENABLE_CXX11=OFF -DCMAKE_INSTALL_LIBDIR=lib -DCMAKE_INSTALL_BINDIR=bin -DCMAKE_INSTALL_INCLUDEDIR=include
	cd $< && $(CMAKEBUILD) . --target install
>>>>>>> origin/3.0.x
	touch $@
