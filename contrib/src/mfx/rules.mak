# mfx (Media SDK)

<<<<<<< master
mfx_GITURL := $(GITHUB)/lu-zero/mfx_dispatch.git
=======
mfx_GITURL := https://github.com/lu-zero/mfx_dispatch.git
>>>>>>> origin/3.0.x
MFX_GITHASH := 7efc7505465bc1f16fbd1da3d24aa5bd9d46c5ca

ifeq ($(call need_pkg,"mfx"),)
PKGS_FOUND += mfx
endif
ifdef HAVE_WIN32
ifeq ($(filter arm aarch64, $(ARCH)),)
PKGS += mfx
endif
endif

<<<<<<< master
ifdef HAVE_WINSTORE
MFX_CONF := CFLAGS="$(CFLAGS) -DMEDIASDK_UWP_LOADER -DMEDIASDK_UWP_PROCTABLE"
MFX_CONF += CXXFLAGS="$(CXXFLAGS) -DMEDIASDK_UWP_LOADER -DMEDIASDK_UWP_PROCTABLE"
=======
MFX_CFLAGS := $(CFLAGS)
MFX_CXXFLAGS := $(CFLAGS)

ifdef HAVE_WINSTORE
MFX_CFLAGS   += -DMEDIASDK_UWP_LOADER -DMEDIASDK_UWP_PROCTABLE
MFX_CXXFLAGS += -DMEDIASDK_UWP_LOADER -DMEDIASDK_UWP_PROCTABLE
>>>>>>> origin/3.0.x
endif

$(TARBALLS)/mfx-$(MFX_GITHASH).tar.xz:
	$(call download_git,$(mfx_GITURL),,$(MFX_GITHASH))

.sum-mfx: mfx-$(MFX_GITHASH).tar.xz
	$(call check_githash,$(MFX_GITHASH))
	touch $@

mfx: mfx-$(MFX_GITHASH).tar.xz .sum-mfx
	$(UNPACK)
	$(APPLY) $(SRC)/mfx/0001-detect-winstore-builds-with-a-regular-mingw32-toolch.patch
	$(APPLY) $(SRC)/mfx/0002-Fix-linking-statically-with-intel_gfx_api-x86.dll.patch
	$(APPLY) $(SRC)/mfx/0003-Don-t-change-the-calling-convention-of-x86-gfx-api.patch
	cd $(UNPACK_DIR) && autoreconf -ivf
	$(MOVE)

.mfx: mfx
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(MFX_CONF)
	+$(MAKEBUILD)
	+$(MAKEBUILD) install
=======
	cd $< && $(HOSTVARS) CFLAGS="$(MFX_CFLAGS)" CXXFLAGS="$(MFX_CXXFLAGS)" ./configure $(HOSTCONF)
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
