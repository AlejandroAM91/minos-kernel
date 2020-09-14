import os
import sys

sys.path.append('scripts/scons')
import target

# Get inputs
triplet, arch = target.gettarget()

# Config global environment
env = Environment(
    AS = 'as',
    CC = 'gcc',
    ENV = {'PATH' : os.environ['PATH']},
)

# Config build environment
build_env = env.Clone(
    LDFLAGS = '-ffreestanding -nostdlib',
    LDLIBS = '-lgcc',
)
build_env.Append(CFLAGS = '-Wall -Wextra -ffreestanding')
if triplet != None:
    build_env.Replace(
        AS = '{}-{}'.format(triplet, env['AS']), 
        CC = '{}-{}'.format(triplet, env['CC']),
    )

# Execute scripts
SConscript(['internal/kernel/SConscript'], ['build_env', 'arch'])
