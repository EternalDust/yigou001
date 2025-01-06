//
// Created by Joy on 2025/1/5.
//
#include "ADC.h"
#include "Data.h"

uint16_t advanced_data[SingleTrig_SIZE];

/*adcbuff*//*不可用*/
//int length(const int* array) {
//    return sizeof(array) / sizeof(array[0]);
//}

int cal_ppvalue(const uint16_t* array){
    int max = array[0];
    int min = array[0];

    for(int i = 0;i < BUFFER_SIZE; ++i)  if(max < array[i])    max = array[i];
    for(int i = 0;i < BUFFER_SIZE; ++i)  if(min > array[i])    min = array[i];

    return max - min;
}

int average_array(const uint16_t* array){
    int sum = 0;
    for(int i = 0; i < BUFFER_SIZE; ++ i)    sum += array[i];

    return sum / BUFFER_SIZE;
}
/*
void mean_filter(void){
    int sum = 0;
    for(int i = 0; i < 10; ++i){
        for(int j = i * 5; j < i * 5 + 5; ++j){
            if (j >= SingleTrig_SIZE)
                return;
            sum += adcbuff[j];
        }
        advanced_data[i] = sum / 5;
        sum = 0;
    }
}
*/
