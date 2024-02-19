import re

def is_game_possible(line, red_max:int, green_max:int, blue_max:int):
    for it in re.finditer("red",line):
        if last_number(line, it.start()) > red_max:
            return False
    for it in re.finditer("green", line):
        if last_number(line, it.start()) > green_max:
            return False
    for it in re.finditer("blue", line):
        if last_number(line, it.start()) > blue_max:
            return False
    return True

def last_number(text:str, index:int):
    ret = 0
    for i in enumerate(text[index-2::-1]):
        if i[1] == " ":
            return ret
        else:
            ret += 10**i[0]*int(i[1])

f = open("file.txt","r")
lines = f.readlines()

red_num = 12
green_num = 13
blue_num = 14
res = 0

for line in enumerate(lines, 1):
    if is_game_possible(line[1], red_num, green_num, blue_num):
        res += line[0]

print(res)