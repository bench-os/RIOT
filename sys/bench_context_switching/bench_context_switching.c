#include "bench_context_switching.h"

/**
 * Struct that stores benchmarking information.
 * 
 * previous_id: The id of the previous thread that performs a ping;
 * new_id: The id of the current thread that has performed a ping;
 * current_time: the timer
 */
struct BContext {
  uint32_t previous_id;
  uint32_t new_id;
  uint32_t current_time;
} bench_context;


void bench_ping(uint32_t id) {
  // Save the new id
  bench_context.new_id = id;
  // Save the current time
  bench_context.current_time = xtimer_now_usec();
  // Check for switching context
  check_change();
}

void check_change(void) {
  if(bench_context.new_id != bench_context.previous_id) {
    // Keep the previous id for log
    uint32_t previous_id = bench_context.previous_id;
    // Change previous_id to new_id
    bench_context.previous_id = bench_context.new_id;
    // Compute the difference
    uint32_t result = xtimer_now_usec() - bench_context.current_time;
    printf("[BENCH_CONTEXT_SWITCHING] %"PRIu32" %"PRIu32" %"PRIu32"\n", previous_id, bench_context.new_id, result);
  }
}