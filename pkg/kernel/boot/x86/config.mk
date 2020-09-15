AUXFILES += $(KERNEL_BOOT_DIR)/config.mk

_src_dir := $(KERNEL_BOOT_DIR)/src

_crti := $(_src_dir)/crti.o
_crtn := $(_src_dir)/crtn.o
_crtbegin := $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
_crtend := $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)


_asm_files := $(shell find $(_src_dir) -type f -name "*.s")
_src_files := $(shell find $(_src_dir) -type f -name "*.c")
_obj_files := $(_asm_files:.s=.o) $(_src_files:.c=.o)
_cln_files := $(_obj_files)

_obj_files := $(filter-out $(_crti) $(_crtn), $(_obj_files))

KERNEL_BOOT_CLN := $(_cln_files)
KERNEL_BOOT_INIT := $(_crti) $(_crtbegin)
KERNEL_BOOT_OBJS := $(_obj_files)
KERNEL_BOOT_END := $(_crtend) $(_crtn)
