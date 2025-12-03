#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define LED_DELAY_MS 500


int pico_led_init(void) {
    return cyw43_arch_init();
}


void pico_set_led(bool led_on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

int main() {
    int rc = pico_led_init();
    stdio_init_all();
    hard_assert(rc == PICO_OK);

    while (true) {
        printf("Hello, Pico 2 W!\n");
        pico_set_led(true);
    }
}
