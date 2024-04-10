# FLAC

<<<<<<< master
FLAC_VERSION := 1.4.2
FLAC_URL := $(GITHUB)/xiph/flac/releases/download/$(FLAC_VERSION)/flac-$(FLAC_VERSION).tar.xz
=======
FLAC_VERSION := 1.3.4
FLAC_URL := http://downloads.xiph.org/releases/flac/flac-$(FLAC_VERSION).tar.xz
>>>>>>> origin/3.0.x

PKGS += flac
ifeq ($(call need_pkg,"flac"),)
PKGS_FOUND += flac
endif

$(TARBALLS)/flac-$(FLAC_VERSION).tar.xz:
	$(call download_pkg,$(FLAC_URL),flac)

.sum-flac: flac-$(FLAC_VERSION).tar.xz

flac: flac-$(FLAC_VERSION).tar.xz .sum-flac
	$(UNPACK)
<<<<<<< master
	# disable building a tool we don't use
	sed -e 's,add_subdirectory("microbench"),#add_subdirectory("microbench"),' -i.orig $(UNPACK_DIR)/CMakeLists.txt
=======
ifdef HAVE_WINSTORE
	$(APPLY) $(SRC)/flac/console_write.patch
	$(APPLY) $(SRC)/flac/remove_blocking_code_useless_flaclib.patch
	$(APPLY) $(SRC)/flac/no-createfilea.patch
endif
ifdef HAVE_DARWIN_OS
	cd $(UNPACK_DIR) && sed -e 's,-dynamiclib,-dynamiclib -arch $(ARCH),' -i.orig configure
endif
ifdef HAVE_ANDROID
ifeq ($(ANDROID_ABI), x86)
	# cpu.c:130:29: error: sys/ucontext.h: No such file or directory
	# defining USE_OBSOLETE_SIGCONTEXT_FLAVOR allows us to bypass that
	cd $(UNPACK_DIR) && sed -i.orig -e s/"#  undef USE_OBSOLETE_SIGCONTEXT_FLAVOR"/"#define USE_OBSOLETE_SIGCONTEXT_FLAVOR"/g src/libFLAC/cpu.c
endif
endif
	$(APPLY) $(SRC)/flac/dont-force-msvcrt-version.patch
>>>>>>> origin/3.0.x
	$(call pkg_static,"src/libFLAC/flac.pc.in")
	$(MOVE)

FLAC_CONF = \
	-DINSTALL_MANPAGES=OFF \
	-DBUILD_CXXLIBS=OFF \
	-DBUILD_EXAMPLES=OFF \
	-DBUILD_PROGRAMS=OFF \
	-DBUILD_DOCS=OFF

ifeq ($(ARCH),i386)
# nasm doesn't like the -fstack-protector-strong that's added to its flags
# let's prioritize the use of nasm over stack protection
FLAC_CONF += -DWITH_STACK_PROTECTOR=OFF
endif

DEPS_flac = ogg $(DEPS_ogg)

<<<<<<< master
.flac: flac toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(FLAC_CONF)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
.flac: flac
	cd $< && $(AUTORECONF)
	cd $< && $(HOSTVARS) CFLAGS="$(FLAC_CFLAGS)" ./configure $(FLACCONF)
	cd $< && $(MAKE) -C include install
	cd $< && $(MAKE) -C src/libFLAC install && $(MAKE) -C src/share install
>>>>>>> origin/3.0.x
	touch $@
