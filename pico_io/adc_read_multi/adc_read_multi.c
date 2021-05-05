#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/adc.h"


#define LED_PIN 16

static int delay = 0;

// map s in range a1 - a2 to value in range b1 - b2
int map(int s, int a1, int a2, int b1, int b2)
{
  return b1 + (s - a1) * (b2 - b1) / (a2 - a1);
}

void core1_blink() {
    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(delay);
        gpio_put(LED_PIN, 0);
        sleep_ms(delay);
    }
}

void main() {

    adc_init();
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);

    // Initialize pins, and set to outputs 
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // Launch second core
    multicore_launch_core1(core1_blink);

    while (1) {
        uint16_t result = adc_read();
        // Map delay in ms based on adc value
        if (result >= 0 && result <= 0xfff) 
          delay = map(result, 0, 0xfff, 0, 1000);
        sleep_ms(200);
    }
}
