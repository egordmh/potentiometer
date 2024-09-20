#include <stdio.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

// потенциометр подключен к пину GPIO34
static esp_adc_cal_characteristics_t adc1_chars;

void app_main(void)
{

    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);

    adc1_config_width(ADC_WIDTH_BIT_DEFAULT);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
    float voltage;
    float base_voltage = 3.3;//3,3 В базовое напряжение
    int base_resistance = 10000;// Максимальное сопротивление потенциометра
    float resistance;

    while (1) 
    {
        int adc_value = adc1_get_raw(ADC1_CHANNEL_6);
        voltage = (base_voltage/4096)*adc_value;
        resistance = voltage/(base_voltage/base_resistance);
        printf("Resistance: %f Ohm", resistance);
        printf("\n");
        vTaskDelay(500/ portTICK_PERIOD_MS);
    }
}