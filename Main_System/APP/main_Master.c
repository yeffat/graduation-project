#include "../LIB/STD_TYPES.h"
#include "../LIB/DELAY/DELAY_interface.h"

#include "../Communication/Maset_Slave_COMM/Master_interface.h"
#include "../Communication/Maset_Slave_COMM/Master_config.h"

#include "../HAL/EEPROM/eeprom.h"
#include "../HAL/Stepper_Motor/STPM_interface.h"
#include "../HAL/IR_HW-201/IR_interface.h"
#include "../HAL/LED/LED.h"
#include "../HAL/SEV_SEG/SEV_SEG.h"

#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/DIO/DIO_reg.h"
// EEPROM addresses
#define NUM_EMPTY_SLOTS_ADDR	0x00
#define SLOT_STATUS_ADDR 		0x01
#define CURRENT_SLOT_ADDR 		0x07
#define EEPROM_INIT_FLAG_ADDR 	0xFF
#define EEPROM_INIT_FLAG 		0xA5
#define ACK	0x20
#define TOTAL_SLOTS 6
#define STEPS_PER_SLOT 1000

// Function prototypes
void System_Init(void);

void Update_EEPROM(void);
void Load_EEPROM(void);
void Clear_EEPROM(void);
void Initialize_EEPROM_If_Needed(void);

uint8_t Find_Nearest_Empty_Slot(uint8_t currentSlot);
void Assign_User_To_Slot(uint8_t slot_id);
void Retrieve_Car_From_Slot(uint8_t slot_id);

void IR_Sensor_ISR(void);
void Handle_Slave_Request_ISR(void);

void Process_Slave_Request(void);

// Global variables
uint8_t num_empty_slots;
uint8_t slot_status[TOTAL_SLOTS];
uint8_t currentSlot;
uint8_t TX_Data[SPI_BUFFER_SIZE];
uint8_t RX_Data[SPI_BUFFER_SIZE];

volatile uint8_t car_parked_correctly;
volatile uint8_t request_pending;

void main(void) {
    System_Init();

    //Clear_EEPROM();
    while(1) {

        if (request_pending) {

           Process_Slave_Request();
        }
    }
}

void System_Init(void) {

    LED_Init();
    SEV_SEG_VidInit();
    Master_Comm_Init();
    eeprom_init();
    Initialize_EEPROM_If_Needed();

    Load_EEPROM();
    IR_Init();
    StepperMotor_Init();

    SEV_SEG_VidSetNumber(currentSlot);
    SetSlaveReadyCallBack(Handle_Slave_Request_ISR);
    IR_SetCallback(IR_Sensor_ISR);
    IR_Disable();
    GIE_voidEnable();

}

uint8_t Find_Nearest_Empty_Slot(uint8_t currentSlot) {
    uint8_t nearest_empty_slot = 0xFF;
    uint16_t minimum_steps = 0xFFFF;

    for (uint8_t i = 0; i < TOTAL_SLOTS; i++) {
        if (slot_status[i] == 0) {
            // Calculate CW and CCW steps
            uint16_t steps_CW = (i >= currentSlot) ? (i - currentSlot) * STEPS_PER_SLOT : (TOTAL_SLOTS - currentSlot + i) * STEPS_PER_SLOT;
            uint16_t steps_CCW = (i <= currentSlot) ? (currentSlot - i) * STEPS_PER_SLOT : (currentSlot + TOTAL_SLOTS - i) * STEPS_PER_SLOT;

            // Choose the minimum steps
            uint16_t steps_needed = (steps_CW < steps_CCW) ? steps_CW : steps_CCW;

            // Update the nearest empty slot if this one is closer
            if (steps_needed < minimum_steps) {
                minimum_steps = steps_needed;
                nearest_empty_slot = i;
            }
        }
    }
    return nearest_empty_slot;
}


void Assign_User_To_Slot(uint8_t slot_id) {
    if (slot_id < TOTAL_SLOTS) {
        StepperMotor_MoveToSlot(&currentSlot, slot_id);
        slot_status[slot_id] = 1;
        num_empty_slots--;
        Update_EEPROM();
        SEV_SEG_VidSetNumber(currentSlot);
    }
}

void Retrieve_Car_From_Slot(uint8_t slot_id) {
    if (slot_id < TOTAL_SLOTS && slot_status[slot_id] == 1) {

        StepperMotor_MoveToSlot(&currentSlot, slot_id);
        slot_status[slot_id] = 0;
        num_empty_slots++;
        Update_EEPROM();
        SEV_SEG_VidSetNumber(currentSlot);
    }
}

void Update_EEPROM(void) {
    eeprom_write_byte(NUM_EMPTY_SLOTS_ADDR, num_empty_slots);
    eeprom_write_block(SLOT_STATUS_ADDR, slot_status, TOTAL_SLOTS);
    eeprom_write_byte(CURRENT_SLOT_ADDR, currentSlot);
}

void Load_EEPROM(void) {
    num_empty_slots = eeprom_read_byte(NUM_EMPTY_SLOTS_ADDR);
    eeprom_read_block(SLOT_STATUS_ADDR, slot_status, TOTAL_SLOTS);
    currentSlot = eeprom_read_byte(CURRENT_SLOT_ADDR);
}
void Clear_EEPROM(void) {
    // Set all the slot statuses to 0 (empty)
    for (uint8_t i = 0; i < TOTAL_SLOTS; i++) {
        eeprom_write_byte(SLOT_STATUS_ADDR + i, 0);
    }

    // Set the number of empty slots to the total number of slots
    eeprom_write_byte(NUM_EMPTY_SLOTS_ADDR, TOTAL_SLOTS);

    // Set the current slot to 0
    eeprom_write_byte(CURRENT_SLOT_ADDR, 0);

}

void Initialize_EEPROM_If_Needed(void) {
    if (eeprom_read_byte(EEPROM_INIT_FLAG_ADDR) != EEPROM_INIT_FLAG) {
        eeprom_write_byte(NUM_EMPTY_SLOTS_ADDR, TOTAL_SLOTS);
        for (uint8_t i = 0; i < TOTAL_SLOTS; i++) {
            eeprom_write_byte(SLOT_STATUS_ADDR + i, 0);
        }
        eeprom_write_byte(CURRENT_SLOT_ADDR, 0);
        eeprom_write_byte(EEPROM_INIT_FLAG_ADDR, EEPROM_INIT_FLAG);
    }
}

void IR_Sensor_ISR(void) {
    car_parked_correctly = 1;
    LED_On(LED_CAR_PARKED);
}

void Handle_Slave_Request_ISR() {

	Master_Receive_Data(RX_Data);
    request_pending = 1;
}

void Process_Slave_Request(void) {
	LED_Off(LED_CAR_PARKED);
    uint16_t timeout = 5000;
    uint8_t request_type = RX_Data[0];
    request_pending = 0;

    switch (request_type) {
        case REQUEST_PARK_CAR: {

            car_parked_correctly = 0;
            uint8_t nearest_empty_slot = Find_Nearest_Empty_Slot(currentSlot);

            if (nearest_empty_slot != 0xFF) {
                TX_Data[0] = EMPTY_SLOT_FOUND;
                TX_Data[1] = nearest_empty_slot;
                //ACK

                Master_Send_Data(TX_Data);

                delay_milliseconds(500);
                LED_On(LED_STEPPER_ON);
                Assign_User_To_Slot(nearest_empty_slot);
                LED_Off(LED_STEPPER_ON);

                TX_Data[0] = REQUESTED_EMPTY_SLOT_READY;

                Master_Send_Data(TX_Data);

                IR_Enable();
                delay_milliseconds(5);
                while (!car_parked_correctly && timeout > 0){
                	 timeout--;
                	 delay_milliseconds(1);
                }
                TX_Data[0] = CLOSE_GATE;
                Master_Send_Data(TX_Data);

                IR_Disable();

                delay_milliseconds(1);


            } else {
                TX_Data[0] = NO_EMPTY_SLOT;
                Master_Send_Data(TX_Data);

            }
            break;
        }
        case REQUEST_RETRIEVE_CAR: {

            uint8_t slot_id = RX_Data[1];
            if (slot_id < TOTAL_SLOTS && slot_status[slot_id] == 1) {

            	LED_On(LED_STEPPER_ON);
                Retrieve_Car_From_Slot(slot_id);
                TX_Data[0] = REQUESTED_CAR_READY;
                TX_Data[1] = RX_Data[1];
                Master_Send_Data(TX_Data);
                LED_Off(LED_STEPPER_ON);

            } else {
                TX_Data[0] = WRONG_SLOT_ID;
                Master_Send_Data(TX_Data);
            }
            break;
        }
        default: {
            TX_Data[0] = UNKNOWN_REQUEST;
            Master_Send_Data(TX_Data);
            break;
        }
    }
}
