import numpy as np

# 假设ADC采样频率在2000次每秒且数据完整上传，则有公式T = (1 / （波峰数+波谷数）/2)s
# 鉴于开发板算力有限，调整为单次波峰波谷计数方式

def frequency(data):
    i = 0
    max = data[0]
    max_index = 0
    min_index = 0
    while i < len(data):
        if max < data[i]:
            max = data[i]
            max_index = i
        i += 1
    min = max
    j = max_index
    while j < len(data) and j < max_index * 6:  # 一般极大值极小值在均匀信号下不会超过两个半周期，保险起见设置三个
        if min > data[j]:
            min = data[j]
            min_index = j
        j += 1
    return 1000 / (min_index - max_index)
    # f = 2000 /（j - i）* 2



def frequency_justmax(data):
    i = 0
    max = data[0]
    max_index = 0
    while i < len(data):
        if max < data[i]:
            max = data[i]
            max_index = i
        i += 1
    return 1000 / max_index  # 2000 / max_index / 2


x = np.linspace(0, 2 * np.pi, 60)
y = np.sin(x)

print(frequency(y))  # 对于正弦信号，由于变化率在极值点处取得极小值，导致两种方法计算出来数据偏差较大
print(frequency_justmax(y))

linear_positive = np.linspace(0, 20, 50)
linear_negative = np.linspace(20, 0, 50)

line = np.concatenate((linear_positive,linear_negative))

final = np.tile(line,10)  # 这里生成的是按线性均匀变化的信号，变化率的绝对值基本不变，故周期计算的值采用极大值与极大极小相减产生的变化不显著
print(frequency(final))
print(frequency_justmax(final))
print(final)