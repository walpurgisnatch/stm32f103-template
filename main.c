#include "main.h"

void delay(int millis) {
    while (millis-- > 0) {
        volatile int x = 5971;
        while (x-- > 0) {
            __asm("nop");
        }
    }
}

int main() {
    GPIO_TYPE myGPIO;

    myGPIO.port = GPIOA;
    myGPIO.pin = 1;
    myGPIO.mode = OUTPUT_MODE;
    myGPIO.mode_type = OUTPUT_GEN_PURPOSE;
    myGPIO.speed = SPEED_2MHZ;

    gpio_init(myGPIO);
    
    for(;;) {
        gpio_toggle(GPIOA, 1);
        delay(250);
    }
}
