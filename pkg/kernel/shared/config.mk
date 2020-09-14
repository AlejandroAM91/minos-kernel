_dir = $(CURDIR)/shared
_arch_dir = $(_dir)/arch/$(ARCH)

_inc_dir = $(_dir)/inc
_src_dir = $(_dir)/src
_arch_inc_dir = $(_arch_dir)/inc
_arch_src_dir = $(_arch_dir)/src

#_asm = $(shell find $(_arch_src_dir) -name *.s)
#_src = $(shell find $(_src_dir) -name *.c)
#_src += $(shell find $(_arch_src_dir) -name *.c)

_dep := $(_src:.c=.d)
_obj := $(_asm:.s=.o) $(_src:.c=.o)

CCFLAGS += -I $(_arch_inc_dir)

KERNEL_AUX += $(_dir)/config.mk
KERNEL_CLN += $(_dep) $(_obj)
#KERNEL_DEP += $(_dep)
KERNEL_OBJ += $(_obj)
