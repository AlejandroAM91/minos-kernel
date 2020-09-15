# PROGRAMS
SHELL := /bin/sh

# DEFAULT CONFIG
TRIPLET ?= i686-elf
IMAGE_NAME ?= minos
IMAGE_VERSION ?= 0.0.0

# ENV
ARCH := $(shell python scripts/make/arch.py $(TRIPLET))

## COMPILERS
AS := $(TRIPLET)-as
CC := $(TRIPLET)-gcc

### FLAGS
CFLAGS := -Wall -Wextra -ffreestanding
LDLIBS := -lgcc -nostdlib

# MODULES
## KERNEL
KERNEL_DIR := $(CURDIR)/pkg/kernel

# AUXFILES
AUXFILES := $(CURDIR)/Makefile

# RULES
## BASE
.PHONY: all
all: kernel-all

.PHONY: clean
clean: kernel-clean

## IMPORTS
-include $(KERNEL_DIR)/config.mk

## COMMON
%.o: %.c $(AUXFILES)
	$(info Compiling $(patsubst $(CURDIR)/%,./%, $<)...)
	@$(CC) -c -MMD $(CFLAGS) $(CCFLAGS) -o $@ $<

%.o: %.s $(AUXFILES)
	$(info Compiling $(patsubst $(CURDIR)/%,./%, $<)...)
	@$(AS) -o $@ $<

