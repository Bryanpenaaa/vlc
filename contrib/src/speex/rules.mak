# speex

SPEEX_VERSION := 1.2.1
<<<<<<< master
SPEEX_URL := $(XIPH)/speex/speex-$(SPEEX_VERSION).tar.gz
=======
SPEEX_URL := http://downloads.us.xiph.org/releases/speex/speex-$(SPEEX_VERSION).tar.gz
>>>>>>> origin/3.0.x

PKGS += speex
ifeq ($(call need_pkg,"speex >= 1.0.5"),)
PKGS_FOUND += speex
endif

$(TARBALLS)/speex-$(SPEEX_VERSION).tar.gz:
	$(call download_pkg,$(SPEEX_URL),speex)

.sum-speex: speex-$(SPEEX_VERSION).tar.gz

speex: speex-$(SPEEX_VERSION).tar.gz .sum-speex
	$(UNPACK)
	$(call pkg_static,"speex.pc.in")
	$(MOVE)

SPEEX_CONF := --disable-binaries
ifndef HAVE_FPU
SPEEX_CONF += --enable-fixed-point
ifeq ($(ARCH),arm)
SPEEX_CONF += --enable-arm5e-asm
endif
endif
ifeq ($(ARCH),aarch64)
SPEEX_CONF += --disable-neon
endif

.speex: speex
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(SPEEX_CONF)
	+$(MAKEBUILD)
	+$(MAKEBUILD) install
=======
	cd $< && $(HOSTVARS) ./configure $(HOSTCONF) $(SPEEX_CONF)
	cd $< && $(MAKE)
	$(call pkg_static,"speex.pc")
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
