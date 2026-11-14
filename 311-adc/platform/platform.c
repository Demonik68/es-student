#include "platform/platform.h"

#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "hardware/adc.h"


#define LED_PIN 25
#define BUTTON_PIN 24
#define CHARGE_PIN 22

// Вход АЦП: вывод GP26, канал 0.
#define ADC_PIN 26
#define ADC_CHANNEL 0

// Опорное напряжение и число уровней 12-разрядного кода АЦП.
#define ADC_VREF_V 3.3f
#define ADC_LEVELS 4096

// Встроенный датчик температуры подключён к каналу 4 АЦП.
#define ADC_TEMP_CHANNEL 4

// Параметры встроенного датчика температуры
#define ADC_TEMP_V_AT_27_C 0.706f
#define ADC_TEMP_V_PER_C 0.001721f

void platform_init(void)
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    adc_init();
    adc_gpio_init(ADC_PIN);
    adc_set_temp_sensor_enabled(true);

    gpio_init(CHARGE_PIN);
    gpio_set_dir(CHARGE_PIN, GPIO_OUT);
    gpio_put(CHARGE_PIN, 0);
}

void platform_led_set(bool on)
{
    gpio_put(LED_PIN, on);
}

bool platform_button_read(void)
{
    return !gpio_get(BUTTON_PIN);
}

float platform_voltage_read(void)
{
    adc_select_input(ADC_CHANNEL);
    return (float)adc_read() * ADC_VREF_V / ADC_LEVELS;
}

float platform_temp_read(void)
{
    adc_select_input(ADC_TEMP_CHANNEL);
    const float voltage = (float)adc_read() * ADC_VREF_V / ADC_LEVELS;
    return 27.0f - (voltage - ADC_TEMP_V_AT_27_C) / ADC_TEMP_V_PER_C;
}

void platform_charge_set(bool on)
{
    gpio_put(CHARGE_PIN, on);
}