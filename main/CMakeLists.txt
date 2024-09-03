idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES uthash mqtt json esp_adc driver spi_flash bootloader_support esp_http_server app_update esp_wifi nvs_flash customized_functions)