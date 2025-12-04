#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "hardware/pwm.h"

#define LED_PIN 15
#define LED_DELAY_MS 500


int pico_led_init(void) {
    return cyw43_arch_init();
}


void pico_set_led(bool led_on) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
}

// 周波数とデューティ比をセットする関数
void pwm_set_freq(uint slice, uint channel, uint freq, float duty) {
    uint32_t clock = 125000000; // 125MHz
    float divider = 16.0f;      // ← 分周を大きくする
    uint32_t wrap = (clock / divider / freq) - 1;

    pwm_set_clkdiv(slice, divider);
    pwm_set_wrap(slice, wrap);
    pwm_set_chan_level(slice, channel, wrap * duty);
}

int main() {
    int rc = pico_led_init();
    stdio_init_all();
    hard_assert(rc == PICO_OK);
    // GP15を出力モードに設定
    gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, true);
    
    // GP15 を PWM に設定（スピーカー）
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(LED_PIN);
    uint chan  = pwm_gpio_to_channel(LED_PIN);
    pwm_set_enabled(slice, true);

    while (true) {
        printf("Hello, Pico 2 W!\n");
        pwm_set_freq(slice, chan, 523, 0.5f);
        pico_set_led(true);          // LED ON
        sleep_ms(LED_DELAY_MS);      // 500ms待つ
        pwm_set_freq(slice, chan, 523, 0.0f);
        pico_set_led(false);         // LED OFF
        sleep_ms(LED_DELAY_MS);      // 500ms待つ
    }
}
