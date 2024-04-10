# Qt

<<<<<<< master
QT_VERSION_MAJOR := 5.15
QT_VERSION := $(QT_VERSION_MAJOR).8
# Insert potential -betaX suffix here:
QT_VERSION_FULL := $(QT_VERSION)
QT_URL := $(QT)/$(QT_VERSION_MAJOR)/$(QT_VERSION_FULL)/submodules/qtbase-everywhere-opensource-src-$(QT_VERSION_FULL).tar.xz
=======
QT_VERSION := 5.6.3
QT_URL := https://download.qt.io/archive/qt/5.6/$(QT_VERSION)/submodules/qtbase-opensource-src-$(QT_VERSION).tar.xz
>>>>>>> origin/3.0.x

ifdef HAVE_MACOSX
#PKGS += qt
endif
ifdef HAVE_WIN32
PKGS += qt
DEPS_qt = fxc2 $(DEPS_fxc2) d3d9 $(DEPS_d3d9)
ifneq ($(call mingw_at_least, 8), true)
DEPS_qt += dcomp $(DEPS_dcomp)
endif # MINGW 8
ifdef HAVE_CROSS_COMPILE
DEPS_qt += wine-headers
endif
endif

DEPS_qt += freetype2 $(DEPS_freetype2) harfbuzz $(DEPS_harfbuzz) jpeg $(DEPS_jpeg) png $(DEPS_png) zlib $(DEPS_zlib)

ifeq ($(call need_pkg,"Qt5Core >= 5.11 Qt5Gui Qt5Widgets"),)
PKGS_FOUND += qt
endif

<<<<<<< master
$(TARBALLS)/qtbase-everywhere-src-$(QT_VERSION_FULL).tar.xz:
=======
$(TARBALLS)/qt-$(QT_VERSION).tar.xz:
>>>>>>> origin/3.0.x
	$(call download_pkg,$(QT_URL),qt)

.sum-qt: qtbase-everywhere-src-$(QT_VERSION_FULL).tar.xz

qt: qtbase-everywhere-src-$(QT_VERSION_FULL).tar.xz .sum-qt
	$(UNPACK)
<<<<<<< master
	$(APPLY) $(SRC)/qt/0002-Windows-QPA-Disable-systray-notification-sounds.patch
	$(APPLY) $(SRC)/qt/0001-disable-qt_random_cpu.patch
	$(APPLY) $(SRC)/qt/0007-ANGLE-remove-static-assert-that-can-t-be-evaluated-b.patch
	$(APPLY) $(SRC)/qt/0008-ANGLE-disable-ANGLE_STD_ASYNC_WORKERS-when-compiling.patch
	$(APPLY) $(SRC)/qt/0009-Add-KHRONOS_STATIC-to-allow-static-linking-on-Windows.patch
	$(APPLY) $(SRC)/qt/0003-allow-cross-compilation-of-angle-with-wine.patch
	$(APPLY) $(SRC)/qt/qt-fix-gcc11-build.patch
	# force path replacement in pkg-config output files
	$(APPLY) $(SRC)/qt/force-pkgconfg-replace.patch
	# pass all files installed through our installer
	$(APPLY) $(SRC)/qt/set-mkspecs-properties.patch
	# fix missing QMAKE_PKGCONFIG_VERSION in Windows targets
	$(APPLY) $(SRC)/qt/set-mkspecs-version.patch
	# don't omit -I${includedir} from .pc files when forcing -I$CONTRIB/include
	$(APPLY) $(SRC)/qt/add-includedir-to-pc-file.patch
	# fix detection of our harfbuzz on macosx
	sed -i.orig 's#"-lharfbuzz"#{ "libs": "-framework CoreText -framework CoreGraphics -framework CoreFoundation -lharfbuzz", "condition": "config.darwin" }, "-lharfbuzz"#' "$(UNPACK_DIR)/src/gui/configure.json"
	# Let us decide the WINVER/_WIN32_WINNT
	sed -i.orig 's,mingw: DEFINES += WINVER=0x0601,# mingw: DEFINES += WINVER=0x0601,' "$(UNPACK_DIR)/mkspecs/features/qt_build_config.prf"
	# Prevent all Qt contribs from generating and installing libtool .la files
	sed -i.orig "/CONFIG/ s/ create_libtool/ -create_libtool/g" $(UNPACK_DIR)/mkspecs/features/qt_module.prf
=======
	mv qtbase-opensource-src-$(QT_VERSION) qt-$(QT_VERSION)
	$(APPLY) $(SRC)/qt/0001-Windows-QPA-Reimplement-calculation-of-window-frames_56.patch
	$(APPLY) $(SRC)/qt/0002-Windows-QPA-Use-new-EnableNonClientDpiScaling-for-Wi_56.patch
	$(APPLY) $(SRC)/qt/0003-QPA-prefer-lower-value-when-rounding-fractional-scaling.patch
	$(APPLY) $(SRC)/qt/0004-qmake-don-t-limit-command-line-length-when-not-actua.patch
	$(APPLY) $(SRC)/qt/0005-harfbuzz-Fix-building-for-win64-with-clang.patch
	$(APPLY) $(SRC)/qt/0006-moc-Initialize-staticMetaObject-with-the-highest-use.patch
	$(APPLY) $(SRC)/qt/0007-Only-define-QT_FASTCALL-on-x86_32.patch
	$(APPLY) $(SRC)/qt/0008-Skip-arm-pixman-drawhelpers-on-windows-just-like-on-.patch
	$(APPLY) $(SRC)/qt/0009-mkspecs-Add-a-win32-clang-g-mkspec-for-clang-targeti.patch
	$(APPLY) $(SRC)/qt/0010-Add-the-QT_HAS_xxx-macros-for-post-C-11-feature-test.patch
	$(APPLY) $(SRC)/qt/0011-qCount-Leading-Trailing-ZeroBits-Use-__builtin_clzs-.patch
	$(APPLY) $(SRC)/qt/0012-Remove-_bit_scan_-forward-reverse.patch
	$(APPLY) $(SRC)/qt/0013-qsimd-Fix-compilation-with-trunk-clang-for-mingw.patch
	$(APPLY) $(SRC)/qt/0014-QtTest-compile-in-C-17-mode-no-more-std-unary_functi.patch
	$(APPLY) $(SRC)/qt/0015-foreach-remove-implementations-not-using-decltype.patch
	$(APPLY) $(SRC)/qt/0016-Replace-custom-type-traits-with-std-one-s.patch
	$(APPLY) $(SRC)/qt/0017-Rename-QtPrivate-is_-un-signed-to-QtPrivate-Is-Un-si.patch
	$(APPLY) $(SRC)/qt/0018-Remove-qtypetraits.h-s-contents-altogether.patch
	$(APPLY) $(SRC)/qt/systray-no-sound.patch
>>>>>>> origin/3.0.x
	$(MOVE)


ifdef HAVE_WIN32
QT_OPENGL := -angle
else
QT_OPENGL := -opengl desktop
endif

ifdef HAVE_MACOSX
QT_SPEC := macx-clang
endif

ifdef HAVE_LINUX
ifdef HAVE_CLANG
QT_SPEC := linux-clang
else
QT_SPEC := linux-g++
endif
endif

ifdef HAVE_WIN32
<<<<<<< master

=======
# filter out the contrib includes as Qt doesn't ike pthread-GC2 headers
QT_VARS := CFLAGS="$(shell echo $$CFLAGS | sed 's@ -I$$(PREFIX)/include@@g')" \
         CXXFLAGS="$(shell echo $$CXXFLAGS | sed 's@ -I$$(PREFIX)/include@@g')"
>>>>>>> origin/3.0.x
ifdef HAVE_CLANG
QT_SPEC := win32-clang-g++
else
QT_SPEC := win32-g++
<<<<<<< master
=======
endif
QT_PLATFORM := -xplatform $(QT_SPEC) -device-option CROSS_COMPILE=$(HOST)-
>>>>>>> origin/3.0.x
endif

endif

<<<<<<< master
ifdef HAVE_CROSS_COMPILE
QT_PLATFORM := -xplatform $(QT_SPEC) -device-option CROSS_COMPILE=$(HOST)-
else
ifneq ($(QT_SPEC),)
QT_PLATFORM := -platform $(QT_SPEC)
endif
endif

QT_CONFIG := -static -opensource -confirm-license $(QT_OPENGL) -no-pkg-config \
	-no-sql-sqlite -no-gif -no-openssl -no-dbus -no-vulkan -no-sql-odbc -no-pch \
	-no-feature-concurrent -no-feature-itemmodeltester -no-feature-printer \
	-no-feature-sqlmodel -no-feature-sql -no-feature-testlib -no-feature-xml \
	-no-compile-examples -nomake examples -nomake tests \
	-system-freetype -system-harfbuzz -system-libjpeg -system-libpng -system-zlib \
	-no-syncqt

# For now, we only build Qt in release mode. In debug mode, startup is prevented by the internal ANGLE
# throwing an assertion in debug mode, but only when built with clang. See issue 27476.
QT_CONFIG += -release

ifeq ($(V),1)
QT_CONFIG += -verbose
endif

ifdef HAVE_MINGW_W64
QT_CONFIG += -no-direct2d
=======
QT_CONFIG += -release

.qt: qt
	cd $< && $(QT_VARS) ./configure $(QT_PLATFORM) $(QT_CONFIG) -prefix $(PREFIX)
	# Make && Install libraries
	cd $< && $(MAKE)
	cd $< && $(MAKE) -C src sub-corelib-install_subtargets sub-gui-install_subtargets sub-widgets-install_subtargets sub-platformsupport-install_subtargets sub-zlib-install_subtargets sub-bootstrap-install_subtargets
	# Install tools
	cd $< && $(MAKE) -C src sub-moc-install_subtargets sub-rcc-install_subtargets sub-uic-install_subtargets
	# Install plugins
	cd $< && $(MAKE) -C src/plugins sub-platforms-install_subtargets
	mv $(PREFIX)/plugins/platforms/libqwindows.a $(PREFIX)/lib/ && rm -rf $(PREFIX)/plugins
	# Move includes to match what VLC expects
	mkdir -p $(PREFIX)/include/QtGui/qpa
	cp $(PREFIX)/include/QtGui/$(QT_VERSION)/QtGui/qpa/qplatformnativeinterface.h $(PREFIX)/include/QtGui/qpa
	# Clean Qt mess
	rm -rf $(PREFIX)/lib/libQt5Bootstrap* $</lib/libQt5Bootstrap*
	# Fix .pc files to remove debug version (d)
	cd $(PREFIX)/lib/pkgconfig; for i in Qt5Core.pc Qt5Gui.pc Qt5Widgets.pc; do sed -i -e 's/d\.a/.a/g' -e 's/d $$/ /' $$i; done
	# Fix Qt5Gui.pc file to include qwindows (QWindowsIntegrationPlugin) and Qt5Platform Support
	cd $(PREFIX)/lib/pkgconfig; sed -i -e 's/ -lQt5Gui/ -lqwindows -lQt5PlatformSupport -lQt5Gui/g' Qt5Gui.pc
ifdef HAVE_CROSS_COMPILE
	# Building Qt build tools for Xcompilation
	cd $</include/QtCore; $(LN_S)f $(QT_VERSION)/QtCore/private private
	cd $<; $(MAKE) -C qmake
	cd $<; $(MAKE) install_qmake install_mkspecs
	cd $</src/tools; \
	for i in bootstrap uic rcc moc; \
		do (cd $$i; echo $$i && ../../../bin/qmake -spec $(QT_SPEC) && $(MAKE) clean && $(MAKE) CC=$(HOST)-gcc CXX=$(HOST)-g++ LINKER=$(HOST)-g++ LIB="$(HOST)-ar -rc" && $(MAKE) install); \
	done
>>>>>>> origin/3.0.x
endif

QT_ENV_VARS := $(HOSTVARS) DXSDK_DIR=$(PREFIX)/bin
QT_QINSTALL="$(shell cd $(SRC)/qt/; pwd -P)/install_wrapper.sh"

qmake_toolchain = echo "!host_build {"    > $(1)/.qmake.cache && \
	echo "  QMAKE_C        = $(CC)"      >> $(1)/.qmake.cache && \
	echo "  QMAKE_CXX      = $(CXX)"     >> $(1)/.qmake.cache && \
	echo "  QMAKE_STRIP    = $(STRIP)"  >> $(1)/.qmake.cache && \
	echo "  QMAKE_CFLAGS   += -isystem $(PREFIX)/include $(CFLAGS)" >> $(1)/.qmake.cache && \
	echo "  QMAKE_CXXFLAGS += -isystem $(PREFIX)/include $(CXXFLAGS)" >> $(1)/.qmake.cache && \
	echo "  QMAKE_LFLAGS   += $(LDFLAGS)"  >> $(1)/.qmake.cache && \
	echo "  QMAKE_INSTALL_FILE = VLC_PREFIX=$(PREFIX) $(QT_QINSTALL)"  >> $(1)/.qmake.cache && \
	echo "} else {"                        >> $(1)/.qmake.cache && \
	echo "  QMAKE_C        = $(BUILDCC)"   >> $(1)/.qmake.cache && \
	echo "  QMAKE_CXX      = $(BUILDCXX)"  >> $(1)/.qmake.cache && \
	echo "  QMAKE_STRIP    = $(BUILDSTRIP)"  >> $(1)/.qmake.cache && \
	echo "  QMAKE_CFLAGS   += $(BUILDCFLAGS)"   >> $(1)/.qmake.cache && \
	echo "  QMAKE_CXXFLAGS += $(BUILDCXXFLAGS)" >> $(1)/.qmake.cache && \
	echo "  QMAKE_LFLAGS   += $(BUILDLDFLAGS)"  >> $(1)/.qmake.cache && \
	echo "}"                                           >> $(1)/.qmake.cache && \
	echo "CONFIG -= debug_and_release" >> $(1)/.qmake.cache && \
	echo "CONFIG += object_parallel_to_source create_pc force_bootstrap" >> $(1)/.qmake.cache


.qt: qt
	$(call qmake_toolchain, $<)
	# Configure qt, build and run qmake
	+cd $< && $(QT_ENV_VARS) ./configure $(QT_PLATFORM) $(QT_CONFIG) -prefix $(PREFIX) -hostprefix $(PREFIX)/lib/qt5 \
	    $(shell $(SRC)/qt/configure-env.py $(CPPFLAGS) $(LDFLAGS))
	# Build libraries, widgets, plugins, doc (empty)
	$(MAKE) -C $<
	# Install libraries, widgets, plugins, tools, doc (empty)
	$(MAKE) -C $< install

	#fix host tools headers to avoid collision with target headers
	mkdir -p $(PREFIX)/lib/qt5/include
	cp -R $(PREFIX)/include/QtCore $(PREFIX)/lib/qt5/include
	sed -i.orig -e "s#\$\$QT_MODULE_INCLUDE_BASE#$(PREFIX)/lib/qt5/include#g" $(PREFIX)/lib/qt5/mkspecs/modules/qt_lib_bootstrap_private.pri
	touch $@
