# jpeg

<<<<<<< master
JPEG_VERSION := 2.0.8-esr
JPEG_URL := $(GITHUB)/libjpeg-turbo/libjpeg-turbo/archive/refs/tags/$(JPEG_VERSION).tar.gz
=======
JPEG_VERSION := 9b
JPEG_URL := http://www.ijg.org/files/jpegsrc.v$(JPEG_VERSION).tar.gz
>>>>>>> origin/3.0.x

$(TARBALLS)/libjpeg-turbo-$(JPEG_VERSION).tar.gz:
	$(call download_pkg,$(JPEG_URL),jpeg)

.sum-jpeg: libjpeg-turbo-$(JPEG_VERSION).tar.gz

jpeg: libjpeg-turbo-$(JPEG_VERSION).tar.gz .sum-jpeg
	$(UNPACK)
<<<<<<< master
=======
	mv jpeg-$(JPEG_VERSION) jpegsrc.v$(JPEG_VERSION)
	$(APPLY) $(SRC)/jpeg/no_executables.patch
	$(UPDATE_AUTOCONFIG)
>>>>>>> origin/3.0.x
	$(MOVE)

JPEG_CONF:= -DENABLE_SHARED=OFF -DWITH_TURBOJPEG=OFF

.jpeg: jpeg toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) $(JPEG_CONF)
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
	touch $@
