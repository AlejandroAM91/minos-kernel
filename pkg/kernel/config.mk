# AUXFILES
AUXFILES += $(KERNEL_DIR)/config.mk

# SUBMODULES
KERNEL_BOOT_DIR := $(KERNEL_DIR)/boot
-include $(KERNEL_BOOT_DIR)/config.mk

# CONFIG
KERNEL_IMAGE := $(CURDIR)/$(IMAGE_NAME)-$(IMAGE_VERSION).img

_src_dir := $(KERNEL_DIR)/src

_src_files := $(shell find $(_src_dir) -type f -name "*.c")
_dep_files := $(_src_files:.c=.d)
_obj_files := $(_src_files:.c=.o)
_cln_files := $(_obj_files) $(_dep_files)

_ld_file := $(CURDIR)/scripts/ld/linker-$(ARCH).ld

# RULES
## BASE
kernel-all: $(KERNEL_IMAGE)

kernel-clean:
	$(info Removing kernel files..)
	-@$(RM) $(KERNEL_IMAGE) $(_cln_files) $(KERNEL_BOOT_CLN)

## COMPONENTS
$(KERNEL_IMAGE): $(KERNEL_BOOT_INIT) $(_obj_files) $(KERNEL_BOOT_OBJS) $(KERNEL_BOOT_END)
	$(info $@)
	$(info Creating $(notdir $@)...)
	@$(CC) $(CFLAGS) $(LDFLAGS) -T $(_ld_file) -o $@ $^ $(LDLIBS)

## DEPENDENCIES
-include $(KERNEL_BOOT_DEPS) $(_dep_files)
