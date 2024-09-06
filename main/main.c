#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "driver/i2c.h"
#include "freertos/queue.h"
#include "esp_log.h"
#include "driver/gpio.h"
#include "ssd1306.c"
#include "image.h"
#include "esp_sleep.h"

SSD1306_t dev;
#define CONFIG_SDA_GPIO 1
#define CONFIG_SCL_GPIO 2
#define CONFIG_RESET_GPIO 0

#define BTN_UP GPIO_NUM_11
#define BTN_DOWN GPIO_NUM_10
#define BTN_PLUS GPIO_NUM_9
#define BTN_MINUS GPIO_NUM_8
#define BTN_OK GPIO_NUM_7
#define BTN_PWR GPIO_NUM_6
#define CH1 GPIO_NUM_5




xQueueHandle BTN_UPQueue;
xQueueHandle BTN_DOWNQueue;
xQueueHandle BTN_PLUSQueue;
xQueueHandle BTN_MINUSQueue;
xQueueHandle BTN_OKQueue;
xQueueHandle BTN_PWRQueue;
xQueueHandle CH1Queue;

uint64_t BTN_UP_pre_time = 0;
uint64_t BTN_UP_intr_time = 0;
uint64_t BTN_UP_curr_time = 0;

uint64_t BTN_DOWN_pre_time = 0;
uint64_t BTN_DOWN_intr_time = 0;
uint64_t BTN_DOWN_curr_time = 0;

uint64_t BTN_PLUS_pre_time = 0;
uint64_t BTN_PLUS_intr_time = 0;
uint64_t BTN_PLUS_curr_time = 0;

uint64_t BTN_MINUS_pre_time = 0;
uint64_t BTN_MINUS_intr_time = 0;
uint64_t BTN_MINUS_curr_time = 0;

uint64_t BTN_OK_pre_time = 0;
uint64_t BTN_OK_intr_time = 0;
uint64_t BTN_OK_curr_time = 0;

uint64_t BTN_PWR_pre_time = 0;
uint64_t BTN_PWR_intr_time = 0;
uint64_t BTN_PWR_curr_time = 0;

uint64_t CH1_pre_time = 0;
uint64_t CH1_intr_time = 0;
uint64_t CH1_curr_time = 0;



void BTN_UPTask(void *params)
{
    gpio_set_direction(BTN_UP, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_UP, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(BTN_UPQueue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(BTN_UP) == 0)
            {
                BTN_UP_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (BTN_UP_curr_time - BTN_UP_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "BTN_UP Task ");
            }

            xQueueReset(BTN_UPQueue);
        }
    }
}

void BTN_DOWNTask(void *params)
{
    gpio_set_direction(BTN_DOWN, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_DOWN, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(BTN_DOWNQueue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(BTN_DOWN) == 0)
            {
                BTN_DOWN_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (BTN_DOWN_curr_time - BTN_DOWN_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "BTN_DOWNTask ");
            }

            xQueueReset(BTN_DOWNQueue);
        }
    }
}


void BTN_PLUSTask(void *params)
{
    gpio_set_direction(BTN_PLUS, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_PLUS, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(BTN_PLUSQueue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(BTN_PLUS) == 0)
            {
                BTN_PLUS_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (BTN_PLUS_curr_time - BTN_PLUS_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "BTN_PLUSTask ");
            }

            xQueueReset(BTN_PLUSQueue);
        }
    }
}


void BTN_MINUSTask(void *params)
{
    gpio_set_direction(BTN_MINUS, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_MINUS, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(BTN_MINUSQueue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(BTN_MINUS) == 0)
            {
                BTN_MINUS_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (BTN_MINUS_curr_time - BTN_MINUS_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "BTN_MINUSTask ");
            }

            xQueueReset(BTN_MINUSQueue);
        }
    }
}


void BTN_OKTask(void *params)
{
    gpio_set_direction(BTN_OK, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_OK, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(BTN_OKQueue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(BTN_OK) == 0)
            {
                BTN_OK_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (BTN_OK_curr_time - BTN_OK_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "BTN_OK Task ");
            }

            xQueueReset(BTN_OKQueue);
        }
    }
}

void BTN_PWRTask(void *params)
{
    gpio_set_direction(BTN_PWR, GPIO_MODE_INPUT);
    gpio_set_intr_type(BTN_PWR, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(BTN_PWRQueue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(BTN_PWR) == 0)
            {
                BTN_PWR_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (BTN_PWR_curr_time - BTN_PWR_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "BTN_PWR Task ");
            }

            xQueueReset(BTN_PWRQueue);
        }
    }
}


void CH1Task(void *params)
{
    gpio_set_direction(CH1, GPIO_MODE_INPUT);
    gpio_set_intr_type(CH1, GPIO_INTR_NEGEDGE);
    int BTN_NUMBER = 0;

    while (1)
    {
        if (xQueueReceive(CH1Queue, &BTN_NUMBER, portMAX_DELAY))
        {
            // Wait for button release
            while (gpio_get_level(CH1) == 0)
            {
                CH1_curr_time = esp_timer_get_time();
            }

            // Check if the button was pressed for a short duration
            if (CH1_curr_time - CH1_intr_time < 1000000) // Adjust the time threshold for short press detection as needed
            {
                ESP_LOGI("NO TAG", "CH1 Task ");
            }

            xQueueReset(CH1Queue);
        }
    }
}



static void IRAM_ATTR BTN_UP_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - BTN_UP_pre_time > 400000)
    {
        xQueueSendFromISR(BTN_UPQueue, &pinNumber, NULL);
        BTN_UP_intr_time = esp_timer_get_time();
    }

    BTN_UP_pre_time = esp_timer_get_time();
}

static void IRAM_ATTR BTN_DOWN_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - BTN_DOWN_pre_time > 400000)
    {
        xQueueSendFromISR(BTN_DOWNQueue, &pinNumber, NULL);
        BTN_DOWN_intr_time = esp_timer_get_time();
    }

    BTN_DOWN_pre_time = esp_timer_get_time();
}

static void IRAM_ATTR BTN_PLUS_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - BTN_PLUS_pre_time > 400000)
    {
        xQueueSendFromISR(BTN_PLUSQueue, &pinNumber, NULL);
        BTN_PLUS_intr_time = esp_timer_get_time();
    }

    BTN_PLUS_pre_time = esp_timer_get_time();
}

static void IRAM_ATTR BTN_MINUS_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - BTN_MINUS_pre_time > 400000)
    {
        xQueueSendFromISR(BTN_MINUSQueue, &pinNumber, NULL);
        BTN_MINUS_intr_time = esp_timer_get_time();
    }

    BTN_MINUS_pre_time = esp_timer_get_time();
}

static void IRAM_ATTR BTN_OK_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - BTN_OK_pre_time > 400000)
    {
        xQueueSendFromISR(BTN_OKQueue, &pinNumber, NULL);
        BTN_OK_intr_time = esp_timer_get_time();
    }

    BTN_OK_pre_time = esp_timer_get_time();
}

static void IRAM_ATTR BTN_PWR_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - BTN_PWR_pre_time > 400000)
    {
        xQueueSendFromISR(BTN_PWRQueue, &pinNumber, NULL);
        BTN_PWR_intr_time = esp_timer_get_time();
    }

    BTN_PWR_pre_time = esp_timer_get_time();
}


static void IRAM_ATTR CH1_interrupt_handler(void *args)
{
    int pinNumber = (int)args;

    if (esp_timer_get_time() - CH1_pre_time > 400000)
    {
        xQueueSendFromISR(CH1Queue, &pinNumber, NULL);
        CH1_intr_time = esp_timer_get_time();
    }

    CH1_pre_time = esp_timer_get_time();
}

void app_main(void)
{

    i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);

    BTN_UPQueue = xQueueCreate(10, sizeof(int));
    BTN_DOWNQueue = xQueueCreate(10, sizeof(int));
    BTN_PLUSQueue = xQueueCreate(10, sizeof(int));
    BTN_MINUSQueue = xQueueCreate(10, sizeof(int));
    BTN_OKQueue = xQueueCreate(10, sizeof(int));
    BTN_PWRQueue = xQueueCreate(10, sizeof(int));
    CH1Queue = xQueueCreate(10, sizeof(int));

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BTN_UP, BTN_UP_interrupt_handler, (void *)BTN_UP);
    gpio_isr_handler_add(BTN_DOWN, BTN_DOWN_interrupt_handler, (void *)BTN_DOWN);
    gpio_isr_handler_add(BTN_PLUS, BTN_PLUS_interrupt_handler, (void *)BTN_PLUS);
    gpio_isr_handler_add(BTN_MINUS, BTN_MINUS_interrupt_handler, (void *)BTN_MINUS);
    gpio_isr_handler_add(BTN_OK, BTN_OK_interrupt_handler, (void *)BTN_OK);
    gpio_isr_handler_add(BTN_PWR, BTN_PWR_interrupt_handler, (void *)BTN_PWR);
    gpio_isr_handler_add(CH1, CH1_interrupt_handler, (void *)CH1);

    xTaskCreate(BTN_UPTask, "BTN_UPTask", 2048, NULL, 1, NULL);
    xTaskCreate(BTN_DOWNTask, "BTN_DOWNTask", 2048, NULL, 1, NULL);
    xTaskCreate(BTN_PLUSTask, "BTN_PLUSTask", 2048, NULL, 1, NULL);
    xTaskCreate(BTN_MINUSTask, "BTN_MINUSTask", 2048, NULL, 1, NULL);
    xTaskCreate(BTN_OKTask, "BTN_OKTask", 2048, NULL, 1, NULL);
    xTaskCreate(BTN_PWRTask, "BTN_PWRTask", 2048, NULL, 1, NULL);
    xTaskCreate(CH1Task, "CH1Task", 2048, NULL, 1, NULL);

}
