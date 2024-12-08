f = open("file.txt","r")
res = 0
lines = f.readlines()
for line in lines:
    for c in line:
        if c.isdigit():
            res += int(c)*10
            break
    line = line[::-1]
    for c in line:
        if c.isdigit():
            res += int(c)
            break
print(res)