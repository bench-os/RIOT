#include "bench_context_switching.h"

/**
 * Struct that stores benchmarking information.
 * 
 * previous_id: The id of the previous thread that performs a ping;
 * new_id: The id of the current thread that has performed a ping;
 * current_time: the timer
 */
struct BContext
{
  uint32_t previous_id;
  uint32_t new_id;
  uint32_t current_time;
} bench_context;

void rx_cb(void* arg, uint8_t data)
{
    (void) arg;
    (void) data;
    uint8_t msg = 1;

    for (int i = 0; i < 100; i++) {
        uart_write(PC_UART, &msg, 1);
    }
}

int bench_init(void)
{
    if (uart_init(PC_UART, BAUDRATE, rx_cb, (void *)PC_UART) != UART_OK)
    {
        return 1;
    }
    return 0;
}

void bench_ping(uint32_t id)
{
  // Save the new id
  bench_context.new_id = id;
  // Check for switching context
  if (!check_change())
  {
    // Save the current time
    xtimer_ticks32_t current = xtimer_now();
    bench_context.current_time = current.ticks32;
  }
}

int check_change(void)
{
  if (bench_context.new_id != bench_context.previous_id)
  {
    // Compute the difference
    xtimer_ticks32_t current = xtimer_now();
    uint32_t previous = bench_context.current_time;
    uint32_t result = current.ticks32 - previous;

    // Keep the previous id for log
    uint32_t previous_id = bench_context.previous_id;
    // Change previous_id to new_id
    bench_context.previous_id = bench_context.new_id;

    //uart_write(PC_UART, (uint8_t *)&(msg), 1);
    printf("[BENCH_CONTEXT_SWITCHING] %" PRIu32 " %" PRIu32 " %" PRIu32 "\n", previous_id, bench_context.new_id, result);

    return 1; // Change occurs
  }

  return 0; // No change
}
