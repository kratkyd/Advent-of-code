import re

#yet again would take a year to finish (probably, depending on the actual value. If it's 12, I'll punch somebody)

def get_seeds(lines):
    ret = []
    seeds = re.findall("[0-9]+", lines[0])
    for i in enumerate([int(x) for x in seeds]):
        if(i[0]%2==0):
            print(i)
    return [int(x) for x in seeds]

def get_source(lines, destination_value, source_type):
    source_index = 0
    for line in enumerate(lines):
        words = re.findall("[a-z]+", line[1])
        if len(words) != 0 and words[0] == source_type:
            source_index = line[0]
            break
    for i in range(source_index+1, len(lines)):
        if(lines[i][0] == "\n" or len(lines[i]) == 0):
            return destination_value
        else:
            destination_range_start = int(re.findall("[0-9]+", lines[i])[0])
            destination_range_end = destination_range_start + int(re.findall("[0-9]+", lines[i])[2])-1
            source_range_start = int(re.findall("[0-9]+", lines[i])[1])
            if (destination_value >= destination_range_start and destination_value <= destination_range_end):
                return source_range_start+(destination_value-destination_range_start)

def get_seed_from_location(lines, location_num):
    humidity_num = get_source(lines, location_num, "humidity")
    temperature_num = get_source(lines, humidity_num, "temperature")
    light_num = get_source(lines, temperature_num, "light")
    water_num = get_source(lines, light_num, "water")
    fertilizer_num = get_source(lines, water_num, "fertilizer")
    soil_num = get_source(lines, fertilizer_num, "soil")
    seed_num = get_source(lines, soil_num, "seed")
    return seed_num

#def get_lowest_location(lines):
#    seeds = get_seeds(lines)
#    lowest = 0
#    location_index = 0
#    for line in enumerate(lines):
#        words = re.findall("[a-z]+", line[1])
#        if(len(words) != 0 and words[0] == "humidity"):
#           location_index = line[0]
#           break
#    for i in range(location_index+1, len(lines)):
#        print(lines[i])
#        if(lines[i][0] == "\n" or len(lines[i]) == 0):
#            return lowest
#        else:
#           location_range_start = int(re.findall("[0-9]+", lines[i])[0])
#           location_range_end = location_range_start+int(re.findall("[0-9]+", lines[i])[2])
#           for j in range(location_range_start, location_range_end):
#               if get_seed_from_location(lines, j) in seeds:
#                   print(get_seed_from_location(lines, j))
#                   print(j)

def get_lowest_location(lines):
    it = 0
    while (True):
        if it%1000==0:
            print(it)
        if get_seed_from_location(lines, it) in get_seeds(lines):
            return it
        it += 1

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    print(get_seeds(lines))

