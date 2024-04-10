# Nettle

NETTLE_VERSION := 3.7.3
NETTLE_URL := $(GNU)/nettle/nettle-$(NETTLE_VERSION).tar.gz

ifeq ($(call need_pkg,"nettle >= 3.4.1"),)
PKGS_FOUND += nettle
endif

ifdef HAVE_WIN32
<<<<<<< master
NETTLE_CONF += --disable-pic
=======
>>>>>>> origin/3.0.x
ifeq ($(ARCH),arm)
NETTLE_CONF += --disable-assembler
endif
endif
<<<<<<< master
NETTLE_CONF += --disable-documentation
=======
>>>>>>> origin/3.0.x

$(TARBALLS)/nettle-$(NETTLE_VERSION).tar.gz:
	$(call download_pkg,$(NETTLE_URL),nettle)

.sum-nettle: nettle-$(NETTLE_VERSION).tar.gz

nettle: nettle-$(NETTLE_VERSION).tar.gz .sum-nettle
	$(UNPACK)
	$(MOVE)

DEPS_nettle = gmp $(DEPS_gmp)

# GMP requires either GPLv2 or LGPLv3
.nettle: nettle
ifndef GPL
	$(REQUIRE_GNUV3)
endif
	$(RECONF)
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(NETTLE_CONF)
	+$(MAKEBUILD) install
=======
	cd $< && $(HOSTVARS) ./configure $(HOSTCONF) $(NETTLE_CONF)
	cd $< && $(MAKE) install
>>>>>>> origin/3.0.x
	touch $@
