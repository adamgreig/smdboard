#include <stdint.h>
#include <stdbool.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define LED0_PORT GPIOA
#define LED0_PIN  GPIO1
#define LED1_PORT GPIOA
#define LED1_PIN  GPIO4
#define LED2_PORT GPIOA
#define LED2_PIN  GPIO7
#define LED3_PORT GPIOC
#define LED3_PIN  GPIO4
#define LED4_PORT GPIOC
#define LED4_PIN  GPIO5
#define LED5_PORT GPIOB
#define LED5_PIN  GPIO11
#define LED6_PORT GPIOB
#define LED6_PIN  GPIO12
#define LED7_PORT GPIOB
#define LED7_PIN  GPIO13


int main(void);
void gpio_init(void);
void delay(void);

int LED_PORTS[8] = {GPIOA, GPIOA, GPIOA, GPIOC, GPIOC, GPIOB, GPIOB, GPIOB};
int LED_PINS[8]  = {GPIO1, GPIO4, GPIO7, GPIO4, GPIO5, GPIO11, GPIO12, GPIO13};


void gpio_init()
{
    for(int i=0; i<8; i++) {
        gpio_clear(LED_PORTS[i], LED_PINS[i]);
        gpio_mode_setup(LED_PORTS[i], GPIO_MODE_OUTPUT,
                        GPIO_PUPD_NONE, LED_PINS[i]);
    }
}

void delay()
{
    uint32_t i;
    for(i=0; i<0xFFFF; i++) {
        __asm__("nop");
    }
}

int main()
{
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);

    gpio_init();
    while(true) {
        for(int i=0; i<8; i++) {
            gpio_set(LED_PORTS[i], LED_PINS[i]);
            delay();
            gpio_clear(LED_PORTS[i], LED_PINS[i]);
        }
    }
}
