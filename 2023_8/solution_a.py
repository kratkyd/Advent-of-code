#!/usr/bin/env python3
import re

def readInstructions(lines):
    ret = []
    for char in lines[0]:
        ret.append(char)
    ret.pop(len(ret)-1)
    return ret

def readNodes(lines):
    ret = []
    for i in range(2, len(lines)):
        ret.append(re.findall(r"[A-Z]+",lines[i]))
    return ret

def findNode(nodes, name):
    for node in nodes:
        if node[0] == name:
            return node

def track(nodes, instructions):
    current_node = findNode(nodes, "AAA")
    steps = 0

    while(True):
        for inst in instructions:
            if inst == "L":
                current_node = findNode(nodes, current_node[1])
            elif inst == "R":
                current_node = findNode(nodes, current_node[2])
            steps += 1
            if current_node[0] == "ZZZ":
                return steps



if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    print(readNodes(lines))
    print(readInstructions(lines))
    print(track(readNodes(lines),readInstructions(lines)))