//parts of his code are taken from
//https://github.com/igrr/esp32-cam-demo
//by Ivan Grokhotkov
//released under Apache License 2.0

#include "XClk.h"
#include "driver/ledc.h"

bool enableClock(int pin, int frequency) {
    // Enable LEDC peripheral
    periph_module_enable(PERIPH_LEDC_MODULE);

    // Configure LEDC timer
    ledc_timer_config_t timerConfig;
    timerConfig.bit_num = LEDC_TIMER_1_BIT;
    timerConfig.freq_hz = frequency;
    timerConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    timerConfig.timer_num = LEDC_TIMER_0;
    esp_err_t timerError = ledc_timer_config(&timerConfig);
    if (timerError != ESP_OK) {
        return false;
    }

    // Configure LEDC channel
    ledc_channel_config_t channelConfig;
    channelConfig.channel = LEDC_CHANNEL_0;
    channelConfig.timer_sel = LEDC_TIMER_0;
    channelConfig.intr_type = LEDC_INTR_DISABLE;
    channelConfig.duty = 1;
    channelConfig.speed_mode = LEDC_HIGH_SPEED_MODE;
    channelConfig.gpio_num = pin;
    esp_err_t channelError = ledc_channel_config(&channelConfig);
    if (channelError != ESP_OK) {
        return false;
    }

    return true;
}

void disableClock() {
    // Disable LEDC peripheral
    periph_module_disable(PERIPH_LEDC_MODULE);
}
