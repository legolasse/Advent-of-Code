import json
import sys

data = json.load(sys.stdin)

answer1 = 0

def go(x):
    global answer1
    if type(x) is dict:
        ok = True
        for key in x:
            if x[key] == "red":
                ok = False
        print('Dict')
        if ok:
            for key in x:
                go(x[key])
    elif type(x) is list:
        print('List')
        for val in x:
            go(val)
    elif type(x) is int:
        answer1 = answer1 + x
    else:
        print('Other')

go(data)

print(answer1)

