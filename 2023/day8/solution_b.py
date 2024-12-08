#!/usr/bin/env python3
import re
import math

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

def findAllNodes(nodes, names):
    ret = []
    for name in names:
        for node in nodes:
            if node[0] == name:
                ret.append(node)
    return ret

def track(nodes, instructions):
    steps = 0
    current_nodes = []
    nums = []
    for node in nodes:
        if node[0][2] == "A":
            current_nodes.append(node)
    print(current_nodes)
    for node in current_nodes:
        cont = True
        while(cont):
            for inst in instructions:
                if inst == "L":
                    node=findNode(nodes, node[1])
                elif inst == "R":
                    node=findNode(nodes, node[2])
                steps += 1
                if node[0][2] == "Z":
                    print(steps)
                    print(node[0])
                    nums.append(steps)  
                    cont = False
                    steps = 0
                    break
    return math.lcm(nums[0],nums[1],nums[2],nums[3],nums[4],nums[5])


if __name__ == "__main__":
    f = open("file.txt", "r")
    lines = f.readlines()

    print(track(readNodes(lines),readInstructions(lines)))