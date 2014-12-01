# the idea is:
#	[1] having a parallelized tasks in make 
#	[2] have a hidden makefile target, so when clicking tabs in bash, the hidden target wouldn't show up
#	[3] use -j option in nested make, so even if no body used j, we will still use the most of it because we are including it by default

SHELL := /bin/bash

.PHONY: distclean .distclean_deprecated
distclean:
	$(MAKE) --jobs=$(shell grep processor /proc/cpuinfo | wc -l) .distclean_deprecated
	# ditclean message
	@echo "###################################################################################################################"
	@echo -e "the parallelized distclean is complete, but that doesn't mean all tasks have completed successfully!!\nIt is up to the user to verify all cleaning tasks have completed successfully"
	@echo "###################################################################################################################"

.SECONDARY: .distclean_deprecated
.distclean_deprecated:
	#
	# Let's try cleaning things in some sort of reverse order of building them
	#
	@$(MAKE) -C project/target distclean&
	@$(MAKE) -C third_party distclean&
	@$(MAKE) -C vendor distclean&
	# Remember: we HAVE to do this last, in this order!
	@$(MAKE) -C vendor kernel-clean&
	@$(MAKE) -C project/host/tools distclean&
	@$(MAKE) -C project/target/tools distclean&
	#
	# Clean the intermediary directory
	#
	@$(RM) -r $(BUILD_DIR)/*&
	#
	# Clean the staged filesystem
	#
	@$(RM) -r $(STAGE_DIR)/*&
	#
	# Clean the image files
	#
	@$(RM) -r $(IMAGES_DIR)&
	# wait for the parallelized distclean finishes
	wait 

