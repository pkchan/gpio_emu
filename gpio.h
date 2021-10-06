#ifndef __GPIO_H_
#define __GPIO_H_

#include <stdint.h>

#define GPIO_PIN_MIN    0   /**< First emulated pin: keyboard 0 */
#define GPIO_PIN_MAX    9   /**< Last emulated pin: keyboard 9 */

/** Prototype of GPIO event handler */
typedef void (*gpio_cb_t)(uint8_t pin, uint8_t val);

/** Function for initializing GPIO emulator */
void gpio_init(gpio_cb_t fn);

/** Function for un-initializing GPIO emulator */
void gpio_cleanup(void);

/** Function for getting GPIO */
uint8_t gpio_get(uint8_t pin);

/** Function for setting GPIO */
void gpio_set(uint8_t pin);

/** Function for clearing GPIO */
void gpio_clear(uint8_t pin);

#endif // __GPIO_H_

