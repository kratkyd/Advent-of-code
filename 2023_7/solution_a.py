#!/usr/bin/env python3
import re

def determine_priority(hand): #0 for high card, 6 for five of a kind, hand is 5 chars
    sorted_hand = "_"+"".join(sorted(hand))+"_"

    fives = len(re.findall(r'(?=(.)(?!\1)(.)\2\2\2\2(?!\2))',sorted_hand))
    fours = len(re.findall(r'(?=(.)(?!\1)(.)\2\2\2(?!\2))',sorted_hand))
    threes = len(re.findall(r'(?=(.)(?!\1)(.)\2\2(?!\2))',sorted_hand))
    twos = len(re.findall(r'(?=(.)(?!\1)(.)\2(?!\2))',sorted_hand))

    if fives>0:
        return 6
    elif fours>0:
        return 5
    elif threes>0:
         if twos>0:
            return 4
         else:
            return 3
    elif twos==2:
         return 2
    elif twos==1:
         return 1
    else:
         return 0

    #find = re.findall(r'(?=(.)(?!\1)(.)\2(?!\2))',sorted_hand) find exactly two

    

if __name__ == "__main__":
    f = open("test_file.txt", "r")
    lines = f.readlines()
    for line in lines:
        print(determine_priority(re.search(r'[^ ]+',line)[0]))
