import re


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

def get_lowest_soil(lines):
    locations = []
    seeds = get_seeds(lines)
    for seed_num in seeds:
       soil_num = get_destination(lines, seed_num, "seed")
       fertilizer_num = get_destination(lines, soil_num, "soil")
       water_num = get_destination(lines, fertilizer_num, "fertilizer")
       light_num = get_destination(lines, water_num, "water")
       temperature_num = get_destination(lines, light_num, "light")
       humidity_num = get_destination(lines, temperature_num, "temperature")
       location_num = get_destination(lines, humidity_num, "humidity")
       locations.append(location_num)
    return min(locations)

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    print(get_lowest_soil(lines))
