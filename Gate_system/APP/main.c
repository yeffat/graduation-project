#include "../LIB/STD_TYPES.h"
#include "../LIB/DELAY/DELAY_interface.h"

#include "../MCAL/GIE/GIE_int.h"

#include "../HAL/LCD/LCD_interface.h"
#include "../HAL/Servo/SERVO_interface.h"
#include "../HAL/IR_sensor/IR_interface.h"
#include "../HAL/Button/Button_interface.h"
#include "../HAL/LED/LED.h"
#include "../HAL/keypad/KEYPAD.h"

#include "../Communication/Maset_Slave_COMM/slave_config.h"
#include "../Communication/Maset_Slave_COMM/slave_interface.h"

// Global variables
#define NACK	0x21
uint8_t ACK;
uint8_t TX_Data[SPI_BUFFER_SIZE];
uint8_t RX_Data[SPI_BUFFER_SIZE];

// Global flags for ISR
volatile uint8_t carDetectedFlag;
volatile uint8_t buttonPressedFlag;

// Function prototypes
void carDetectedISR(void);
void buttonPressedISR(void);
void handleCarDetection(void);
void handleButtonPress(void);
void processReceivedData(void);
void systemInit(void);

void main(void) {
    uint16_t time_out = 0;
    systemInit();

    while (1) {

        Slave_ReceiveByte(&ACK);
        if (ACK == 0x20){
            Slave_Receive_Data(RX_Data);
			if (RX_Data[0] != 0xff)
			{
			processReceivedData();
			}
			ACK=0;
        }

        if (carDetectedFlag || buttonPressedFlag) {
        	if (carDetectedFlag){
                carDetectedFlag = 0;
                handleCarDetection();
        	}
        	else{
                buttonPressedFlag = 0;
                handleButtonPress();
        	}

        }
        if (time_out == 20000)
            GIE_voidEnable();

        time_out++;
    }
}

void systemInit(void) {
	/*
	 * Makes absolutely no sense but some how the compiler wouldn't work fine without it
	 */


    Slave_Comm_Init();
    LCD_VidInit();
    LED_Init();
    keyPad_init();
    IR_Init();
    Button_Init();
    SERVO_u8Init();

    LED_On(LED_GATE_CLOSED);
    SERVO_u8SetServoAngle(0);

    IR_SetCallback(carDetectedISR);
    Button_SetCallback(buttonPressedISR);
    RX_Data[0] = 0xff;
    GIE_voidEnable();

}

void processReceivedData(void) {
        switch (RX_Data[0]) {
            case EMPTY_SLOT_FOUND:
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"Empty Slot ID: ", 0, 0);
                LCD_vidDisplayINT(RX_Data[1]);
                ACK = 0xfc;
                RX_Data[0] = 0xff;
                break;

            case REQUESTED_EMPTY_SLOT_READY:
                LCD_VidCLEAR();
                SERVO_u8SetServoAngle(90);
                LED_On(LED_GATE_OPEN);
                LED_Off(LED_GATE_CLOSED);
                LCD_U8WriteString((uint8_t*)"Slot Ready!", 0, 0);
                LCD_U8WriteString((uint8_t*)"ID: ", 0, 1);
                LCD_vidDisplayINT(RX_Data[1]);
                RX_Data[0] = 0xff;
                ACK = 0xfc;

                break;

            case CLOSE_GATE:
                SERVO_u8SetServoAngle(0);
                LED_Off(LED_GATE_OPEN);
                LED_On(LED_GATE_CLOSED);
                LCD_VidCLEAR();
                RX_Data[0] = 0xff;
                ACK = 0xfc;
                GIE_voidEnable();
                break;

            case REQUESTED_CAR_READY:
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"Car is Ready", 0, 0);
                SERVO_u8SetServoAngle(90);
                LED_On(LED_GATE_OPEN);
                LED_Off(LED_GATE_CLOSED);
                delay_milliseconds(3000);
                SERVO_u8SetServoAngle(0);
                LED_Off(LED_GATE_OPEN);
                LED_On(LED_GATE_CLOSED);
                LCD_VidCLEAR();
                RX_Data[0] = 0xff;
                ACK = 0xfc;
                GIE_voidEnable();
                break;

            case NO_EMPTY_SLOT:
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"No Empty Slot", 0, 0);

                RX_Data[0] = 0xff;
                ACK = 0xfc;
                GIE_voidEnable();
                break;

            case WRONG_SLOT_ID:
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"Wrong Slot ID!", 0, 0);
                delay_milliseconds(1000);
                LCD_VidCLEAR();

                RX_Data[0] = 0xff;
                ACK = 0xfc;
                GIE_voidEnable();
                break;
            case UNKNOWN_REQUEST:
            	LCD_VidCLEAR();
            	LCD_U8WriteString((uint8_t*)"UNKNOWN REQUEST", 0, 0);
            	delay_milliseconds(1000);
				LCD_VidCLEAR();
				RX_Data[0] = 0xff;
				ACK = 0xfc;
				GIE_voidEnable();
            	break;
            default:
                RX_Data[0] = 0xff;
                ACK = 0xfc;
                GIE_voidEnable();
                break;
        }

}

void handleCarDetection(void) {
    GIE_voidDisable();
    LCD_VidCLEAR();
    LCD_U8WriteString((uint8_t*)"Welcome To Smart Parking system", 0, 0);
    delay_milliseconds(999);
    TX_Data[0] = REQUEST_PARK_CAR;
    Slave_Send_Request(TX_Data);
}

void handleButtonPress(void) {
    GIE_voidDisable();
    uint8_t int_time_out = 0;
    LCD_VidCLEAR();
    LCD_U8WriteString((uint8_t*)"Welcome To Smart Parking system", 0, 0);
    uint8_t action = 0xFF;
    uint16_t timeout =30;
    delay_milliseconds(999);

    while (int_time_out <= 2) {
        LCD_VidCLEAR();

        if (int_time_out >= 2) {
            GIE_voidEnable();
            LCD_VidCLEAR();
            return;
        }
        LCD_U8WriteString((uint8_t*)"1:Park Car", 0, 0);
        LCD_U8WriteString((uint8_t*)"2:Retrieve Car", 0, 1);
        timeout = 30;
        while (timeout > 0) {
            action = KeyPad_get_pressed_key();
            if (action != 0xFF) {
                break;
            }
            delay_milliseconds(1);
            timeout--;
        }

        if (action == 1 || action == 2) {
            if (action == 1) {
                TX_Data[0] = REQUEST_PARK_CAR;
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"Processing", 0, 0);
                Slave_Send_Request(TX_Data);
                break;
            } else if (action == 2) {
            	delay_milliseconds(100);
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"Enter Slot ID:", 0, 0);
                TX_Data[0] = REQUEST_RETRIEVE_CAR;
                uint8_t slotIDEntered = 0xff;
                timeout = 30;
                while (timeout > 0) {
                    slotIDEntered = KeyPad_get_pressed_key();
                    if (slotIDEntered != 0xFF) {
                        break;
                    }
                    delay_milliseconds(1);
                    timeout--;
                }
                TX_Data[1] = slotIDEntered;
                LCD_VidCLEAR();
                LCD_U8WriteString((uint8_t*)"Processing", 0, 0);
                Slave_Send_Request(TX_Data);
                break;
            }
        } else {
            LCD_VidCLEAR();
            LCD_U8WriteString((uint8_t*)"Invalid choice", 0, 0);
            delay_milliseconds(800);
        }
        int_time_out++;
    }
}

void carDetectedISR(void) {
    carDetectedFlag = 1;
}

void buttonPressedISR(void) {
    buttonPressedFlag = 1;
}
