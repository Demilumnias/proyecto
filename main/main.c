#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include <stdbool.h>

#define LED_PIN     GPIO_NUM_7       // LED externo (a través de resistencia hacia GND)
#define BUTTON_PIN  GPIO_NUM_4       // Pulsador externo (conectado a GND, pull-up interno)

void app_main(void) {
    // --- Configuración del LED ---
    gpio_config_t led = {
        .pin_bit_mask = 1ULL << LED_PIN,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&led);

    // --- Configuración del botón ---
    gpio_config_t btn = {
        .pin_bit_mask = 1ULL << BUTTON_PIN,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,   // activo en alto cuando está suelto
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&btn);

    // --- Variables de estado ---
    bool led_on = false;
    gpio_set_level(LED_PIN, led_on);  // inicia apagado

    int last = 1; // 1 = suelto, 0 = presionado

    ESP_LOGI("LED", "Programa iniciado. LED en GPIO7, botón en GPIO4.");

    while (1) {
        int lvl = gpio_get_level(BUTTON_PIN);

        // Detectar flanco de bajada (1 -> 0)
        if (last == 1 && lvl == 0) {
            // Antirrebote: pequeña espera y confirmación
            vTaskDelay(pdMS_TO_TICKS(20));
            if (gpio_get_level(BUTTON_PIN) == 0) {
                // Cambiar estado del LED
                led_on = !led_on;
                gpio_set_level(LED_PIN, led_on);

                // Mostrar mensaje en el monitor
                ESP_LOGI("LED", "LED %s", led_on ? "ENCENDIDO" : "APAGADO");

                // Esperar a que se suelte para no contar doble
                while (gpio_get_level(BUTTON_PIN) == 0) {
                    vTaskDelay(pdMS_TO_TICKS(10));
                }
                // Pequeña pausa adicional al soltar
                vTaskDelay(pdMS_TO_TICKS(20));
            }
        }

        last = lvl;
        vTaskDelay(pdMS_TO_TICKS(5)); // ciclo de lectura suave
    }
}
