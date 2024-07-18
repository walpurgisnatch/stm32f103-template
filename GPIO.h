#ifndef _GPIO
#define _GPIO

#include "stm32f1xx.h"

#define OUTPUT_MODE ((uint32_t) 0x01)
#define INPUT_MODE  ((uint32_t) 0x02)

// INPUT MODES
#define INPUT_ANALOG            ((uint32_t) 0x00)
#define INPUT_FLOATING          ((uint32_t) 0x01)
#define INPUT_PU_PD             ((uint32_t) 0x02)

// OUTPUT
#define OUTPUT_GEN_PURPOSE      ((uint32_t) 0x00)
#define OUTPUT_OD               ((uint32_t) 0x01)
#define OUTPUT_ALT_FUNCTION     ((uint32_t) 0x02)
#define OUTPUT_ALT_FUNCTION_OD  ((uint32_t) 0x03)

// PIN Speed
#define SPEED_2MHZ              ((uint32_t) 0x02)
#define SPEED_10MHZ             ((uint32_t) 0x01)
#define SPEED_50MHZ             ((uint32_t) 0x03)

// clock enabling
#define GPIO_ALT_FUNC_CLOCK_ENABLE  (RCC->APB2ENR |= (1<<0))
#define GPIOA_CLOCK_ENABLE          (RCC->APB2ENR |= (1<<2))
#define GPIOB_CLOCK_ENABLE          (RCC->APB2ENR |= (1<<3))
#define GPIOC_CLOCK_ENABLE          (RCC->APB2ENR |= (1<<4))
#define GPIOD_CLOCK_ENABLE          (RCC->APB2ENR |= (1<<5))

#define CNF_POS_BIT1                (PINPOS[pin] + 2)
#define CNF_POS_BIT2                (PINPOS[pin] + 3)

typedef struct {
    GPIO_TypeDef *port;
    uint32_t pin;
    uint32_t mode;
    uint32_t mode_type;
    uint32_t pull;
    uint32_t speed;
    uint32_t alt_func;
} GPIO_TYPE;

void config_pin (GPIO_TypeDef *port, uint32_t pin, uint32_t mode_type);
void config_pin_speed (GPIO_TypeDef *port, uint32_t pin, uint32_t speed, uint32_t mode);

void gpio_init (GPIO_TYPE gpio);
void gpio_write (GPIO_TypeDef *port, uint32_t pin, uint8_t state);
void gpio_toggle (GPIO_TypeDef *port, uint32_t pin);

#endif
