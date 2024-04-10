# ncurses

NCURSES_VERSION := 6.3
NCURSES_URL := $(GNU)/ncurses/ncurses-$(NCURSES_VERSION).tar.gz

ifdef HAVE_MACOSX
PKGS += ncurses
endif

ifeq ($(call need_pkg,"ncursesw"),)
PKGS_FOUND += ncurses
endif

$(TARBALLS)/ncurses-$(NCURSES_VERSION).tar.gz:
	$(call download_pkg,$(NCURSES_URL),ncurses)

.sum-ncurses: ncurses-$(NCURSES_VERSION).tar.gz

ncurses: ncurses-$(NCURSES_VERSION).tar.gz .sum-ncurses
	$(UNPACK)
	$(APPLY) $(SRC)/ncurses/ncurses-win32.patch
	$(MOVE)

NCURSES_CONF := --enable-widec --with-terminfo-dirs=/usr/share/terminfo \
    --with-pkg-config=yes --enable-pc-files --without-manpages --without-tests \
    --without-ada --without-progs
ifdef WITH_OPTIMIZATION
NCURSES_CONF+= --without-debug
endif
ifdef HAVE_WIN32
NCURSES_CONF+= --disable-sigwinch
endif

.ncurses: ncurses
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(NCURSES_CONF)
	+$(MAKEBUILD) -C ncurses -j1
	+$(MAKEBUILD) -C ncurses install
	+$(MAKEBUILD) -C include -j1
	+$(MAKEBUILD) -C include install
	+$(MAKEBUILD) -C misc pc-files
	install $(BUILD_DIR)/misc/ncursesw.pc "$(PREFIX)/lib/pkgconfig"
=======
	cd $< && mkdir -p "$(PREFIX)/lib/pkgconfig" && $(HOSTVARS) PKG_CONFIG_LIBDIR="$(PREFIX)/lib/pkgconfig" ./configure $(patsubst --datarootdir=%,,$(HOSTCONF)) --without-debug --enable-widec --without-develop --without-shared --with-terminfo-dirs=/usr/share/terminfo --with-pkg-config=yes --enable-pc-files
	cd $< && make -C ncurses -j1 && make -C ncurses install
	cd $< && make -C include -j1 && make -C include install
	cd $< && make -C misc pc-files && cp misc/ncursesw.pc "$(PREFIX)/lib/pkgconfig"
>>>>>>> origin/3.0.x
	touch $@
