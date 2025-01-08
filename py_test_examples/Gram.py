import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] =['SimHei']

def ppvalue(data):
    i = 0
    max = data[0]
    min = data[0]
    while i < len(data):
        if max < data[i]:
            max = data[i]
        if min > data[i]:
            min = data[i]
        i += 1
    return max - min

def average(data):
    sum = 0
    i = 0
    while i < len(data):
        sum += data[i]
        i += 1
    return sum / len(data)

def filter(data):
    after = []
    sum = 0
    i = 0
    j = 0
    while i < 10:
        while j < i * 5 + 5:
            if j >= len(data):
                return after
            sum += data[j]
            j += 1
        after.append(sum / 5)
        sum = 0
        i += 1
    return after


data = [5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3
        ,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3
        ,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3
        ,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3
        ,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3,5,2,3,5,6,1,5,3,6,4,5,9,4,8,6,3,4,5,3,5,6,4,5,2,1,5,6,4,5,6,4,2,5,6,3]
after = filter(data)

import pandas as pd

s = pd.Series(data)

s.plot()
plt.plot(data)
plt.plot(after)
plt.xlim([1,15])
plt.ylim([3,9])
plt.xlabel('采样次数')
plt.ylabel('V')
plt.title('均值滤波前后')
plt.show()



