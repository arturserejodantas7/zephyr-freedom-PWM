#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <pwm_z42.h>

#define TPM_MODULE 1000

uint16_t duty = TPM_MODULE / 2; // 50%

// GPIO
#define IN1_PIN 0
#define IN2_PIN 1
#define IN3_PIN 2
#define IN4_PIN 3

const struct device *gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpiob));

int main(void)
{
    // Inicializa PWM (TPM0)
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);

    // ENA → PTD0
    pwm_tpm_Ch_Init(TPM0, 0, TPM_PWM_H, GPIOD, 0);

    // ENB → PTD1
    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOD, 1);

    // Define mesma velocidade para ambos
    pwm_tpm_CnV(TPM0, 0, duty);
    pwm_tpm_CnV(TPM0, 1, duty);

    // Configura GPIO
    gpio_pin_configure(gpio_dev, IN1_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio_dev, IN2_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio_dev, IN3_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio_dev, IN4_PIN, GPIO_OUTPUT);

    while (1)
    {
        // Ambos motores para frente (linha reta)
        gpio_pin_set(gpio_dev, IN1_PIN, 1);
        gpio_pin_set(gpio_dev, IN2_PIN, 0);

        gpio_pin_set(gpio_dev, IN3_PIN, 1);
        gpio_pin_set(gpio_dev, IN4_PIN, 0);

        
    }

    return 0;
}