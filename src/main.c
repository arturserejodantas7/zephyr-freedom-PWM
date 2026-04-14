#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>

#define SLEEP_TIME_MS 1000

/* LED da FRDM-KL25Z */
#define LED0_NODE DT_ALIAS(led0)

#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
#define LED0 DT_GPIO_LABEL(LED0_NODE, gpios)
#define PIN DT_GPIO_PIN(LED0_NODE, gpios)
#define FLAGS DT_GPIO_FLAGS(LED0_NODE, gpios)
#else
#error "LED0 not defined in device tree"
#endif

static const struct device *gpio_dev;

void main(void)
{
    int ret;
    bool led_is_on = false;

    /* Pega o device GPIO correto (forma moderna) */
    gpio_dev = DEVICE_DT_GET(DT_GPIO_CTLR(LED0_NODE, gpios));

    if (!device_is_ready(gpio_dev)) {
        return;
    }

    /* Configura o pino */
    ret = gpio_pin_configure(gpio_dev, PIN, GPIO_OUTPUT_ACTIVE | FLAGS);
    if (ret < 0) {
        return;
    }

    while (1) {
        gpio_pin_set(gpio_dev, PIN, (int)led_is_on);
        led_is_on = !led_is_on;
        k_msleep(SLEEP_TIME_MS);
    }
}