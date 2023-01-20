import os
from termcolor import colored

riscv_tests_path = './riscv-tests/build/bin'


cmd = 'make -C $NEMU_HOME run ARGS="-b -l nemu-log.txt" '
nemu_path = '$NEMU_HOME/build/riscv64-nemu-interpreter -l nemu-log.txt -b  \
            --diff=$NEMU_HOME/tools/spike-diff/build/riscv64-spike-so  '

npc_path = 'make -C $NPC_HOME test IMG='


def execCmd(cmd):
    r = os.popen(cmd)
    text = r.read()
    r.close()
    return text


execCmd('make -C $NEMU_HOME ')


files = os.listdir(riscv_tests_path)
absolute_paths = [os.path.abspath(
    os.path.join(riscv_tests_path, f)) for f in files]


for test_bin in absolute_paths:
    ret = execCmd(nemu_path + test_bin)
    file_name = os.path.basename(test_bin)
    if (-1 != ret.find('HIT GOOD TRAP')):
        print(colored(file_name+'---------ok', 'green'))
    else:
        print(colored(file_name+'---------bad', 'red'))


# for test_bin in absolute_paths:
#     ret = execCmd(npc_path + test_bin)
#     file_name = os.path.basename(test_bin)
#     if (-1 != ret.find('HIT GOOD')):
#        print(colored(file_name+'---------ok','green'))
#     else:
#         print(colored(file_name+'---------bad','red'))
