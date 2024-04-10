# Mysofa

MYSOFA_VERSION := 0.5
MYSOFA_URL = $(GITHUB)/hoene/libmysofa/archive/v$(MYSOFA_VERSION).tar.gz

PKGS += mysofa

ifeq ($(call need_pkg,"libmysofa"),)
PKGS_FOUND += mysofa
endif

DEPS_mysofa += zlib $(DEPS_zlib)
ifdef HAVE_WIN32
<<<<<<< master
DEPS_mysofa += winpthreads $(DEPS_winpthreads)
=======
DEPS_mysofa += pthreads $(DEPS_pthreads)
>>>>>>> origin/3.0.x
endif

$(TARBALLS)/libmysofa-$(MYSOFA_VERSION).tar.gz:
	$(call download_pkg,$(MYSOFA_URL),mysofa)

.sum-mysofa: libmysofa-$(MYSOFA_VERSION).tar.gz

mysofa: libmysofa-$(MYSOFA_VERSION).tar.gz .sum-mysofa
	$(UNPACK)
	$(MOVE)

MYSOFA_CONF := -DBUILD_TESTS=OFF

.mysofa: mysofa toolchain.cmake
<<<<<<< master
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(MYSOFA_CONF)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
	cd $< && rm -f CMakeCache.txt
	cd $< && $(HOSTVARS) $(CMAKE) -DBUILD_TESTS=OFF
	cd $< && $(CMAKEBUILD) . --target install
>>>>>>> origin/3.0.x
	touch $@

