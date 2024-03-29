#!/usr/bin/env python3
import re

cards = ['J','2','3','4','5','6','7','8','9','T','Q','K','A']

def determine_priority(hand): #0 for high card, 6 for five of a kind, hand is 5 chars
    sorted_hand = "_"+"".join(sorted(hand))+"_"

    fives = len(re.findall(r'(?=(.)(?!\1)(.)\2\2\2\2(?!\2))',sorted_hand))
    fours = len(re.findall(r'(?=(.)(?!\1)(.)\2\2\2(?!\2))',sorted_hand))
    threes = len(re.findall(r'(?=(.)(?!\1)(.)\2\2(?!\2))',sorted_hand))
    twos = len(re.findall(r'(?=(.)(?!\1)(.)\2(?!\2))',sorted_hand))
    j_num = len(re.findall(r'J', sorted_hand))

    if fives>0 or (fours>0 and j_num==1) or (threes>0 and j_num==2) or (twos>0 and j_num==3) or (j_num>3):
        return 6
    elif fours>0 or (threes>0 and j_num==1) or (twos>1 and j_num==2) or (j_num==3):
        return 5
    elif threes>0 or (twos>0 and j_num==1) or (j_num==2):
         if (twos==1 and j_num==0) or (twos==2 and j_num==1):
            return 4
         else:
            return 3
    elif twos==2:
         return 2
    elif twos==1 or (j_num==1):
         return 1
    else:
         return 0

    #find = re.findall(r'(?=(.)(?!\1)(.)\2(?!\2))',sorted_hand) find exactly two


def is_hand_better(hand1, hand2): #is hand1 better than hand2
    hand1_value = determine_priority(hand1)
    hand2_value = determine_priority(hand2)

    if hand1_value > hand2_value:
        return True
    elif hand1_value < hand2_value:
        return False
    else:
        for i in range(5):
            if cards.index(hand1[i]) > cards.index(hand2[i]):
                return True
            elif cards.index(hand2[i]) > cards.index(hand1[i]):
                return False
    return False

def quicksort_hands(hands, low, high):
    if (low < high):
        pivot = hands[high]
        it = low
        for i in range(low, high+1):
            if is_hand_better(pivot[0], hands[i][0]):
                hands[i], hands[it] = hands[it], hands[i]
                it += 1
        hands[it], hands[high] = hands[high], hands[it]
        quicksort_hands(hands, low, it-1)
        quicksort_hands(hands, it+1, high)

    return hands

def total(hands):
    res = 0
    quicksort_hands(hands, 0, len(hands)-1)
    print(hands)
    for hand in enumerate(hands):
        res += (hand[0]+1)*hand[1][1]
    return res

if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()
    hands = [((re.findall("[A-Z0-9]+", x))[0], int((re.findall("[A-Z0-9]+", x))[1])) for x in lines]
    print(total(hands))
    print(is_hand_better("KKJKJ",""))
    #for line in lines:
#        print(determine_priority(re.search(r'[^ ]+',line)[0]))
