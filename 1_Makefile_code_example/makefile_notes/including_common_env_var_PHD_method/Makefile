#
# ./Makefile
#
PATH_TO_TOP = .
export BUILD_VERSION := $(shell date -u +%Y%m%d_%H%M)
include $(PATH_TO_TOP)/Makefile.common

.PHONY: all
all:
	@#
	@# We want to clean the ROOT_STAGE_DIR before installing into it, but if the
	@# variable is empty, we could end up blowing away the root filesystem on the
	@# host machine (a.k.a. The Morgan Syndrome).  To prevent that, we add a few
	@# sanity checks before using the ROOT_STAGE_DIR.
	@#
	@if [ ! -z "$(ROOT_STAGE_DIR)" ] && [ "$(ROOT_STAGE_DIR)" != "/" ] ;\
	then                                                                \
	    if [ ! -d $(ROOT_STAGE_DIR) ] ;                                 \
	    then                                                            \
	        $(INSTALL) -m755 -d $(ROOT_STAGE_DIR) ;                     \
	    else                                                            \
	        echo "Cleaning $(ROOT_STAGE_DIR) ..." ;                     \
	        $(RM) -r $(ROOT_STAGE_DIR)/* ;                              \
	    fi;                                                             \
	else                                                                \
	    echo "ERROR: ROOT_STAGE_DIR not set or incorrect!" ;            \
	    exit 1 ;                                                        \
	fi
	@$(INSTALL) -m755 -d $(IMAGES_DIR)
	@$(MAKE) -C pace/host/tools install
	@$(MAKE) -C third_party all
	@$(MAKE) -C vendor all
	@$(MAKE) -C pace/target all
	@$(INSTALL) -m755 -d $(BUILD_DIR)/dev
	@$(INSTALL) -m755 -d $(BUILD_DIR)/home
	@$(INSTALL) -m755 -d $(BUILD_DIR)/proc
	@$(INSTALL) -m755 -d $(BUILD_DIR)/root
	@$(INSTALL) -m755 -d $(BUILD_DIR)/sys
	@$(INSTALL) -m755 -d $(BUILD_DIR)/tmp
	@$(INSTALL) -m755 -d $(BUILD_DIR)/var
	@$(INSTALL) -m755 -d $(BUILD_DIR)/Volumes
	@$(INSTALL) -m777 -d $(BUILD_DIR)/srv/tftp
	@$(TOP_BUILD_DIR)/pace/host/scripts/make_dev_entries.sh $(BUILD_DIR)/dev
	@#
	@# Because some of the files in $(BUILD_DIR) come straight from the repository,
	@# their permissions are read-only.  Make sure we can write all files and directories
	@# so we can strip them later
	@#
	@cd $(BUILD_DIR) ; sudo chmod -R u+w *


.PHONY: install
install: all
	#
	# Installing all rootfs components
	#
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)
	@echo $(BUILD_VERSION) > $(ROOT_STAGE_DIR)/BUILD_VERSION
	@$(MAKE) -C third_party install
	@$(MAKE) -C vendor install
	@$(MAKE) -C pace/target install
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/dev
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/home
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/proc
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/root
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/sys
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/tmp
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/var
	@$(INSTALL) -m755 -d $(ROOT_STAGE_DIR)/Volumes
	@$(INSTALL) -m777 -d $(ROOT_STAGE_DIR)/srv/tftp


.PHONY: package
package: install
	@$(TOP_BUILD_DIR)/pace/host/scripts/strip_dir_tree.sh $(TOP_BUILD_DIR) $(ROOT_STAGE_DIR)
	@#
	@# Before we build the kernel image, we must make sure $(ROOT_STAGE_DIR)/init exists, or the initramfs cannot be setup
	@#
	@cd $(ROOT_STAGE_DIR) ; ln -sf bin/busybox init
	@#
	@# Now make the compressed kernel image with the necessary initramfs included
	@#
	@$(MAKE) -C vendor kernel-img
	@#
	@# Move the kernel image someplace easy to access
	@#
	@$(CP) $(KERNEL_DIR)/arch/mips/boot/zbimage-linux-xload $(IMAGES_DIR)/PaceDiags-$(CHIP_TYPE)-kernel-rootfs.bin


#
# A quicker target for development.  Assumes that you have already built everything once
# and just rebuilds the programs and generates a new kernel image.
#
.PHONY: test
test: 
	@$(MAKE) -C pace/target/programs install
	@$(MAKE) -C $(KERNEL_DIR) V=$(DEBUG_BUILD) -j$(MAKE_JOBS) zbimage-linux-xload
	@$(CP) $(KERNEL_DIR)/arch/mips/boot/zbimage-linux-xload $(IMAGES_DIR)/PaceDiags-$(CHIP_TYPE)-kernel-rootfs.bin

#
# The purpose of this rule is to allow you to customize the cleaning process
# during the development -- choose just how much of the tree to wipe away.
# That way, if you are testing a specific part of the build, you don't have to
# wait for everything to build every time.
#
# So all the rules from the 'distclean' are in here, but the idea is for you
# to feel free to re-arrange them and comment them out as needed.  And only
# invoke this rule during the development.
#
.PHONY: clean
clean:
	#
	# Clean the intermediary directory
	#
	@#$(RM) -r $(BUILD_DIR)/*
	#
	# Clean the image files and the staged filesystem
	#
	@$(RM) -r $(STAGE_DIR)/*
	#
	# Let's try cleaning things in reverse order of building them
	#
	@$(MAKE) -C vendor distclean
	@#$(MAKE) -C third_party distclean
	#
	# Remember: we HAVE to do this last, in this order!  Otherwise some of the
	# older kernels won't be able to find make-3.81 we build, and their clean
	# rules will not work
	#
	@$(MAKE) -C vendor kernel-clean
	@$(MAKE) -C pace/host/tools distclean


.PHONY: distclean
distclean:
	#
	# Let's try cleaning things in some sort of reverse order of building them
	#
	@$(MAKE) -C pace/target distclean
	@$(MAKE) -C third_party distclean
	@$(MAKE) -C vendor distclean
	# Remember: we HAVE to do this last, in this order!
	@$(MAKE) -C vendor kernel-clean
	@$(MAKE) -C pace/host/tools distclean
	#
	# Clean the intermediary directory
	#
	@$(RM) -r $(BUILD_DIR)/*
	#
	# Clean the staged filesystem
	#
	@$(RM) -r $(STAGE_DIR)/*
	#
	# Clean the image files
	#
	@$(RM) -r $(IMAGES_DIR)


