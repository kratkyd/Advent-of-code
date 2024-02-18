f = open("file.txt","r")
lines = f.readlines()

numbers = ["zero","one","two","three","four","five","six","seven","eight","nine","ten"]
num_enum = list(enumerate(numbers))

def check_first(str):
    subline = ""
    for c in str:
        if c.isdigit():
            return int(c)
        else:
            subline += c
        for num in num_enum:
            if num[1] in subline:
                return num[0]

def check_last(str):
    subline = ""
    str = str[::-1]
    for c in str:
        if c.isdigit():
            return int(c)
        else:
            subline += c
        for num in num_enum:
            if num[1] in subline[::-1]:
                return num[0]

res = 0
for line in lines:
    res += 10*check_first(line)
    res += check_last(line)
print(res)