#include <zephyr/kernel.h>
#include <pwm_z42.h>

#define TPM_MODULE 1000

int main(void)
{
    // -------------------------
    // INIT PWM
    // -------------------------
    pwm_tpm_Init(TPM2, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);
    pwm_tpm_Init(TPM0, TPM_PLLFLL, TPM_MODULE, TPM_CLK, PS_128, EDGE_PWM);

    pwm_tpm_Ch_Init(TPM2, 0, TPM_PWM_H, GPIOB, 18);
    pwm_tpm_Ch_Init(TPM2, 1, TPM_PWM_H, GPIOB, 19);
    pwm_tpm_Ch_Init(TPM0, 1, TPM_PWM_H, GPIOD, 1);

    while (1)
    {
        // 🔶 LIGA (SEU LARANJA REAL)
        pwm_tpm_CnV(TPM2, 0, 0);
        pwm_tpm_CnV(TPM2, 1, 0);
        pwm_tpm_CnV(TPM0, 1, 1000);

        k_msleep(1000);

        // ⚫ DESLIGA (FORÇA LIMPEZA TOTAL DO PWM)
        pwm_tpm_CnV(TPM2, 0, TPM_MODULE);
        pwm_tpm_CnV(TPM2, 1, TPM_MODULE);
        pwm_tpm_CnV(TPM0, 1, TPM_MODULE);

        k_msleep(1000);
    }

    return 0;
}