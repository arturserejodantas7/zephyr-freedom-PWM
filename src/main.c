#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <pwm_z42.h>

#define TPM_MODULE 1000

// Duty cycles para cor laranja
uint16_t duty_red   = 1000;  // 100%
uint16_t duty_green = 400;   // ~40%
uint16_t duty_blue  = 0;     // desligado

int main(void)
{
    // -------------------------
    // INIT PWM (RED - TPM2 CH0)
    // -------------------------
    pwm_tpm_Init(TPM2, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Ch_Init(TPM2, 0, TPM_PWM_H, GPIOB, 18);

    // -------------------------
    // INIT PWM (GREEN - TPM2 CH1)
    // -------------------------
    pwm_tpm_Ch_Init(TPM2, 1, TPM_PWM_H, GPIOB, 19);

    // -------------------------
    // INIT PWM (BLUE - TPM0 CH1)
    // -------------------------
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOD, 1);

    // -------------------------
    // SET DUTY CYCLE (LARANJA)
    // -------------------------
    pwm_tpm_CnV(TPM2, 0, 0);
pwm_tpm_CnV(TPM2, 1, 0);
pwm_tpm_CnV(TPM0, 1, 1000);
k_msleep(2000);


    while (1)
    {
        // LED permanece fixo (laranja constante)
        k_msleep(1000);
    }

    return 0;
}