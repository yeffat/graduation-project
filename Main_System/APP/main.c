#include "../LIB/STD_TYPES.h"
#include "../LIB/DELAY/DELAY_interface.h"

#include "../Communication/Maset_Slave_COMM/Master_interface.h"
#include "../Communication/Maset_Slave_COMM/Master_config.h"
//#include "../Communication/WIFI_Server/wifi_service.h"

#include "../HAL/EEPROM/eeprom.h"
#include "../HAL/Stepper_Motor/STPM_interface.h"
#include "../HAL/IR_HW-201/IR_interface.h"
#include "../HAL/LED/LED.h"
#include "../HAL/SEV_SEG/SEV_SEG.h"
#include "..\MCAL\DIO\DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"

// EEPROM addresses
#define NUM_EMPTY_SLOTS_ADDR	0x00
#define SLOT_STATUS_ADDR		0x01
#define CURRENT_SLOT_ADDR		0x07
#define EEPROM_INIT_FLAG_ADDR	0xFF
#define EEPROM_INIT_FLAG		0xA5

#define TOTAL_SLOTS 6
#define STEPS_PER_SLOT 100

// Function prototypes
void System_Init(void);
void Manage_Parking(void);
void Update_EEPROM(void);
void Load_EEPROM(void);
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
uint8_t currentSlot; // Variable to keep track of the current slot

volatile uint8_t car_parked_correctly = 0; // Flag to indicate if the car is parked correctly
volatile uint8_t request_pending = 0; // Flag to indicate if a request is pending

uint8_t TX_Data[SPI_BUFFER_SIZE] = {0};
uint8_t RX_Data[SPI_BUFFER_SIZE] = {0};

void main(void){
    // Initialize the system
	uint8_t test;
	GIE_voidEnable();
	LED_Init();
	Master_Comm_Init();
	SetSlaveReadyCallBack(Handle_Slave_Request_ISR);
	delay_milliseconds(10);



    while (1) {
        // Manage the rotary parking system
        //Manage_Parking();

        // Process any pending requests
//        if (request_pending) {
//            Process_Slave_Request();
//        }

        // Send empty slots information to the server
        // Send_Empty_Slots_To_Server();
    }
}

void System_Init(void) {
    // Initialize peripherals and modules
	LED_Init();
	SEV_SEG_VidInit();
	Master_Comm_Init();

    eeprom_init();
	Initialize_EEPROM_If_Needed();
    Load_EEPROM();
    IR_Init();
    StepperMotor_Init();

//    // Initialize WiFi module
//    // WIFI_Init();
//    // Enable global interrupts

    GIE_voidEnable();

    SEV_SEG_VidSetNumber(currentSlot);

    // Display the initial slot
    // Set the callback for when the slave is ready
    SetSlaveReadyCallBack(Handle_Slave_Request_ISR);
     //Set the callback for the IR sensor interrupt
    IR_SetCallback(IR_Sensor_ISR);



}

//void Manage_Parking(void) {
//}



uint8_t Find_Nearest_Empty_Slot(uint8_t currentSlot) {
    uint8_t nearest_empty_slot = 0xFF;
    uint16_t minimum_steps = 0xFFFF;

    for (uint8_t i = 0; i < TOTAL_SLOTS; i++) {
        if (slot_status[i] == 0) {
            uint16_t steps_needed = (uint16_t)(i - currentSlot) * STEPS_PER_SLOT;
            if (steps_needed < 0) {
                steps_needed = -steps_needed;
            }
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
        // Move the car to the designated slot
        StepperMotor_MoveToSlot(currentSlot, slot_id);

        // Update slot status
        slot_status[slot_id] = 1;
        num_empty_slots--;

        // Update current slot
        currentSlot = slot_id;
        Update_EEPROM();
        eeprom_write_byte(CURRENT_SLOT_ADDR, currentSlot);

        // Update the seven-segment display
        SEV_SEG_VidSetNumber(currentSlot);

        // Command to open gate
        // Master_Send_Command(OPEN_GATE);
    }
}

void Retrieve_Car_From_Slot(uint8_t slot_id) {
    if (slot_id < TOTAL_SLOTS && slot_status[slot_id] == 1) {
        // Move the car to the gate
        StepperMotor_MoveToSlot(currentSlot, slot_id);

        // Update slot status
        slot_status[slot_id] = 0;
        num_empty_slots++;
        Update_EEPROM();

        // Update current slot
        currentSlot = slot_id;
        eeprom_write_byte(CURRENT_SLOT_ADDR, currentSlot);

        // Update the seven-segment display
        SEV_SEG_VidSetNumber(currentSlot);

        // Command to open gate
        // Master_Send_Command(OPEN_GATE);
    }
}

void Update_EEPROM(void) {
    // Update EEPROM with current parking information
    eeprom_write_byte(NUM_EMPTY_SLOTS_ADDR, num_empty_slots);
    eeprom_write_block(SLOT_STATUS_ADDR, slot_status, TOTAL_SLOTS);
    eeprom_write_byte(CURRENT_SLOT_ADDR, currentSlot);
}

void Load_EEPROM(void) {
    // Load parking information from EEPROM
    num_empty_slots = eeprom_read_byte(NUM_EMPTY_SLOTS_ADDR);
    eeprom_read_block(SLOT_STATUS_ADDR, slot_status, TOTAL_SLOTS);
    currentSlot = eeprom_read_byte(CURRENT_SLOT_ADDR);
}

void Initialize_EEPROM_If_Needed(void) {
    // Check if EEPROM is already initialized
    if (eeprom_read_byte(EEPROM_INIT_FLAG_ADDR) != EEPROM_INIT_FLAG) {
        // EEPROM is not initialized, set default values

        eeprom_write_byte(NUM_EMPTY_SLOTS_ADDR, TOTAL_SLOTS);
        //delay_milliseconds(5);
        for (uint8_t i = 0; i < TOTAL_SLOTS; i++) {
            eeprom_write_byte(SLOT_STATUS_ADDR + i, 0);

        }
        eeprom_write_byte(CURRENT_SLOT_ADDR, 0);

        // Set the EEPROM initialization flag
        eeprom_write_byte(EEPROM_INIT_FLAG_ADDR, EEPROM_INIT_FLAG);

    }
}

void IR_Sensor_ISR(void) {
    // This ISR is called when the IR sensor detects that the car is correctly parked
    car_parked_correctly = 1;
    LED_On(LED_CAR_PARKED);

}

void Handle_Slave_Request_ISR() {
    request_pending = 1; // Set the flag indicating a request is pending
    uint8_t test;
    LED_On(LED_CAR_PARKED);
	Master_Send_Command(0x01, &test);
if (test == 0x02){
	LED_On(LED_STEPPER_ON);
}
}

//void Process_Slave_Request(void) {
//
//    volatile uint8_t request_type; // Store the request type
//    uint8_t received_data[2];
//    Master_Receive_Data(RX_Data);
//    request_type = RX_Data[0];  // Assuming request type is the first byte
//    request_pending = 0; // Clear the flag indicating request is being processed
//
//    switch (request_type) {
//        case REQUEST_PARK_CAR: {
//        	//IR_Disable();
//            car_parked_correctly = 0; // Reset the flag
//
//            uint8_t nearest_empty_slot = Find_Nearest_Empty_Slot(currentSlot);
//            if (nearest_empty_slot != 0xFF) {
//                // Notify the slave that an empty slot is found
//            	TX_Data[0]=EMPTY_SLOT_FOUND;
//            	TX_Data[1]=nearest_empty_slot;
//                Master_Send_Data(TX_Data);
//                     while (!car_parked_correctly) {
//                            // Optionally, add a timeout or error handling here
//                          }
//                Assign_User_To_Slot(nearest_empty_slot);
//                // Notify the slave that the requested empty slot is ready
//                Master_Send_Command(REQUESTED_EMPTY_SLOT_READY);
//
//            } else {
//                // No empty slots available, notify the slave
//                Master_Send_Command(NO_EMPTY_SLOT);
//            }
//
//            break;
//        }
//        case REQUEST_RETRIEVE_CAR: {
//            uint8_t slot_id = received_data[1]; // Assume slot_id is the second byte in the received data
//            if (slot_id < TOTAL_SLOTS && slot_status[slot_id] == 1) {
//                Retrieve_Car_From_Slot(slot_id);
//                // Notify the slave that the requested car is ready
//                Master_Send_Command(REQUESTED_CAR_READY);
//            } else {
//                // Wrong slot ID or the slot is empty, notify the slave
//                Master_Send_Command(WRONG_SLOT_ID);
//            }
//
//            break;
//        }
//        default:
//            // Handle unknown request
//            Master_Send_Command(UNKNOWN_REQUEST);
//
//            break;
//    }
//}

// void Send_Empty_Slots_To_Server(void) {
//     WIFI_SendEmptySlots(num_empty_slots);
// }
