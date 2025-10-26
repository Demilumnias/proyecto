#include <stdint.h>
#include <stdbool.h>
#include "gpio_regs.h"

// Ajusta si querés otros pines:
#define LED_PIN 4   // GPIO4 -> R 220–330Ω -> LED -> GND
#define BTN_PIN 5   // GPIO5 con pull-up externo 10k a 3V3; botón a GND

static void delay_cycles(volatile uint32_t n){ while(n--) __asm__ __volatile__("nop"); }
static void sleep_ms(uint32_t ms){ for(uint32_t i=0;i<ms;++i) delay_cycles(20000); } // ~1ms aprox

int main(void){
    // LED como salida, arranca apagado
    GPIO_ENABLE_W1TS_REG = (1u << LED_PIN);
    GPIO_OUT_W1TC_REG    = (1u << LED_PIN);

    // Botón como entrada (no tocar ENABLE bit)
    GPIO_ENABLE_REG &= ~(1u << BTN_PIN);

    bool led_on = false;
    int last = 1;     // reposo=1 por pull-up
    int stable = 1;

    for(;;){
        int raw = (GPIO_IN_REG >> BTN_PIN) & 1u;

        // Debounce simple
        if(raw != stable){
            sleep_ms(20);
            int raw2 = (GPIO_IN_REG >> BTN_PIN) & 1u;
            if(raw2 == raw) stable = raw2;
        }

        // Flanco 1->0: presionado
        if(last == 1 && stable == 0){
            led_on = !led_on;
            if(led_on) GPIO_OUT_W1TS_REG = (1u << LED_PIN);
            else       GPIO_OUT_W1TC_REG = (1u << LED_PIN);

            // Esperar a que se suelte
            while(((GPIO_IN_REG >> BTN_PIN) & 1u) == 0) sleep_ms(10);
            sleep_ms(20);
        }

        last = stable;
        sleep_ms(5);
    }
}
