# CACA
CACA_VERSION := 0.99.beta20
<<<<<<< master
CACA_URL := $(GITHUB)/cacalabs/libcaca/releases/download/v$(CACA_VERSION)/libcaca-$(CACA_VERSION).tar.gz
=======
CACA_URL := https://github.com/cacalabs/libcaca/releases/download/v$(CACA_VERSION)/libcaca-$(CACA_VERSION).tar.gz
>>>>>>> origin/3.0.x

ifndef HAVE_DARWIN_OS
ifndef HAVE_LINUX # see VLC Trac 17251
ifndef HAVE_WINSTORE
PKGS += caca
endif
endif
<<<<<<< master
endif
=======
>>>>>>> origin/3.0.x

ifeq ($(call need_pkg,"caca >= 0.99.beta19"),)
PKGS_FOUND += caca
endif

$(TARBALLS)/libcaca-$(CACA_VERSION).tar.gz:
	$(call download_pkg,$(CACA_URL),caca)

.sum-caca: libcaca-$(CACA_VERSION).tar.gz

caca: libcaca-$(CACA_VERSION).tar.gz .sum-caca
	$(UNPACK)
	$(APPLY) $(SRC)/caca/caca-fix-compilation-llvmgcc.patch
	$(APPLY) $(SRC)/caca/caca-fix-pkgconfig.patch
	$(call pkg_static,"caca/caca.pc.in")
	$(UPDATE_AUTOCONFIG)
	$(MOVE)
	mv caca/config.sub caca/config.guess caca/.auto

CACA_CONF := \
	--disable-gl \
	--disable-imlib2 \
	--disable-doc \
	--disable-cppunit \
	--disable-zzuf \
	--disable-ruby \
	--disable-csharp \
	--disable-cxx \
	--disable-java \
	--disable-python \
	--disable-cocoa \
	--disable-network \
	--disable-vga \
	--disable-imlib2
ifdef HAVE_MACOSX
CACA_CONF += --disable-x11
endif
<<<<<<< master
ifndef WITH_OPTIMIZATION
CACA_CONF += --enable-debug
endif
=======
>>>>>>> origin/3.0.x
ifdef HAVE_WIN32
CACA_CONF += --disable-ncurses \
    ac_cv_func_vsnprintf_s=yes \
    ac_cv_func_sprintf_s=yes
endif
ifdef HAVE_LINUX
CACA_CONF += --disable-ncurses
endif

CACA_CONF += \
	MACOSX_SDK=$(MACOSX_SDK) \
	MACOSX_SDK_CFLAGS=" " \
	MACOSX_SDK_CXXFLAGS=" " \
	CPPFLAGS="$(CPPFLAGS) -DCACA_STATIC"

.caca: caca
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(CACA_CONF)
	+$(MAKEBUILD) -C $<
	+$(MAKEBUILD) -C $< install
	touch $@
