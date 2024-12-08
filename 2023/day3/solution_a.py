import re
import numpy as np

f = open("file.txt", "r")
lines = f.readlines()

def find_nums(line):
    nums = []
    for it in re.finditer("[0-9]+",line):
        nums.append(it)
    return nums
        # print(it.start())
        # print(it.end())

def calculate_sum(lines):
    ret = 0
    for line in enumerate(lines):
        for it in find_nums(line[1]):
            if is_part(it, line, lines):
                ret += int(it[0])
    return ret
            
def is_part(it, line, lines):#assumed same length of lines
    if ((it.start()!=0) and line[1][it.start()-1] != ".") or ((it.end() != len(line[1])-1) and line[1][it.end()] != "."):#character before and after
        return True
    for i in range(np.clip(it.start()-1,0,None), np.clip(it.end()+1,None,len(line[1])-1)):
        if line[0]!=0:#characters above
            if lines[line[0]-1][i] != ".":
                return True
        if line[0]!=len(lines)-1:#characters below
            if lines[line[0]+1][i] != ".":
                return True
    print()
    return False

print(calculate_sum(lines))
#could be remade, making one string and searching for chars instead
