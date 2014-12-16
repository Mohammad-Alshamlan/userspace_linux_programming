# Check COMPILKIND to see if release mode or debug mode to be used
ifeq '$(filter release, $(COMPILKIND))' ''
ifeq '$(filter debug, $(COMPILKIND))' ''
$(warning Both release and debug are not specified in COMPILKIND)
$(warning The default setting 'release' is used)
endif
else
ifneq '$(filter debug, $(COMPILKIND))' ''
$(warning Both release and debug are specified in COMPILKIND)
$(warning The default setting 'release' is used)
endif
endif

# Check COMPILKIND to see which libc runtime to be used
ifeq '$(filter uclibc, $(COMPILKIND))' ''
ifeq '$(filter glibc, $(COMPILKIND))' ''
$(warning Please specify libc runtime in COMPILKIND: uclibc or glibc)
$(warning Otherwise, the default setting 'glibc' is used)
endif
else
ifneq '$(filter glibc, $(COMPILKIND))' ''
$(warning Both uclibc and glibc are specified in COMPILKIND)
$(warning The default setting 'glibc' is used)
endif
endif

# Check COMPILKIND to see which floating point mode to be used
ifeq '$(filter hardfloat, $(COMPILKIND))' ''
ifeq '$(filter softfloat, $(COMPILKIND))' ''
$(warning Please specify floating point mode in COMPILKIND: hardfloat or softfloat)
$(warning Otherwise, the default setting 'hardfloat' is used)
endif
else
ifneq '$(filter softfloat, $(COMPILKIND))' ''
$(warning Both hardfloat and softfloat are specified in COMPILKIND)
$(warning The default setting 'hardfloat' is used)
endif
endif
