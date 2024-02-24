import re

def get_winning_numbers(line):
    numbers = []
    for it in re.finditer("\\|", line):
        line = line[:it.start()]
    for it in re.finditer("[0-9]+",line):
        numbers.append(int(it[0]))
    numbers.pop(0)
    return numbers

def get_my_numbers(line):
    numbers = []
    for it in re.finditer("\\|", line):
        line = line[it.start():]
    for it in re.finditer("[0-9]+", line):
        numbers.append(int(it[0]))
    return numbers

def calculate_score(line):
    score = 0
    my_numbers = get_my_numbers(line)
    winning_numbers = get_winning_numbers(line)
    for num in my_numbers:
        if num in winning_numbers:
            if(score == 0):
                score = 1
            else:
                score *= 2
    return score

if __name__ ==  '__main__':
    f = open("file.txt", "r")
    lines = f.readlines()
    sum = 0
    for line in lines:
        sum += calculate_score(line)
    print(sum)