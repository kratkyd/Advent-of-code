#!/usr/bin/env python3
#correct!!!!!!!
import re

def get_seeds(lines):
    ret = []
    num = 0
    nums = re.findall("[0-9]+", lines[0])
    for i in enumerate([int(x) for x in nums]): 
        if(i[0]%2==0):
            num = int(i[1])
        else:
            ret.append((num, num+int(i[1])-1))
    return ret

def get_map_lines(lines, source_type):
    index = 0
    ret = []
    for line in enumerate(lines):
        words = re.findall("[a-z]+", line[1])
        if(len(words) != 0 and words[0] == source_type):
           index = line[0]
           break
    for i in range(index+1, len(lines)):
           if(lines[i][0] == "\n" or len(lines[i]) == 0):
               break
           else:
               arr = []
               for i in re.findall("[0-9]+", lines[i]):
                   arr.append(int(i))
               ret.append(arr)
    return ret

def get_destination(lines, source_tuples, source_type):

    map_lines = get_map_lines(lines, source_type)
    ret = []
    for i in map_lines:
        for j in enumerate(source_tuples):
            val = (0,0)
            if (j[1][0] < i[1]+i[2]) and (j[1][1] >= i[1]) and j[1] != (0,0):
                ret.append(((max(j[1][0],i[1])+i[0]-i[1]),min(j[1][1],i[1]+i[2]-1)+i[0]-i[1]))
                if(j[1][0]<i[1]):
                    source_tuples.append((j[1][0],i[1]-1))
                if(j[1][1]>i[1]+i[2]-1):
                    source_tuples.append((i[1]+i[2],j[1][1]))
                source_tuples[j[0]] = (0,0)
    source_tuples = [x for x in source_tuples if x != (0,0)]
    ret = ret + source_tuples
    return ret

def get_lowest_location_from_seeds(lines):
    soils = get_destination(lines, get_seeds(lines), "seed")

    fertilizers = get_destination(lines, soils, "soil")

    waters = get_destination(lines, fertilizers, "fertilizer")

    lights = get_destination(lines, waters, "water")
    temperatures = get_destination(lines, lights, "light")
    humidities = get_destination(lines, temperatures, "temperature")
    locations = get_destination(lines, humidities, "humidity")
    return sorted(locations)[0][0]

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    #print(get_destination(lines, get_seeds(lines), "seed"))
    print(get_lowest_location_from_seeds(lines))
