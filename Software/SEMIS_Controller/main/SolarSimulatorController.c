#include <string.h>
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "esp_http_server.h"

#include "html_helper.h"
#include "power_control.h"

static const char *TAG = "main_controller";

static httpd_handle_t server = NULL;

void app_main(void)
{
    // initiallize hw
    power_init();

    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    // TODO: implement value saving to nvs, for example, save the current power state, so that it can be restored after reboot
    // // Open NVS handle
    // ESP_LOGI(TAG, "\nOpening Non-Volatile Storage (NVS) handle...");
    // nvs_handle_t my_handle;
    // ret = nvs_open("storage", NVS_READWRITE, &my_handle);
    // if (ret != ESP_OK) {
    //     ESP_LOGE(TAG, "Error (%s) opening NVS handle!", esp_err_to_name(ret));
    //     return;
    // }

    // // Read value: if not initialized, default is 0
    // int32_t read_counter = 0;
    // ESP_LOGI(TAG, "\nReading counter from NVS...");
    // ret = nvs_get_i32(my_handle, "counter", &read_counter);
    // switch (ret) {
    //     case ESP_OK:
    //         ESP_LOGI(TAG, "Read counter = %" PRIu32, read_counter);
    //         break;
    //     case ESP_ERR_NVS_NOT_FOUND:
    //         ESP_LOGW(TAG, "The value is not initialized yet!");
    //         break;
    //     default:
    //         ESP_LOGE(TAG, "Error (%s) reading!", esp_err_to_name(ret));
    // }
    //  // Store and read an integer value
    // read_counter += 1;
    // ESP_LOGI(TAG, "\nWriting counter to NVS...");
    // ret = nvs_set_i32(my_handle, "counter", read_counter);
    // if (ret != ESP_OK) {
    //     ESP_LOGE(TAG, "Failed to write counter!");
    // }
    // // Delete a key from NVS
    // ESP_LOGI(TAG, "\nDeleting key from NVS...");
    // ret = nvs_erase_key(my_handle, "counter");
    // if (ret != ESP_OK) {
    //     ESP_LOGE(TAG, "Failed to erase key!");
    // }

    // Close NVS handle
    
    // nvs_close(my_handle); // TODO implement value saving


    if (CONFIG_LOG_MAXIMUM_LEVEL > CONFIG_LOG_DEFAULT_LEVEL) {
        /* If you only want to open more logs in the wifi module, you need to make the max level greater than the default level,
         * and call esp_log_level_set() before esp_wifi_init() to improve the log level of the wifi module. */
        esp_log_level_set("wifi", CONFIG_LOG_MAXIMUM_LEVEL);
    }

    ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
    wifi_init_sta();

    // no loop() needed; handlers run in esp-idf tasks
    server = start_webserver(); // Start HTTP server
}