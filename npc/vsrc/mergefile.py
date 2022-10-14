from importlib.metadata import files
import os


socdef = "`define ysyx_041514_YSYX_SOC"

result = os.popen('find . -name "*.v"')
files = result.read()  # 获取所有 .v 文件的路径

log = open("./testfile.v", "w")  # 打开文件
log.truncate()
log.write(socdef)  # 添加宏定义，切换到 SOC 仿真环境

for path in files.splitlines():
    if path.find("ysyx_041514.v")!=-1:
        continue
    if path.find("ysyx_041514_S011HD1P_X32Y2D128_BW.v")!=-1:
        continue
    f = open(path).read()                         # 将打开的文件内容保存到变量f
    f = f.replace('`include "sysconfig.v"', " ")  #  include 去除
    f = f.replace('ysyx_041514_soc','ysyx_041514')# 模块名称替换，满足端口要求
    f = f.replace('`define MUL_SIM',' ')
    f = f.replace('`define DIV_SIM',' ')

    log.write(f)  # 写入文件
    print('已经合并：' + path)
log.close()

os.system("cp testfile.v /home/leesum/ysyxSoC/ysyx/soc/ysyx_041514.v")  # 更新 ysyxSOC 文件
os.system("rm ./testfile.v")
