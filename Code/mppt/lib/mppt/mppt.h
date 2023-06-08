#ifndef mppt_H_
#define mppt_H_


int calculatePower(uint16_t adcVoltage, uint16_t current);
int calcPWM(float adcVoltage, int desired_voltage);

#endif /* INCFILE1_H_ */