# UPNP
<<<<<<< master
UPNP_VERSION := 1.14.15
=======
UPNP_VERSION := 1.14.13
>>>>>>> origin/3.0.x
UPNP_URL := $(GITHUB)/pupnp/pupnp/archive/refs/tags/release-$(UPNP_VERSION).tar.gz

ifdef BUILD_NETWORK
PKGS += upnp
endif
<<<<<<< master
ifeq ($(call need_pkg,"libupnp >= 1.8.3"),)
=======
ifeq ($(call need_pkg,"libupnp >= 1.6.19"),)
>>>>>>> origin/3.0.x
PKGS_FOUND += upnp
endif

$(TARBALLS)/pupnp-release-$(UPNP_VERSION).tar.gz:
	$(call download_pkg,$(UPNP_URL),upnp)

.sum-upnp: pupnp-release-$(UPNP_VERSION).tar.gz
<<<<<<< master

ifdef HAVE_WIN32
DEPS_upnp += winpthreads $(DEPS_winpthreads)
=======

UPNP_CFLAGS := $(CFLAGS) -DUPNP_STATIC_LIB
UPNP_CXXFLAGS := $(CXXFLAGS) -DUPNP_STATIC_LIB
UPNP_CONF := --disable-samples --disable-device --disable-webserver

ifdef HAVE_WIN32
DEPS_upnp += pthreads $(DEPS_pthreads)
>>>>>>> origin/3.0.x
endif

UPNP_CONF := -DUPNP_BUILD_SHARED=OFF \
	-DBUILD_TESTING=OFF \
	-DUPNP_BUILD_SAMPLES=OFF

ifdef HAVE_WINSTORE
<<<<<<< master
UPNP_CONF += -DUPNP_ENABLE_IPV6=OFF -DUPNP_ENABLE_UNSPECIFIED_SERVER=ON
else
ifdef HAVE_IOS
UPNP_CONF += -DUPNP_ENABLE_IPV6=OFF -DUPNP_ENABLE_UNSPECIFIED_SERVER=ON
else
UPNP_CONF += -DUPNP_ENABLE_IPV6=ON
endif
=======
UPNP_CONF += --disable-ipv6 --enable-unspecified_server
else
UPNP_CONF += --enable-ipv6
endif
ifndef WITH_OPTIMIZATION
UPNP_CONF += --enable-debug
>>>>>>> origin/3.0.x
endif

upnp: pupnp-release-$(UPNP_VERSION).tar.gz .sum-upnp
	$(UNPACK)
ifdef HAVE_WIN32
<<<<<<< master
	$(APPLY) $(SRC)/upnp/libupnp-win32.patch
	$(APPLY) $(SRC)/upnp/windows-version-inet.patch
endif
ifdef HAVE_ANDROID
	$(APPLY) $(SRC)/upnp/revert-ifaddrs.patch
else
	# Avoid forcing `-lpthread` on android as it does not provide it and
	# identifies as 'Linux' in CMake.
	$(APPLY) $(SRC)/upnp/libtool-nostdlib-workaround.patch
endif
	$(APPLY) $(SRC)/upnp/miniserver.patch
	$(MOVE)

.upnp: upnp toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(UPNP_CONF)
	+$(CMAKEBUILD)
	+$(CMAKEINSTALL)
=======
	$(APPLY) $(SRC)/upnp/libupnp-pthread-force.patch
	$(APPLY) $(SRC)/upnp/libupnp-win32-exports.patch
	$(APPLY) $(SRC)/upnp/libupnp-win32.patch
	$(APPLY) $(SRC)/upnp/windows-version-inet.patch
	$(APPLY) $(SRC)/upnp/0001-ThreadPool-Fix-non-UCRT-builds.patch
	$(APPLY) $(SRC)/upnp/win32-remove-wrong-safe-wrappers.patch
endif
ifdef HAVE_LINUX
ifndef HAVE_ANDROID
	$(APPLY) $(SRC)/upnp/libupnp-pthread-force.patch
endif
endif
ifdef HAVE_ANDROID
	$(APPLY) $(SRC)/upnp/revert-ifaddrs.patch
endif
	$(APPLY) $(SRC)/upnp/miniserver.patch
	$(UPDATE_AUTOCONFIG)
	$(MOVE)

.upnp: upnp
	$(RECONF)
	cd $< && $(HOSTVARS) CFLAGS="$(UPNP_CFLAGS)" CXXFLAGS="$(UPNP_CXXFLAGS)" ./configure $(UPNP_CONF) $(HOSTCONF)
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
