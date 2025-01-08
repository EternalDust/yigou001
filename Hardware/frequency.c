//
// Created by Joy on 2025/1/5.
// Encoding UTF-8
//
#include <stdio.h>

#include "Data.h"

//假设ADC采样频率在2000次每秒且数据完整上传，则有公式T = (1 / （波峰数+波谷数）/2)s
//鉴于开发板算力有限，调整为单次波峰波谷计数方式

int frequency(const int* array, int Length){
    //int Length = length(array);
    int i = 0, j = 0;
    int max = 0;
    int min = 0;
    int max_index = 0;
    int min_index = 0;

    while (i < Length) {
        if (array[i] > max) {
            max = array[i];
            max_index = i;
        }
        ++i;
    }
    min = max;
    j = max_index;

    while (j < Length && j < max_index * 6) {  //一般极大值极小值在均匀信号下不会超过一个周期，保险起见设置三个
        if (array[j] < min) {
            min = array[j];
            min_index = j;
        }
        ++j;
    }

    return min_index == max_index ? 0 : 1000 / (min_index - max_index); //f = 2000 /（j - i）* 2
  }

int frequency_justmax(const int* array, int Length) {
    int i = 0, j = 0;
    int max = 0;
    int max_index = 0;
    while (i < Length) {
        if (array[i] > max) {
            max = array[i];
            max_index = i;
        }
        ++i;
    }
    return max_index == 0 ? 0 : 1000 / max_index;  //2000 / max_index / 2
}

//对于正弦信号，由于变化率在极值点处取得极小值，导致两种方法计算出来数据偏差较大、
//若为按线性均匀变化的信号，变化率的绝对值基本不变，故周期计算的值采用极大值与极大极小相减产生的变化不显著
//可参考一下frequency.py文件

// int main() {
//     int array[] = {1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0
//     ,1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,9,8,7,6,5,4,3,2,1,0};

//     printf("%d", frequency(array, sizeof(array) / sizeof(int)) );

//     return 0;
// }