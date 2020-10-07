# COMMON VARIABLES
## CONFIG
IMAGE   ?= minos
OUTDIR  ?= $(CURDIR)
TRIPLET ?= i686-elf
VERSION ?= 0.0.0

ARCH    ?= $(shell python ../../scripts/make/arch.py $(TRIPLET))

## PROGRAMS
AS := $(TRIPLET)-as
CC := $(TRIPLET)-gcc
RM := rm -f

## SOURCES
### DIRS
_inc_dir := $(CURDIR)/inc
_src_dir := $(CURDIR)/src

_arch_dir := $(CURDIR)/arch/$(ARCH)
# _arch_inc_dir := $(_arch_dir)/inc
_arch_src_dir := $(_arch_dir)/src

### FILES
_asm := $(shell find $(_arch_src_dir) -name "*.s")
_src := $(shell find $(_src_dir) -name "*.c")
_src += $(shell find $(_arch_src_dir) -name "*.c")

_crti := $(_arch_src_dir)/crti.o
_crtn := $(_arch_src_dir)/crtn.o
_crtbegin := $(shell $(CC) -print-file-name=crtbegin.o)
_crtend   := $(shell $(CC) -print-file-name=crtend.o)

_dep := $(_src:.c=.d)
_obj := $(_asm:.s=.o) $(_src:.c=.o)
_obj := $(filter-out $(_crti) $(_crtn), $(_obj))

### RESULT
KERNEL_ASM := $(_asm)
KERNEL_AUX := $(CURDIR)/Makefile
KERNEL_INC := $(_arch_inc_dir) $(_inc_dir)
KERNEL_OUT := $(OUTDIR)/$(IMAGE).img 
KERNEL_SRC := $(_src)

## BUILD
KERNEL_OBJ     := $(_obj)
KERNEL_DEP     := $(_dep)
KERNEL_PREOBJ  := $(_crti) $(_crtbegin)
KERNEL_POSTOBJ := $(_crtend) $(_crtn)

## CLEAN
KERNEL_CLN := $(KERNEL_OUT) $(KERNEL_OBJ) $(KERNEL_DEP)

## FLAGS
CFLAGS  := -Wall -Wextra -ffreestanding
CCFLAGS := $(patsubst %, -I%, $(KERNEL_INC))
LDFLAGS := -T ../../scripts/ld/linker-$(ARCH).ld
LDLIBS  := -lgcc -nostdlib

# RULES
## BASE
.PHONY: all
all: $(KERNEL_OUT)

.PHONY: clean
clean:
	$(info Removing files...)
	@$(RM) $(KERNEL_CLN)

## PROJECT
$(KERNEL_OUT): $(KERNEL_PREOBJ) $(KERNEL_OBJ) $(KERNEL_POSTOBJ)
	$(info Creating $(notdir $@)...)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

## COMMON
%.o: %.c $(KERNEL_AUX)
	$(info Compiling $(patsubst $(CURDIR)/%,./%, $<)...)
	@$(CC) -c -MMD $(CFLAGS) $(CCFLAGS) -o $@ $<

%.o: %.s $(KERNEL_AUX)
	$(info Compiling $(patsubst $(CURDIR)/%,./%, $<)...)
	@$(AS) -o $@ $<

-include $(KERNEL_DEP)
