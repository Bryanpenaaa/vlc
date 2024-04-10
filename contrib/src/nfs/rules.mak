# NFS
<<<<<<< master
NFS_VERSION := 5.0.2
NFS_URL := $(GITHUB)/sahlberg/libnfs/archive/libnfs-$(NFS_VERSION).tar.gz
=======
NFS_VERSION := 5.0.1
NFS_URL := https://github.com/sahlberg/libnfs/archive/libnfs-$(NFS_VERSION).tar.gz
>>>>>>> origin/3.0.x

PKGS += nfs
ifeq ($(call need_pkg,"libnfs >= 1.10"),)
PKGS_FOUND += nfs
endif

$(TARBALLS)/libnfs-$(NFS_VERSION).tar.gz:
	$(call download_pkg,$(NFS_URL),nfs)

.sum-nfs: libnfs-$(NFS_VERSION).tar.gz

nfs: libnfs-$(NFS_VERSION).tar.gz .sum-nfs
	$(UNPACK)
	mv libnfs-libnfs-$(NFS_VERSION) libnfs-$(NFS_VERSION)
<<<<<<< master
=======
	$(UPDATE_AUTOCONFIG)
>>>>>>> origin/3.0.x
	$(MOVE)

.nfs: nfs toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
	touch $@
