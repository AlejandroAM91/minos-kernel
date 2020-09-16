AUXFILES += $(KERNEL_BOOT_DIR)/config.mk
KERNEL_BOOT_ARCH_DIR := $(KERNEL_BOOT_DIR)/arch/$(ARCH)

# Arch config
-include $(KERNEL_BOOT_ARCH_DIR)/config.mk

_src_dir := $(KERNEL_BOOT_DIR)/src

_src_files := $(shell find $(_src_dir) -type f -name "*.c")
_dep_files := $(_src_files:.c=.d)
_obj_files := $(_src_files:.c=.o)
_cln_files := $(_dep_files) $(_obj_files)

KERNEL_BOOT_CLN := $(KERNEL_BOOT_ARCH_CLN) $(_cln_files)
KERNEL_BOOT_INIT := $(KERNEL_BOOT_ARCH_INIT)
KERNEL_BOOT_OBJS := $(KERNEL_BOOT_ARCH_OBJS) $(_obj_files)
KERNEL_BOOT_DEPS := $(_dep_files)
KERNEL_BOOT_END := $(KERNEL_BOOT_ARCH_END)
