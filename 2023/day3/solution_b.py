import re

f = open("file.txt","r")
lines = f.readlines()

def find_stars(line):
    stars = []
    for it in re.finditer(r"\*",line):
        stars.append(it)
    return stars

def gear_ratio(it : iter, line : enumerate, lines : list):
    number_of_neighbours = 0
    ratio = 1
    for it_num in re.finditer("[0-9]+",lines[line[0]-1]):
        if it_num.end()>=it.start() and it_num.start()<=it.start()+1:
            number_of_neighbours += 1
            ratio *= int(it_num[0])
    for it_num in re.finditer("[0-9]+",line[1]):
        if it_num.end() == it.start() or it_num.start() == it.start()+1:
            number_of_neighbours += 1
            ratio *= int(it_num[0])
    for it_num in re.finditer("[0-9]+",lines[line[0]+1]):
        if it_num.end()>=it.start() and it_num.start()<=it.start()+1:
            number_of_neighbours += 1
            ratio *= int(it_num[0])
    if(number_of_neighbours >= 2):
        return ratio
    else:
        return 0


def calculate_sum(lines):
    ret = 0
    for line in enumerate(lines):
        for it in find_stars(line[1]):
            ret += gear_ratio(it, line, lines)
    return ret

print(calculate_sum(lines))