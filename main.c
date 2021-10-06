#include <stdio.h>
#include "gpio.h"

/** GPIO event handler */
void gpio_handler(uint8_t pin, uint8_t val) {
    /* Sets opposite value to pin #(9-pin) */
    if (val) {
        gpio_clear(GPIO_PIN_MAX - pin);
    } else {
        gpio_set(GPIO_PIN_MAX - pin);
    }
}

/** Entry point */
void main(void) {
    gpio_init(gpio_handler);
    gpio_set(0);
    gpio_set(1);
    gpio_set(2);
    gpio_set(3);
    gpio_set(4);
    gpio_cleanup(); // This function blocks until user presses Esc
}
