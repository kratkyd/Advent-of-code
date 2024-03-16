#!/usr/bin/env python3
import re

def get_list(lines):
    ret = []
    times = re.findall("[0-9]+", lines[0])
    distances = re.findall("[0-9]+", lines[1])
    print(times)
    print(distances)
    for i in range(len(times)):
        ret.append((int(times[i]),int(distances[i])))
    return ret

def calculate_distances(time_full):
    ret = []
    for i in range(time_full+1):
        ret.append((time_full-i)*i)
    return ret
                
def over_record_num(time, record_dist):
    ret = 0
    for i in calculate_distances(time):
        if i > record_dist:
            ret+=1
    return ret

def get_result(lines):
    ret = 1
    for i in get_list(lines):
        num = over_record_num(i[0],i[1])
        if num != 0:
            ret *= num
    return ret

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    print(get_result(lines))
