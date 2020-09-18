# COMMON VARIABLES
## CONFIG
export OUTDIR  ?= $(CURDIR)
export TRIPLET ?= i686-elf

## PACKAGES
PACKAGES := pkg/kernel

# RULES
## BASE
all: $(PACKAGES)

clean:
	$(info Cleaning all packages...)
	@for d in $(PACKAGES); do \
    	$(MAKE) -C $$d clean; \
    done

## MODULES
.PHONY: $(PACKAGES)
$(PACKAGES):
	$(MAKE) -C $@
