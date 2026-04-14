#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <pwm_z42.h>

#define TPM_MODULE 1000

// GPIO
#define IN1_PIN 0
#define IN2_PIN 1

const struct device *gpio_dev = DEVICE_DT_GET(DT_NODELABEL(gpiob));

int main(void)
{
    uint16_t duty = 0;

    // Inicializa PWM
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);

    // ENA → PTD0
    pwm_tpm_Ch_Init(TPM0, 0, TPM_PWM_H, GPIOD, 0);

    // Configura GPIO
    gpio_pin_configure(gpio_dev, IN1_PIN, GPIO_OUTPUT);
    gpio_pin_configure(gpio_dev, IN2_PIN, GPIO_OUTPUT);

    // Motor sempre para frente
    gpio_pin_set(gpio_dev, IN1_PIN, 1);
    gpio_pin_set(gpio_dev, IN2_PIN, 0);

    while (1)
    {
        // Aumenta velocidade
        for (duty = 0; duty < TPM_MODULE; duty += 50)
        {
            pwm_tpm_CnV(TPM0, 0, duty);
          
        }

        // Diminui velocidade
        for (duty = TPM_MODULE; duty > 0; duty -= 50)
        {
            pwm_tpm_CnV(TPM0, 0, duty);
            
        }
    }

    return 0;
}