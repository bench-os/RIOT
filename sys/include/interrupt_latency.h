#ifndef INTERRUPT_LATENCY_H
#define INTERRUPT_LATENCY_H

#include <stdlib.h>
#include "board.h"
#include "periph/gpio.h"

typedef struct {
    void (*cb)(void*);
    void *arg;
    gpio_t pin_in;
    gpio_t pin_out;
} interrupt_latency_t;

interrupt_latency_t* create_handler(void (*cb)(void*), void*, gpio_t, gpio_t);


void handle(void* arg);

#endif
