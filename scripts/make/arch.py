#!/usr/env python
import sys

ARCHS = {
    'i686': 'x86'
}
DEFAULT_ARCH = 'x86'

def arch():
    if len(sys.argv) > 1:
        triplet = sys.argv[1].split('-')
        if triplet[0] in ARCHS:
            return ARCHS[triplet[0]]
    
    sys.stderr.write('Warning: Not existing architecture, fallingback to x86')
    return DEFAULT_ARCH

print(arch())
