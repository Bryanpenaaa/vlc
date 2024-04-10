# Qt

<<<<<<< master
QTSVG_VERSION_MAJOR := 5.15
QTSVG_VERSION := $(QTSVG_VERSION_MAJOR).8
QTSVG_URL := $(QT)/$(QTSVG_VERSION_MAJOR)/$(QTSVG_VERSION)/submodules/qtsvg-everywhere-opensource-src-$(QTSVG_VERSION).tar.xz
=======
QTSVG_VERSION := 5.6.3
QTSVG_URL := https://download.qt.io/archive/qt/5.6/$(QTSVG_VERSION)/submodules/qtsvg-opensource-src-$(QTSVG_VERSION).tar.xz
>>>>>>> origin/3.0.x

DEPS_qtsvg += qt $(DEPS_qt)

ifdef HAVE_WIN32
PKGS += qtsvg
endif

ifeq ($(call need_pkg,"Qt5Svg"),)
PKGS_FOUND += qtsvg
endif

<<<<<<< master
$(TARBALLS)/qtsvg-everywhere-src-$(QTSVG_VERSION).tar.xz:
=======
$(TARBALLS)/qtsvg-$(QTSVG_VERSION).tar.xz:
>>>>>>> origin/3.0.x
	$(call download_pkg,$(QTSVG_URL),qt)

.sum-qtsvg: qtsvg-everywhere-src-$(QTSVG_VERSION).tar.xz

qtsvg: qtsvg-everywhere-src-$(QTSVG_VERSION).tar.xz .sum-qtsvg
	$(UNPACK)
	$(MOVE)

.qtsvg: qtsvg
	$(call qmake_toolchain, $<)
	cd $< && $(PREFIX)/lib/qt5/bin/qmake
	# Make && Install libraries
<<<<<<< master
	$(MAKE) -C $<
	$(MAKE) -C $< install
=======
	cd $< && $(MAKE)
	cd $< && $(MAKE) -C src sub-plugins-install_subtargets sub-svg-install_subtargets
	mv $(PREFIX)/plugins/iconengines/libqsvgicon.a $(PREFIX)/lib/
	mv $(PREFIX)/plugins/imageformats/libqsvg.a $(PREFIX)/lib/
	cd $(PREFIX)/lib/pkgconfig; sed -i \
		-e 's/d\.a/.a/g' \
		-e 's/-lQt\([^ ]*\)d/-lQt\1/g' \
		-e '/Libs:/  s/-lQt5Svg/-lqsvg -lqsvgicon -lQt5Svg/ ' \
		Qt5Svg.pc
>>>>>>> origin/3.0.x
	touch $@
