import re

#solution would technically work, but would take a million years, let's try in c++

def get_seeds(lines):
    seeds = re.findall("[0-9]+", lines[0])
    return [int(x) for x in seeds]

def get_destination(lines, source_value, source_type):
    destination_index = 0
    for line in enumerate(lines):
        words = re.findall("[a-z]+", line[1])
        if len(words) != 0 and words[0] == source_type:
            destination_index = line[0]
            break
    for i in range(destination_index+1, len(lines)):
        if (lines[i][0] == "\n" or len(lines[i]) == 0):
            return source_value
        else:
            source_range_start = int(re.findall("[0-9]+", lines[i])[1])
            source_range_end = source_range_start + int(re.findall("[0-9]+", lines[i])[2])-1
            destination_range_start = int(re.findall("[0-9]+", lines[i])[0])
            if (source_value >= source_range_start and source_value <= source_range_end):
                return destination_range_start+(source_value - source_range_start)
    return source_value

def get_location_from_seed(lines, seed_num):
    soil_num = get_destination(lines, seed_num, "seed")
    fertilizer_num = get_destination(lines, soil_num, "soil")
    water_num = get_destination(lines, fertilizer_num, "fertilizer")
    light_num = get_destination(lines, water_num, "water")
    temperature_num = get_destination(lines, light_num, "light")
    humidity_num = get_destination(lines, temperature_num, "temperature")
    location_num = get_destination(lines, humidity_num, "humidity")
    return location_num

def get_lowest_soil(lines):
    seeds = get_seeds(lines)
    lowest = get_location_from_seed(lines, seeds[0])
    for i in range(0, len(seeds), 2):
        for j in range(seeds[i], seeds[i]+seeds[i+1]):
            location_num = get_location_from_seed(lines, j)
            if location_num < lowest:
                lowest = location_num
    return lowest

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    print(get_lowest_soil(lines))