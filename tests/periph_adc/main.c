/*
 * Copyright (C) 2014 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup tests
 * @{
 *
 * @file
 * @brief       Test case for the low-level ADC driver
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include <stdio.h>

#include "board.h"
#include "vtimer.h"
#include "periph/adc.h"

#define RES             ADC_RES_12BIT

static int values[ADC_NUMOF][ADC_MAX_CHANNELS];

int main(void)
{
    int res;

    printf("RIOT ADC test\n");
    printf("This test simply converts each available ADC channel about every 10ms\n\n");

    for (int i = 0; i < ADC_NUMOF; i++) {
        for (int j = 0; j < ADC_MAX_CHANNELS; j++) {
            values[i][j] = -1;
        }
    }

#if ADC_0_EN
    printf("Initializing ADC_0 @ %i bit resolution", (6 + (2* RES)));
    res = adc_init(ADC_0, RES);
    if (res == 0) {
        puts("    ...[ok]");
    }
    else {
        puts("    ...[failed]");
        return 1;
    }
#endif
#if ADC_0_EN
    printf("Initializing ADC_1 @ %i bit resolution", (6 + (2* RES)));
    res = adc_init(ADC_1, RES);
    if (res == 0) {
        puts("    ...[ok]\n");
    }
    else {
        puts("    ...[failed]");
        return 1;
    }
#endif
#if ADC_0_EN
    printf("Initializing ADC_1 @ %i bit resolution", (6 + (2* RES)));
    res = adc_init(ADC_2, RES);
    if (res == 0) {
        puts("    ...[ok]\n");
    }
    else {
        puts("    ...[failed]");
        return 1;
    }
#endif

    while (1) {
#if ADC_0_EN
        for (int i = 0; i < ADC_0_CHANNELS; i++) {
            values[ADC_0][i] = adc_sample(ADC_0, i);
        }
#endif
#if ADC_1_EN
        for (int i = 0; i < ADC_1_CHANNELS; i++) {
            values[ADC_1][i] = adc_sample(ADC_0, i);
        }
#endif
#if ADC_2_EN
        for (int i = 0; i < ADC_2_CHANNELS; i++) {
            values[ADC_2][i] = adc_sample(ADC_0, i);
        }
#endif

        printf("\rValues: ");

        for (int i = 0; i < ADC_NUMOF; i++) {
            for (int j = 0; j < ADC_MAX_CHANNELS; j++) {
                if (values[i][j] >= 0) {
                    printf("ADC_%i-CH%i: %4i  ", i, j, values[i][j]);
                }
            }
        }
        vtimer_usleep(10 * 1000);
    }

    return 0;
}
