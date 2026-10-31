#ifndef ENDPOINT_CONFIG_H
#define ENDPOINT_CONFIG_H

#include <stddef.h>

struct server_settings {
    unsigned char opset_data[20];
    char ip[20];
    char login_identifier[20];
    int port;
};

void apply_endpoint_config(
    struct server_settings *settings,
    const char *config_path
);

int get_endpoint_config_path(char *path, size_t capacity);

#endif