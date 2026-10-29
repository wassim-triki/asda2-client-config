#include <windows.h>
#include <stdio.h>
#include "endpoint_config.h"


int main(void)
{
  struct server_settings settings = {
      .ip = "127.0.0.1",
      .port = 5000
  };

  char config_path[MAX_PATH];

  if(!get_endpoint_config_path(config_path, sizeof(config_path))){
    printf("Failed to resolve config path.\n");
    return 1;
  }

  apply_endpoint_config(&settings,config_path);

  printf("IP: %s | PORT: %d\n",
     settings.ip
    ,settings.port);

  return 0;
}

