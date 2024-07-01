
#ifndef BUTTON_H_
#define BUTTON_H_

#include "MKL46Z4.h"
#include "PWM.h"

void initButton();

void statusButton();

void check_count(int count);
#endif /* BUTTON_H_ */
