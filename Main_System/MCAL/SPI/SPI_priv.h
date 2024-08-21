

/*Preprocessor Guard*/
#ifndef SPI_PRIV_H 
#define SPI_PRIV_H 

/* Private macros to define the possible state of Serial Transfer Complete interrupt */
#define SPI_u8_ENABLE         (uint8_t)0
#define SPI_u8_DISABLE        (uint8_t)1

/* Private macros to define the possible order by which the byte will be sent */
#define SPI_u8_LSB            (uint8_t)0
#define SPI_u8_MSB            (uint8_t)1

/* Private macros to define the states of an SPI node (Master/Slave) */
#define SPI_u8_MASTER         (uint8_t)0
#define SPI_u8_SLAVE          (uint8_t)1

/* Private macros to define the clock polarity */
#define SPI_u8_RISINGEDGE     (uint8_t)0
#define SPI_u8_FALLINGEDGE    (uint8_t)1

/* Private macros to define the clock phase */
#define SPI_u8_SAMPLE         (uint8_t)0
#define SPI_u8_SETUP          (uint8_t)1


/* Private macros to define the SPI clock rate */
#define SPI_OVER_4         0UL
#define SPI_OVER_16        1UL
#define SPI_OVER_64        2UL
#define SPI_OVER_128       3UL
#define SPI_OVER_2_HSPD    4UL
#define SPI_OVER_8_HSPD    5UL
#define SPI_OVER_32_HSPD   6UL
#define SPI_OVER_64_HSPD   7UL

/****************************************************************/
/* Defining SPI regisiters                                     */
/****************************************************************/
#define SPI_SPCR			(*(volatile uint8_t*)0x2D)
/*Defining the bits of SPI_SPCR register*/
#define SPR0                 (uint8_t)0
#define SPR1                 (uint8_t)1
#define CPHA                 (uint8_t)2
#define CPOL	             (uint8_t)3
#define MSTR	             (uint8_t)4
#define DORD                 (uint8_t)5
#define SPE                  (uint8_t)6
#define SPIE                 (uint8_t)7

#define SPI_SPSR			(*(volatile uint8_t*)0x2E)
/*Defining the bits of SPI_SPSR register*/
#define SPI2X                 (uint8_t)0
#define SPIF                  (uint8_t)7

#define SPI_SPDR			(*(volatile uint8_t*)0x2F)

/************************************************************/
/*      ISRs of SPI interrupts                             */
/************************************************************/
/*The ISR of Serial Transfer Complete*/
void __vector_12 (void) __attribute__((signal));

#endif /* SPI_PRIV_H */ 
