#include "xparameters.h"
#include "xgpiops.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xil_io.h"
#include "platform.h"
#include "sleep.h"

#define BUTTON_PIN 0 // Adjust this to the correct pin number for your button

int main()
{
    XGpioPs_Config *XGPIO_Config;
    XGpioPs my_Gpio;
    int Status;
    int buttonState;

    // Initialize platform
    init_platform();

    // Look up the configuration for the GPIO device
    XGPIO_Config = XGpioPs_LookupConfig(XPAR_PS7_GPIO_0_DEVICE_ID);
    if (XGPIO_Config == NULL) {
        xil_printf("XGpioPs_LookupConfig failed\r\n");
        return XST_FAILURE;
    }

    // Initialize the GPIO driver
    Status = XGpioPs_CfgInitialize(&my_Gpio, XGPIO_Config, XGPIO_Config->BaseAddr);
    if (Status != XST_SUCCESS) {
        xil_printf("XGpioPs_CfgInitialize failed\r\n");
        return XST_FAILURE;
    }

    // Set the direction of the pin to input (0)
    XGpioPs_SetDirectionPin(&my_Gpio, BUTTON_PIN, 0);

    // Enable the input pin
    XGpioPs_SetOutputEnablePin(&my_Gpio, BUTTON_PIN, 0);

    // Loop to continuously check the button state
    while (1) {
        buttonState = XGpioPs_ReadPin(&my_Gpio, BUTTON_PIN);

        if (buttonState == 1) {
            xil_printf("Button pressed\r\n");
        } else {
            xil_printf("Button not pressed\r\n");
        }

        // Add a small delay to avoid overwhelming the output
        usleep(100000);
    }

    // Cleanup platform
    cleanup_platform();

    return 0;
}
