# COMMON VARIABLES
## CONFIG
IMAGE   ?= minos
OUTDIR  ?= $(CURDIR)
TRIPLET ?= i686-elf
VERSION ?= 0.0.0

ARCH    ?= $(shell python ../../scripts/make/arch.py $(TRIPLET))

## SOURCES
KERNEL_ASM :=
KERNEL_AUX := $(CURDIR)/Makefile
KERNEL_INC := 
KERNEL_OUT := $(OUTDIR)/$(IMAGE).img 
KERNEL_SRC := 

## BUILD
KERNEL_OBJ     := $(KERNEL_ASM:.s=.o) $(KERNEL_SRC:.c=.o)
KERNEL_DEP     := $(KERNEL_SRC:.c=.d)
KERNEL_PREOBJ  :=
KERNEL_POSTOBJ :=

## CLEAN
KERNEL_CLN := $(KERNEL_OBJ) $(KERNEL_DEP)

## FLAGS
CFLAGS  := -Wall -Wextra -ffreestanding
LDFLAGS := -T ../../scripts/ld/linker-$(ARCH).ld
LDLIBS  := -lgcc -nostdlib

## PROGRAMS
AS := $(TRIPLET)-as
CC := $(TRIPLET)-gcc
RM := rm -f

# CONFIG
all:

-include boot/config.mk

# RULES
## BASE
.PHONY: all
all: $(KERNEL_OUT)

.PHONY: clean
clean:
	$(RM) $(KERNEL_CLN)

## PROJECT
$(KERNEL_OUT): $(KERNEL_PREOBJ) $(KERNEL_OBJ) $(KERNEL_POSTOBJ)
	$(info Creating $(notdir $@)...)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)

## COMMON
%.o: %.c $(KERNEL_AUX)
	$(info Compiling $(patsubst $(CURDIR)/%,./%, $<)...)
	@$(CC) -c -MMD $(CFLAGS) $(CCFLAGS) -o $@ $<

-include $(KERNEL_DEP)
