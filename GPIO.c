#include "GPIO.h"
#include <stdint.h>


uint32_t PINPOS[16] = {
    (0x00),
    (0x04),
    (0x08),
    (0x0C),
    (0x10),
    (0x14),
    (0x18),
    (0x1C),
    (0x00),
    (0x04),
    (0x08),
    (0x0C),
    (0x10),
    (0x14),
    (0x18),
    (0x1C)
};

void config_pin(GPIO_TypeDef *port, uint32_t pin, uint32_t mode_type) {
    volatile uint32_t *current_port = pin >= 8 ? &port->CRH : &port->CRL;
    
    switch(mode_type) {
            
    case OUTPUT_GEN_PURPOSE | INPUT_ANALOG:
        *current_port &= ~((1<<CNF_POS_BIT1) | (1<<CNF_POS_BIT2));
        break;
            
    case OUTPUT_OD | INPUT_FLOATING:
        *current_port &= ~(1<<CNF_POS_BIT2);
        *current_port |= (1<<CNF_POS_BIT1);
        break;

    case OUTPUT_ALT_FUNCTION | INPUT_PU_PD:
        *current_port |= OUTPUT_ALT_FUNCTION<<CNF_POS_BIT1;
        break;

    case OUTPUT_ALT_FUNCTION_OD:
        *current_port |= OUTPUT_ALT_FUNCTION_OD<<CNF_POS_BIT1;
        break;
    }
}

void config_pin_speed(GPIO_TypeDef *port, uint32_t pin, uint32_t speed, uint32_t mode) {
    volatile uint32_t *current_port = pin >= 8 ? &port->CRH : &port->CRL;
    
    if(mode == INPUT_MODE)
        *current_port &= ~(1<<(PINPOS[pin]) | 1<<(PINPOS[pin] + 1));
    else
        *current_port |= (speed<<(PINPOS[pin]));
}

void gpio_init(GPIO_TYPE gpio) {
    if (gpio.port == GPIOA)
        GPIOA_CLOCK_ENABLE;
    if (gpio.port == GPIOB)
        GPIOB_CLOCK_ENABLE;
    if (gpio.port == GPIOC)
        GPIOC_CLOCK_ENABLE;
    if (gpio.port == GPIOD)
        GPIOD_CLOCK_ENABLE;
    
    config_pin(gpio.port, gpio.pin, gpio.mode_type);
    config_pin_speed(gpio.port, gpio.pin, gpio.speed, gpio.mode);
}

void gpio_write(GPIO_TypeDef *port, uint32_t pin, uint8_t state) {
    if(state) {
        port->BSRR = (1<<pin);
    } else {
        port->BSRR = (1<<(pin + 16));
    }
}
    
void gpio_toggle(GPIO_TypeDef *port, uint32_t pin) {
    port->ODR ^= (1<<pin);
}
