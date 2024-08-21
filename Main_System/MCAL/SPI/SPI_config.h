
/*Preprocessor Guard*/
#ifndef SPI_CONFIG_H 
#define SPI_CONFIG_H 

/*
  Macro to specify the role of the SPI node
  Ranges: SPI_u8_MASTER
		  SPI_u8_SLAVE
*/
#define  SPI_u8_SELECTROLE      SPI_u8_MASTER

/*
  Macro to specify state of the Serial Transfer Complete interrupt
  Ranges: SPI_u8_ENABLE
		  SPI_u8_DISABLE
*/
#define SPI_u8_INT_STATE		SPI_u8_DISABLE

/*
  Macro to specify order by which the byte will be sent
  Ranges: SPI_u8_LSB
		  SPI_u8_MSB
*/
#define SPI_u8_DATA_ORDER       SPI_u8_MSB

/*
  Macro to specify the clock polarity
  Ranges: SPI_u8_RISINGEDGE
		  SPI_u8_FALLINGEDGE
*/
#define SPI_u8_CLKPOL          SPI_u8_RISINGEDGE

/*
  Macro to specify the clock phase
  Ranges: SPI_u8_SAMPLE
		  SPI_u8_SETUP
*/
#define SPI_u8_CLKPHASE          SPI_u8_SAMPLE

/*
  Macro to specify the SPI clock rate
  Ranges: SPI_OVER_4
		  SPI_OVER_16
		  SPI_OVER_64
		  SPI_OVER_128
		  SPI_OVER_2_HSPD
		  SPI_OVER_8_HSPD
		  SPI_OVER_32_HSPD
		  SPI_OVER_64_HSPD
*/
#define  SPI_u8_CLKRATE          SPI_OVER_16

#if (SPI_u8_CLKRATE == SPI_OVER_4)
#define SPI_u8_SPRBITS            (uint8_t)0
#elif (SPI_u8_CLKRATE == SPI_OVER_16)
#define SPI_u8_SPRBITS            (uint8_t)1
#elif (SPI_u8_CLKRATE == SPI_OVER_64)
#define SPI_u8_SPRBITS            (uint8_t)2
#elif (SPI_u8_CLKRATE == SPI_OVER_128)
#define SPI_u8_SPRBITS            (uint8_t)3
#elif (SPI_u8_CLKRATE == SPI_OVER_2_HSPD)
#define SPI_u8_SPRBITS            (uint8_t)0
#elif (SPI_u8_CLKRATE == SPI_OVER_8_HSPD)
#define SPI_u8_SPRBITS            (uint8_t)1
#elif (SPI_u8_CLKRATE == SPI_OVER_32_HSPD)
#define SPI_u8_SPRBITS            (uint8_t)2
#elif (SPI_u8_CLKRATE == SPI_OVER_64_HSPD)
#define SPI_u8_SPRBITS            (uint8_t)3
#endif

/* Macro to define the timeout which determines the fault time in the SPI upon transmitting or receiving */
#define SPI_u16_FAULT_TIMEOUT      (uint16_t)50000
#endif /* SPI_CONFIG_H */

