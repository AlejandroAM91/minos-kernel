_dir = $(CURDIR)/boot
_arch_dir = $(_dir)/arch/$(ARCH)

_src_dir = $(_dir)/src
_arch_src_dir = $(_arch_dir)/src

_asm = $(shell find $(_arch_src_dir) -name *.s)
_src = $(shell find $(_src_dir) -name *.c)
_src += $(shell find $(_arch_src_dir) -name *.c)

_crti := $(_arch_src_dir)/crti.o
_crtn := $(_arch_src_dir)/crtn.o
_crtbegin := $(shell $(CC) -print-file-name=crtbegin.o)
_crtend   := $(shell $(CC) -print-file-name=crtend.o)

_dep := $(_src:.c=.d)
_obj := $(_asm:.s=.o) $(_src:.c=.o)
_obj := $(filter-out $(_crti) $(_crtn), $(_obj))

KERNEL_AUX += $(_dir)/config.mk
KERNEL_CLN += $(_dep) $(_obj) $(_crti) $(_crtn)
KERNEL_DEP += $(_dep)
KERNEL_OBJ += $(_obj)
KERNEL_PREOBJ  += $(_crti) $(_crtbegin)
KERNEL_POSTOBJ += $(_crtend) $(_crtn)
