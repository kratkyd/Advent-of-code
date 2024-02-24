import re
import numpy as np

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

def get_card_sum(lines, line_i): #line_i is index of line I am currently on, initializes on 0
    print(line_i)
    sum = 1
    winning_numbers = get_winning_numbers(lines[line_i])
    my_numbers = get_my_numbers(lines[line_i])
    for num in my_numbers:
        if num in winning_numbers:
            sum += 1
    for i in range(1, sum):
        sum -= 1
        if(line_i + i < len(lines)):
            sum += get_cards_sum(lines, line_i+i)
    return sum

def get_cards_sum(lines):
    sum = 0
    card_nums = [0]*len(lines)
    for line_i in range(len(lines)):
        card_nums[line_i] += 1
        score = 0
        winning_numbers = get_winning_numbers(lines[line_i])
        my_numbers = get_my_numbers(lines[line_i])
        for num in my_numbers:
            if num in winning_numbers:
                score += 1
        for i in range(1, np.clip(score+1, 0, len(lines)-line_i)):
            card_nums[line_i+i] += 1*card_nums[line_i]
    for num in card_nums:
        sum += num
    return sum


if __name__ ==  '__main__':
    f = open("file.txt", "r")

    lines = f.readlines()
    print(get_cards_sum(lines))
