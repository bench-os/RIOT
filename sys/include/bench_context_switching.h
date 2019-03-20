#ifndef __BENCH_CONTEXT_SWITCHING_H__
#define __BENCH_CONTEXT_SWITCHING_H__

#include "xtimer.h"
#include "periph/uart.h"
#include "mutex.h"
#include <stdio.h>

#define PC_UART UART_DEV(0)
#define BAUDRATE (9600)

/**
 * Init the benchmark.
 */
int bench_init(void);

/**
 * Ping the benchmark.
 */
void bench_ping(uint32_t id);

/**
 * Check if there was a switching context.
 */
int check_change(void);

#endif