import os

ARCHS = {
    'i686': 'x86'
}
DEFAULT_ARCH = 'x86'

def gettarget():
    triplet = os.getenv('TARGET')
    arch = DEFAULT_ARCH
    if triplet != None:
        triplet_split = triplet.split('-')
        arch = ARCHS[triplet_split[0]]
    return triplet, arch
