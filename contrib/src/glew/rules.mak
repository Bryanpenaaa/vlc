# GLEW
GLEW_VERSION := 2.1.0
GLEW_URL := $(SF)/glew/glew/$(GLEW_VERSION)/glew-$(GLEW_VERSION).tgz

ifeq ($(call need_pkg,"glew"),)
PKGS_FOUND += glew
endif

$(TARBALLS)/glew-$(GLEW_VERSION).tgz:
	$(call download_pkg,$(GLEW_URL),glew)

.sum-glew: glew-$(GLEW_VERSION).tgz

glew: glew-$(GLEW_VERSION).tgz .sum-glew
	$(UNPACK)
	$(APPLY) $(SRC)/glew/glew-drop-debug-postfix.patch
	$(MOVE)

<<<<<<< master
.glew: glew toolchain.cmake
	$(CMAKECLEAN)
	$(HOSTVARS) $(CMAKE) -S $</build/cmake
	+$(CMAKEBUILD)
	$(CMAKEINSTALL)
=======
.glew: glew
	cd $< && $(HOSTVARS) GLEW_DEST=$(PREFIX) CFLAGS="$(CFLAGS) -DGLEW_STATIC" $(MAKE)
	cd $< && $(HOSTVARS) GLEW_DEST=$(PREFIX) $(MAKE) install
ifdef HAVE_WIN32
	-rm $(PREFIX)/lib/*glew32.dll*
endif
>>>>>>> origin/3.0.x
	touch $@
