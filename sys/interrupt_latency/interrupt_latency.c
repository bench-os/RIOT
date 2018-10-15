#include "interrupt_latency.h"

interrupt_latency_t* create_handler(void (*cb)(void*), void* arg, gpio_t pin_in, gpio_t pin_out)
{
    interrupt_latency_t *handler = (interrupt_latency_t*) malloc(sizeof(interrupt_latency_t));
    handler->cb = cb;
    handler->arg = arg;
    handler->pin_in = pin_in;
    handler->pin_out = pin_out;

    return handler;
}

void handle(void* arg)
{
    interrupt_latency_t *handler = (interrupt_latency_t *) arg;

    if (gpio_read(handler->pin_in) > 0) {
        gpio_set(handler->pin_out);
        // Call the callback
        handler->cb(handler->arg);
    }
    else {
        gpio_clear(handler->pin_out);
    }
}
