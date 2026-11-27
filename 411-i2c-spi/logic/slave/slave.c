#include "slave/slave.h"
#include "platform/platform.h"

#include <stdbool.h>
#include <stdint.h>

enum { BLINK_PERIOD_MS = 500 };

static uint32_t last_change;
static bool led_on;

void slave_device_init(void)
{
    platform_slave_init();
    led_on = false;
    last_change = platform_time_ms();
}

void slave_device_handle(void)
{
    
    if ((uint32_t)(platform_time_ms() - last_change) >= BLINK_PERIOD_MS)
    {
        last_change += BLINK_PERIOD_MS;
        led_on = !led_on;
        platform_led_set(led_on);
    }
}