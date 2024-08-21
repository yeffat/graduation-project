
/*Preprocessor Guard*/
#ifndef I2C_PRIV_H 
#define I2C_PRIV_H 
/****************************************************************/
/* Defining I2C regisiters                                      */
/****************************************************************/
#define TWBR			(*(volatile uint8_t*)0x20)
/*Defining the bits of I2C_TWBR register*/
#define TWBR0                 (uint8_t)0
#define TWBR1                 (uint8_t)1
#define TWBR2                 (uint8_t)2
#define TWBR3	              (uint8_t)3
#define TWBR4	              (uint8_t)4
#define TWBR5                 (uint8_t)5
#define TWBR6                 (uint8_t)6
#define TWBR7                 (uint8_t)7

#define TWCR			(*(volatile uint8_t*)0x56)
/*Defining the bits of I2C_TWCR register*/
#define TWIE                  (uint8_t)0
#define TWEN                  (uint8_t)2
#define TWWC                  (uint8_t)3
#define TWSTO                 (uint8_t)4
#define TWSTA                 (uint8_t)5
#define TWEA                  (uint8_t)6
#define TWINT                 (uint8_t)7

#define TWSR			(*(volatile uint8_t*)0x21)
/*Defining the bits of I2C_TWSR register*/
#define TWPS0                 (uint8_t)0
#define TWPS1                 (uint8_t)1
#define TWS3                  (uint8_t)3
#define TWS4                  (uint8_t)4
#define TWS5                  (uint8_t)5
#define TWS6                  (uint8_t)6
#define TWS7                  (uint8_t)7

#define TWDR			(*(volatile uint8_t*)0x23)
/*Defining the bits of I2C_TWDR register*/
#define TWD0                  (uint8_t)0
#define TWD1                  (uint8_t)1
#define TWD2                  (uint8_t)2
#define TWD3	              (uint8_t)3
#define TWD4	              (uint8_t)4
#define TWD5                  (uint8_t)5
#define TWD6                  (uint8_t)6
#define TWD7                  (uint8_t)7

#define TWAR			(*(volatile uint8_t*)0x22)
/*Defining the bits of I2C_TWAR register*/
#define TWGCE                  (uint8_t)0

#endif /* I2C_PRIV_H */ 
