# ZLIB
ZLIB_VERSION := 1.2.13
ZLIB_URL := $(GITHUB)/madler/zlib/releases/download/v$(ZLIB_VERSION)/zlib-$(ZLIB_VERSION).tar.xz

PKGS += zlib
ifeq ($(call need_pkg,"zlib"),)
PKGS_FOUND += zlib
endif

<<<<<<< master
=======
ifeq ($(shell uname),Darwin) # zlib tries to use libtool on Darwin
ifdef HAVE_CROSS_COMPILE
ZLIB_CONFIG_VARS=CHOST=$(HOST)
endif
endif

>>>>>>> origin/3.0.x
$(TARBALLS)/zlib-$(ZLIB_VERSION).tar.xz:
	$(call download_pkg,$(ZLIB_URL),zlib)

.sum-zlib: zlib-$(ZLIB_VERSION).tar.xz

zlib: zlib-$(ZLIB_VERSION).tar.xz .sum-zlib
	$(UNPACK)
	$(APPLY) $(SRC)/zlib/0001-Fix-mingw-static-library-name-on-mingw-and-Emscripte.patch
	$(APPLY) $(SRC)/zlib/0002-Add-an-option-to-enable-disable-building-examples.patch
	# disable the installation of the dynamic library since there's no option
	sed -e 's,install(TARGETS zlib zlibstatic,install(TARGETS zlibstatic,' -i.orig $(UNPACK_DIR)/CMakeLists.txt
	# only use the proper libz name for the static library
	sed -e 's,set_target_properties(zlib zlibstatic ,set_target_properties(zlibstatic ,' -i.orig $(UNPACK_DIR)/CMakeLists.txt
	$(MOVE)

<<<<<<< master
ZLIB_CONF = -DINSTALL_PKGCONFIG_DIR:STRING=$(PREFIX)/lib/pkgconfig -DBUILD_EXAMPLES=OFF

.zlib: zlib toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(ZLIB_CONF)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
.zlib: zlib
ifdef HAVE_WIN32
	cd $< && $(HOSTVARS) $(MAKE) -fwin32/Makefile.gcc install $(HOSTVARS) $(ZLIB_CONFIG_VARS) LD="$(CC)" prefix="$(PREFIX)" INCLUDE_PATH="$(PREFIX)/include" LIBRARY_PATH="$(PREFIX)/lib" BINARY_PATH="$(PREFIX)/bin"
else
	cd $< && $(HOSTVARS_PIC) $(ZLIB_CONFIG_VARS) ./configure --prefix=$(PREFIX) --static
	cd $< && $(MAKE) install
endif
>>>>>>> origin/3.0.x
	touch $@
