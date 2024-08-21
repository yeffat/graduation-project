
#ifndef STD_TYPES_H 
#define STD_TYPES_H

typedef unsigned char 		 		uint8_t;
typedef signed char 		 		sint8_t;
typedef unsigned short int  		uint16_t;
typedef unsigned long int 	 		uint32_t;
typedef unsigned long long int 		uint64_t;
typedef signed short int 	 		sint16_t;
typedef signed long int 	 		sint32_t;
typedef signed long long int 		sint64_t;
typedef float 				 		float32_t;
typedef double 						float64_t;
typedef long double 				float128_t;// may be float80_t based on the compiler 

#define ERROR_NOK (uint8_t)1
#define ERROR_OK  (uint8_t)0

#define UNSIGNED_MIN 0

/* Macro for NULL */
#define NULL ((void*)0)
#endif

