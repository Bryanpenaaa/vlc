# x264

<<<<<<< master
X264_HASH := e067ab0b530395f90b578f6d05ab0a225e2efdf9
X264_VERSION := $(X264_HASH)
X264_GITURL := https://code.videolan.org/videolan/x264.git
=======
X264_GITURL := git://git.videolan.org/x264.git
X264_SNAPURL := http://download.videolan.org/pub/videolan/x264/snapshots/x264-snapshot-20180324-2245.tar.bz2
X262_GITURL := git://git.videolan.org/x262.git
>>>>>>> origin/3.0.x

ifdef BUILD_ENCODERS
ifdef GPL
PKGS += x264
endif
endif

ifeq ($(call need_pkg,"x264 >= 0.148"),)
PKGS_FOUND += x264
endif

ifeq ($(call need_pkg,"x264 >= 0.153"),)
PKGS_FOUND += x26410b
endif

PKGS_ALL += x26410b

X264CONF = \
	--disable-avs \
	--disable-lavf \
	--disable-cli \
	--disable-ffms \
	--disable-opencl
ifndef HAVE_WIN32
X264CONF += --enable-pic
else
ifdef HAVE_WINSTORE
X264CONF += --enable-win32thread
else
X264CONF += --disable-win32thread
endif
<<<<<<< master
=======
ifeq ($(ARCH), arm)
X264_AS = AS="./tools/gas-preprocessor.pl -arch arm -as-type clang -force-thumb -- $(CC) -mimplicit-it=always"
endif
ifeq ($(ARCH),aarch64)
# Configure defaults to gas-preprocessor + armasm64 for this target,
# unless overridden.
X264_AS = AS="$(CC)"
endif
>>>>>>> origin/3.0.x
endif
ifdef HAVE_CROSS_COMPILE
ifndef HAVE_DARWIN_OS
X264CONF += --cross-prefix="$(HOST)-"
endif
ifdef HAVE_ANDROID
<<<<<<< master
X264CONF += --cross-prefix="$(subst ar,,$(AR))"
=======
>>>>>>> origin/3.0.x
# broken text relocations
ifeq ($(ANDROID_ABI), x86)
X264CONF += --disable-asm
endif
<<<<<<< master
=======
ifeq ($(ANDROID_ABI), x86_64)
X264CONF += --disable-asm
endif
endif
endif
ifdef HAVE_DARWIN_OS
ifeq ($(ARCH),aarch64)
X264CONF += --extra-asflags="-arch $(PLATFORM_SHORT_ARCH)"
>>>>>>> origin/3.0.x
endif
endif

$(TARBALLS)/x264-$(X264_VERSION).tar.xz:
	$(call download_git,$(X264_GITURL),,$(X264_HASH))

.sum-x26410b: .sum-x264
	touch $@

.sum-x264: x264-$(X264_VERSION).tar.xz

<<<<<<< master
x264 x26410b: %: x264-$(X264_VERSION).tar.xz .sum-%
	$(UNPACK)
=======
x264 x26410b: %: x264-git.tar.bz2 .sum-%
	rm -Rf $*-git
	mkdir -p $*-git
	tar xvjfo "$<" --strip-components=1 -C $*-git
	$(UPDATE_AUTOCONFIG)
	mv $*-git $*

x262: x262-git.tar.gz .sum-x262
	rm -Rf $@-git
	mkdir -p $@-git
	tar xvzfo "$<" --strip-components=1 -C $@-git
>>>>>>> origin/3.0.x
	$(UPDATE_AUTOCONFIG)
	$(APPLY) $(SRC)/x264/x264-winstore.patch
	$(MOVE)

.x264: x264
	$(REQUIRE_GPL)
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(X264CONF)
	+$(MAKEBUILD)
	+$(MAKEBUILD) install
	touch $@

.x26410b: .x264
=======
	cd $< && $(HOSTVARS) $(X264_AS) ./configure $(X264CONF)
	cd $< && $(MAKE) install
	touch $@

.x26410b: .x264
	touch $@

.x262: x262
	$(REQUIRE_GPL)
	cd $< && sed -i -e 's/x264/x262/g' configure
	cd $< && sed -i -e 's/x264_config/x262_config/g' *.h Makefile *.c
	cd $< && $(HOSTVARS) ./configure $(X264CONF)
	cd $< && sed -i -e 's/x264.pc/x262.pc/g' Makefile
	cd $< && sed -i -e 's/x264.h/x262.h/g' Makefile
	cd $< && $(MAKE)
	cd $< && cp x264.h x262.h
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
