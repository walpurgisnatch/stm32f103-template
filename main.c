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
    // enable GPIOC port
    RCC->APB2ENR |= (1<<4);
    
    // --- GPIO setup ----
    GPIOC->CRH |=  (1<<21);
    GPIOC->CRH &= ~(1<<20);
    GPIOC->CRH &= ~(1<<23);
    GPIOC->CRH &= ~(1<<22);

    // main loop
    for(;;) {
        GPIOC->BSRR = (1<<13);
        delay(250);
        GPIOC->BSRR = (1<<29);
        delay(250);
    }
}
