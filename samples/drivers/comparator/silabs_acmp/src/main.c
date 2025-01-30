/*
 * Copyright (c) 2024 Silicon Labs
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/drivers/comparator.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <stdio.h>

static const struct device *const acmp = DEVICE_DT_GET(DT_NODELABEL(acmp0));
static const struct device *const gpioc = DEVICE_DT_GET(DT_NODELABEL(gpioc));

static void acmp_callback(const struct device* dev, void* data) {
	(void)data;
	printf("acmp_callback:\t ACMP EDGE DETECTED\n");
	int pin = gpio_pin_get(gpioc, 3);
	printf("ACMP Output:\t%d \n", comparator_get_output(acmp));
	printf("GPIOC3:\t%d \n", pin);
	printf("FLAGS:\t%d \n", ACMP(0)->IF);
	return;
}

int main(void)
{
	int pin_value = 0;
	comparator_set_trigger_callback(acmp, acmp_callback, NULL);
	comparator_set_trigger(acmp, COMPARATOR_TRIGGER_BOTH_EDGES);
	gpio_pin_configure(gpioc, 3, GPIO_OUTPUT_INACTIVE);
	while(1) {
		if ( pin_value ) {
			pin_value = 0;
		} else {
			pin_value = 1;
		}
		gpio_pin_set(gpioc, 3, pin_value);
		comparator_trigger_is_pending(acmp);
		k_msleep(200);
	}

	return 0;
}

