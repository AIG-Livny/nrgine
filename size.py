import sys
import os
import subprocess

# "size" need to know exact filename with extension.
# GCC and make operate only with filename but 
# extension may be different in different OS     
def get_exe_path(exepath = sys.argv[1]):
    dir     = os.path.dirname(exepath)
    if not os.path.exists(dir):
        exit()
    name    = os.path.basename(exepath)
    for i in os.listdir(dir):
        if os.path.splitext(i)[0] == name:
            return dir+"/"+i
    return exepath

# Colorful text Win/Lin
def color_text(color, text):
    return f"[{color}m{text}[0m" if os.name == 'nt' else f"\\033[{color}m{text}\\033[0m"

newsize = []
oldsize = []
def diff(i):
    d = int(newsize[i]) - int(oldsize[i])
    if d < 0:
        return f"{newsize[i]}({color_text(32,str(d))})"
    elif d > 0:
        return f"{newsize[i]}({color_text(31,'+'+str(d))})"
    else:
        return f"{newsize[i]}({str(d)})"




if len(sys.argv) < 3:
    exit()

if sys.argv[2] == '-set':
    olso = subprocess.run(['size', get_exe_path()], capture_output=True).stdout.decode("utf-8")
    if olso == '':
        exit()
    f = open('size_old.txt','w+')
    f.write(olso)
    f.close()
    exit()

if sys.argv[2] == '-get':
    newsize = subprocess.run(['size', get_exe_path()], capture_output=True).stdout.decode("utf-8").split()
    if newsize == []:
        exit()
    if os.path.exists('size_old.txt'):
        f = open('size_old.txt')
        oldsize = f.read().split()
        f.close()
    if oldsize == []:
        print(f"{newsize[0]}: {newsize[6]}    {newsize[1]}: {newsize[7]}    {newsize[2]}: {newsize[8]}   Summ: {newsize[9]}")
        exit()
    os.remove('size_old.txt')
    print(f"{newsize[0]}: {diff(6)}    {newsize[1]}: {diff(7)}    {newsize[2]}: {diff(8)}   Summ: {diff(9)}")