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
	printf("acmp_callback:\t ACMP FALLING EDGE DETECTED\n");
	return;
}

int main(void)
{
	comparator_set_trigger_callback(acmp, acmp_callback, NULL);
	comparator_set_trigger(acmp, COMPARATOR_TRIGGER_FALLING_EDGE);
	while(1) {
		printf("ACMP Output:\t%d \n", comparator_get_output(acmp));
		k_msleep(200);
	}

	return 0;
}

