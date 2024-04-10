# libxml2

LIBXML2_VERSION := 2.9.14
LIBXML2_URL := https://download.gnome.org/sources/libxml2/2.9/libxml2-$(LIBXML2_VERSION).tar.xz

PKGS += libxml2
ifeq ($(call need_pkg,"libxml-2.0"),)
PKGS_FOUND += libxml2
endif

$(TARBALLS)/libxml2-$(LIBXML2_VERSION).tar.xz:
	$(call download_pkg,$(LIBXML2_URL),libxml2)

.sum-libxml2: libxml2-$(LIBXML2_VERSION).tar.xz

<<<<<<< master
LIBXML2_CONF = \
        -DLIBXML2_WITH_C14N=OFF \
        -DLIBXML2_WITH_ISO8859X=OFF \
        -DLIBXML2_WITH_SCHEMAS=OFF \
        -DLIBXML2_WITH_SCHEMATRON=OFF \
        -DLIBXML2_WITH_VALID=OFF \
        -DLIBXML2_WITH_WRITER=OFF \
        -DLIBXML2_WITH_XINCLUDE=OFF \
        -DLIBXML2_WITH_XPATH=OFF \
        -DLIBXML2_WITH_XPTR=OFF \
        -DLIBXML2_WITH_MODULES=OFF \
        -DLIBXML2_WITH_LEGACY=OFF \
        -DLIBXML2_WITH_ZLIB=OFF    \
        -DLIBXML2_WITH_ICONV=OFF   \
        -DLIBXML2_WITH_HTTP=OFF    \
        -DLIBXML2_WITH_FTP=OFF     \
        -DLIBXML2_WITH_DOCB=OFF    \
        -DLIBXML2_WITH_REGEXPS=OFF \
        -DLIBXML2_WITH_PYTHON=OFF \
        -DLIBXML2_WITH_LZMA=OFF \
        -DLIBXML2_WITH_TESTS=OFF \
        -DLIBXML2_WITH_PROGRAMS=OFF
=======
XMLCONF = --with-minimal     \
          --with-catalog     \
          --with-reader      \
          --with-tree        \
          --with-push        \
          --with-xptr        \
          --with-valid       \
          --with-xpath       \
          --with-xinclude    \
          --with-sax1        \
          --without-zlib     \
          --without-iconv    \
          --without-http     \
          --without-ftp      \
          --without-docbook  \
          --without-regexps  \
          --without-python
>>>>>>> origin/3.0.x

ifdef WITH_OPTIMIZATION
LIBXML2_CONF += -DLIBXML2_WITH_DEBUG=OFF
endif

<<<<<<< master
XMLCONF += CFLAGS="$(CFLAGS) -DLIBXML_STATIC"

libxml2: libxml2-$(LIBXML2_VERSION).tar.xz .sum-libxml2
	$(UNPACK)
	# fix pkg-config file using an unset variable
	sed -e 's,"\\\$${pcfiledir}/$${PACKAGE_RELATIVE_PATH}","$${CMAKE_INSTALL_PREFIX}",' -i.orig  "$(UNPACK_DIR)/CMakeLists.txt"
=======
libxml2: libxml2-$(LIBXML2_VERSION).tar.xz .sum-libxml2
	$(UNPACK)
	$(APPLY) $(SRC)/libxml2/win32.patch
	$(APPLY) $(SRC)/libxml2/bins.patch
	$(APPLY) $(SRC)/libxml2/pthread.patch
>>>>>>> origin/3.0.x
ifdef HAVE_WINSTORE
	$(APPLY) $(SRC)/libxml2/nogetcwd.patch
endif
	$(call pkg_static,"libxml-2.0.pc.in")
	$(MOVE)

<<<<<<< master
.libxml2: libxml2 toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(LIBXML2_CONF)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
.libxml2: libxml2
	$(RECONF)
	cd $< && $(HOSTVARS) ./configure $(HOSTCONF) CFLAGS="$(CFLAGS) -DLIBXML_STATIC" $(XMLCONF)
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
