#include "VKIRSender.h"
#include <Arduino.h>

#define PWM_PIN 3

void VKIRSender::mark(int time){
	analogWriteAdvance(PWM_PIN,PWM_SOURCE_CLOCK_13MHZ,PWM_CLOCK_DIV1,342,171);
	delayMicroseconds(time);
}

void VKIRSender::space(int time){
	analogWriteAdvance(PWM_PIN,PWM_SOURCE_CLOCK_13MHZ,PWM_CLOCK_DIV1,342,0);
	delayMicroseconds(time);
}

void VKIRSender::enableIROut(int hz){

}
