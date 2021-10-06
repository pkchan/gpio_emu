#include "gpio.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>

struct termios term_attr_bak;   /**< Backup of old terminal attribtes */
static pthread_t thread_id;     /**< Thread ID of GPIO interrupt emulator */
static volatile uint16_t reg;   /**< Emulated GPIO register */
static gpio_cb_t cb;            /**< Callback function */

/** Function for displaing GPIO */
static void disp(void) {
    printf("reg=");
    for (int i = GPIO_PIN_MAX; i >= GPIO_PIN_MIN; i--) {
        printf("%d", gpio_get(i));
    }
    printf("\r\n");
}

/** Function for GPIO interrupt emulation */
void *emu(void *vargp)
{
    char c;
    do {
        c = getchar();
        if (c >= GPIO_PIN_MIN + 0x30 && c <= GPIO_PIN_MAX + 0x30) {
            uint8_t i = c - 0x30;

            /* Toggle GPIO and callback */
            reg ^= 1 << i;
            if (cb) {
                cb(i, gpio_get(i));
            }
        }
    } while (c != 0x1b);        // Escape
    return NULL;
}

void gpio_init(gpio_cb_t fn) {
    /* Initialize register and save callback function */
    reg = 0;
    cb = fn;

    /* Configure terminal attribute: getchar() doesn't need newline anymore */
    struct termios newattr;
    tcgetattr(STDIN_FILENO, &term_attr_bak);
    newattr = term_attr_bak;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);

    /* Create a thread for GPIO emulator */
    pthread_create(&thread_id, NULL, emu, NULL);
}

void gpio_cleanup(void) {
    /* End thread: will block until Esc is received in emu() */
    pthread_join(thread_id, NULL);

    /* Restore terminal attribute */
    tcsetattr(STDIN_FILENO, TCSANOW, &term_attr_bak);
}

uint8_t gpio_get(uint8_t pin) {
    if (pin > GPIO_PIN_MAX) {
        return 0xFF;
    }
    return (reg >> pin) & 1;
}

void gpio_set(uint8_t pin) {
    if (pin > GPIO_PIN_MAX) {
        return;
    }

    uint16_t r = reg;
    reg |= 1 << pin;

    /* Display */
    if (reg != r) {
        disp();
    }
}

void gpio_clear(uint8_t pin) {
    if (pin > GPIO_PIN_MAX) {
        return;
    }

    uint16_t r = reg;
    reg &= ~(1 << pin);

    /* Display */
    if (reg != r) {
        disp();
    }
}

