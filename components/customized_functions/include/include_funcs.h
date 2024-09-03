#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include "esp_log.h"

void customlog(esp_err_t err, bool err_check, const char *tag, char *format, ...) {
    // ESP_LOG_NONE ESP_LOG_ERROR ESP_LOG_WARN ESP_LOG_INFO ESP_LOG_DEBUG ESP_LOG_VERBOSE
    va_list args;
    va_start(args, format);
    esp_log_level_t level = (err == ESP_OK) ? ESP_LOG_INFO : ESP_LOG_ERROR;
    char buffer[256];
    vsnprintf(buffer, sizeof(buffer), format, args);
    ESP_LOG_LEVEL(level, tag, "%s", buffer);
    va_end(args);
    if (err_check) {
        ESP_ERROR_CHECK(err);
    }
}

bool is_empty_char(char *c) {
    if ((c == NULL) || (c[0] == '\0')) {
        return 1;
    } else {
        return 0;
    }
}

// Function to convert a hex character to its integer value
int hex_to_int(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    } else if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    } else if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    } else {
        return -1;
    }
}

// Function to decode a URL-encoded string
char *url_decode(const char *str) {
    size_t len = strlen(str);
    char *decoded = malloc(len + 1); // Allocate memory for the decoded string
    if (decoded == NULL) {
        return NULL; // Memory allocation failed
    }

    char *p = decoded;
    for (size_t i = 0; i < len; i++) {
        if (str[i] == '%' && i + 2 < len) {
            int high = hex_to_int(str[i + 1]);
            int low = hex_to_int(str[i + 2]);
            if (high >= 0 && low >= 0) {
                *p++ = (char)((high << 4) | low);
                i += 2;
            } else {
                *p++ = str[i];
            }
        } else if (str[i] == '+') {
            *p++ = ' ';
        } else {
            *p++ = str[i];
        }
    }
    *p = '\0'; // Null-terminate the decoded string

    return decoded;
}

double MIN(double x, double y)
{
    if (x<y)
        return x;
    else if (y<x)
        return y;
    else
        return 0.0;
}

void get_substring(char* A, char* B, char* dest, uint8_t reset) {
    if (reset==1) {
        memset(dest, '\0', strlen(dest)*sizeof(char));
    }
    if (A==NULL && B==NULL) {
        dest[0] = '\0';
    } else if (B==NULL) {
        strcpy(dest, A);
    } else if (A==NULL) {
        strcpy(dest, B);
    } else {
        size_t length = B - A;
        memcpy(dest, A, length);
        dest[length] = '\0'; // Null-terminate the destination string
        // printf("length is %d\n", length);
    }
}


/*


char* trim(char* str, uint_least8_t trimtrailing, uint_least8_t outbound) {
    char* end;
    if (outbound==1) {
        while (isspace((unsigned char)*str-1) || *str-1 == '\n' || *str-1 == '\r') str--;
        // Trim trailing space and line breaks
        if (trimtrailing<=0) {
            return str;
        }
        end = str + strlen(str) - 1;
        while (end > str && (isspace((unsigned char)*end+1) || *end+1 == '\n' || *end+1 == '\r')) end++;

        // Write new null terminator
        *(end + 1) = '\0';

        return str;
    } else {
        // Trim leading space and line breaks
        while (isspace((unsigned char)*str) || *str == '\n' || *str == '\r') str++;

        if (*str == 0)  // All spaces and line breaks?
            return str;

        // Trim trailing space and line breaks
        if (trimtrailing<=0) {
            return str;
        }
        end = str + strlen(str) - 1;
        while (end > str && (isspace((unsigned char)*end) || *end == '\n' || *end == '\r')) end--;

        // Write new null terminator
        *(end + 1) = '\0';

        return str;
    }
}



char* format_string(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Determine the length of the formatted string
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (length < 0) {
        return NULL; // Error occurred
    }

    // Allocate memory for the formatted string
    char *formatted_string = (char *)malloc(length + 1);
    if (!formatted_string) {
        return NULL; // Memory allocation failed
    }

    // Format the string and store it in the allocated memory
    va_start(args, format);
    vsnprintf(formatted_string, length + 1, format, args);
    va_end(args);

    return formatted_string;
}

*/
