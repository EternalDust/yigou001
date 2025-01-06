
#include <stdint.h>

#ifndef DATA_H_
#define DATA_H_

//extern uint16_t advanced_data[SingleTrig_SIZE];
//void mean_filter();
int frequency(const uint16_t* array, int Length);
int cal_ppvalue(const uint16_t* array);
int average_array(const uint16_t* array);
int frequency_justmax(const uint16_t* array, int Length);

#endif
