import re

def calculate_power(line):
    red_max = 0
    green_max = 0
    blue_max = 0
    for it in re.finditer("red",line):
        num = last_number(line, it.start())
        if num > red_max:
            red_max = num
    for it in re.finditer("green", line):
        num = last_number(line, it.start())
        if num > green_max:
            green_max = num
    for it in re.finditer("blue", line):
        num = last_number(line, it.start())
        if num > blue_max:
            blue_max = num
    return red_max*green_max*blue_max

def last_number(text:str, index:int):
    ret = 0
    for i in enumerate(text[index-2::-1]):
        if i[1] == " ":
            return ret
        else:
            ret += 10**i[0]*int(i[1])

f = open("file.txt", "r")
lines = f.readlines()

res = 0
for line in lines:
    res += calculate_power(line)

print(res)