#!/usr/bin/env python3
import re

def get_data(lines):
    ret = 0
    times = re.findall("[0-9]+", lines[0])
    distances = re.findall("[0-9]+", lines[1])
    time = ""
    distance = ""

    for i in range(len(times)):
        time += times[i]
        distance += distances[i]
    return (int(time),int(distance))

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

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()
    data = get_data(lines)
    print(over_record_num(data[0],data[1]))
