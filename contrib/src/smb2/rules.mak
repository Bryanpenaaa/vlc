# SMB2
SMB2_VERSION := 4.0.0
<<<<<<< HEAD
SMB2_URL := $(GITHUB)/sahlberg/libsmb2/archive/v$(SMB2_VERSION).tar.gz

ifdef BUILD_NETWORK
ifndef HAVE_WIN32
PKGS += smb2
endif
endif
=======
SMB2_URL := https://github.com/sahlberg/libsmb2/archive/v$(SMB2_VERSION).tar.gz

>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
ifeq ($(call need_pkg,"smb2"),)
PKGS_FOUND += smb2
endif

$(TARBALLS)/libsmb2-$(SMB2_VERSION).tar.gz:
	$(call download_pkg,$(SMB2_URL),smb2)

.sum-smb2: libsmb2-$(SMB2_VERSION).tar.gz

smb2: libsmb2-$(SMB2_VERSION).tar.gz .sum-smb2
	$(UNPACK)
	$(MOVE)

<<<<<<< HEAD
SMB2_CONF := --disable-examples --disable-werror --without-libkrb5

.smb2: smb2
	cd $< && ./bootstrap
	$(MAKEBUILDDIR)
	$(MAKECONFIGURE) $(SMB2_CONF)
	+$(MAKEBUILD)
	+$(MAKEBUILD) install
=======
.smb2: smb2
	cd $< && ./bootstrap
	cd $< && $(HOSTVARS) ./configure --disable-examples --disable-werror --without-libkrb5 $(HOSTCONF)
	cd $< && $(MAKE) install
>>>>>>> 3e483547037e49f8ef828f2f0455593400968cf4
	touch $@
