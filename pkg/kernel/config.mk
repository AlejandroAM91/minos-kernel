AUXFILES += $(KERNEL_DIR)/config.mk

KERNEL_BOOT_DIR := $(KERNEL_DIR)/boot/$(ARCH)

-include $(KERNEL_BOOT_DIR)/config.mk

_src_dir := $(KERNEL_DIR)/src

_src_files := $(shell find $(_src_dir) -type f -name "*.c")
_obj_files := $(_src_files:.c=.o) $(KERNEL_BOOT_OBJS)

_ld_file := $(CURDIR)/scripts/ld/linker-$(ARCH).ld

# RULES
$(KERNEL_IMAGE): $(KERNEL_BOOT_INIT) $(_obj_files) $(KERNEL_BOOT_END)
	$(info Creating $(notdir $@)...)
	@$(CC) $(CFLAGS) $(LDFLAGS) -T $(_ld_file) -o $@ $^ $(LDLIBS)
