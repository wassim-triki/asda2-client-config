#include <windows.h>
#include "endpoint_config.h"

__declspec(dllexport)
void __cdecl configure_client(struct server_settings *settings){

  char config_path[MAX_PATH];

  if(!get_endpoint_config_path(config_path, sizeof(config_path))){
    return;
  }

  apply_endpoint_config(settings,config_path);
}