#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#define LED_PIN 15
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
    // GP15を出力モードに設定
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, true);

    while (true) {
        printf("Hello, Pico 2 W!\n");
        pico_set_led(true);          // LED ON
        sleep_ms(LED_DELAY_MS);      // 500ms待つ
        pico_set_led(false);         // LED OFF
        sleep_ms(LED_DELAY_MS);      // 500ms待つ

        printf("LED ON\n");
        gpio_put(LED_PIN, true);   // LED点灯
        sleep_ms(LED_DELAY_MS);
        printf("LED OFF\n");
        gpio_put(LED_PIN, false);  // LED消灯
        sleep_ms(LED_DELAY_MS);
    }
}
