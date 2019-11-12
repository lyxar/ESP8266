/*
 * DHT11_Master.h
 *
 * Created: 07-11-2019 10:23:21
 *  Author: Emil Holm Hansen
 */ 


#ifndef DHT11_MASTER_H_
#define DHT11_MASTER_H_

#ifndef  F_CPU
#define F_CPU 16000000UL
#endif
#define DHT_PORT PORTA
#define DHT_DDR DDRA
#define DHT_PIN PINA
#define DHT_BIT PA1

#define bit_is_set(sfr,bit) \
(_SFR_BYTE(sfr) & _BV(bit))
#define bit_is_clear(sfr,bit) \
(!(_SFR_BYTE(sfr) & _BV(bit)))
#define set_bit(port, bit) (port) |= (1<<(bit))
#define clear_bit(port, bit) (port) &= ~(1<<(bit))

void DHT_WakeUp(void);
int DHT_Response(void);
void DHT_Decode_Data(int (*array)[8]);
int ConvertToDecimal(int (*array)[8], int byte);

#endif /* DHT11_MASTER_H_ */