#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

// on-board LED (GPIO 25)
#define LED_PIN PICO_DEFAULT_LED_PIN

// map s in range a1 - a2 to value in range b1 - b2
int map(int s, int a1, int a2, int b1, int b2)
{
  return b1 + (s - a1) * (b2 - b1) / (a2 - a1);
}

uint main() {
    stdio_init_all();
    printf("ADC Example, measuring GPIO26 and mapping to blink delay\n");

    adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    // Set GPIO 25 as output
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (1) {
        uint16_t result = adc_read();
        // Map delay in ms based on adc value
        int delay = 0;
        if (result >= 0 && result <= 0xfff) 
          delay = map(result, 0, 0xfff, 0, 1000);
        printf("Raw value: 0x%03x, Delay: %u ms\n", result, delay);
        gpio_put(LED_PIN, 1);
        sleep_ms(delay);
        gpio_put(LED_PIN, 0);
        sleep_ms(delay);
    }
}
