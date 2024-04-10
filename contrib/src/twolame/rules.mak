# twolame

TWOLAME_VERSION := 0.4.0
TWOLAME_URL := $(SF)/twolame/twolame-$(TWOLAME_VERSION).tar.gz

ifdef BUILD_ENCODERS
PKGS += twolame
endif
ifeq ($(call need_pkg,"twolame"),)
PKGS_FOUND += twolame
endif

$(TARBALLS)/twolame-$(TWOLAME_VERSION).tar.gz:
	$(call download_pkg,$(TWOLAME_URL),twolame)

.sum-twolame: twolame-$(TWOLAME_VERSION).tar.gz

twolame: twolame-$(TWOLAME_VERSION).tar.gz .sum-twolame
	$(UNPACK)
	$(UPDATE_AUTOCONFIG)
	cd $(UNPACK_DIR) && cp config.guess config.sub build-scripts
	$(MOVE)

TWOLAME_CONF := CFLAGS="${CFLAGS} -DLIBTWOLAME_STATIC"

.twolame: twolame
	$(RECONF)
<<<<<<< master
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(TWOLAME_CONF)
	+$(MAKEBUILD)
	+$(MAKEBUILD) -C libtwolame
	+$(MAKEBUILD) -C libtwolame install
	+$(MAKEBUILD) install-data
=======
	cd $< && $(HOSTVARS) CFLAGS="${CFLAGS} -DLIBTWOLAME_STATIC" ./configure $(HOSTCONF)
	cd $< && $(MAKE)
	cd $< && $(MAKE) -C libtwolame install
	cd $< && $(MAKE) install-data
>>>>>>> origin/3.0.x
	touch $@
