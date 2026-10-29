#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <string.h>
#include "endpoint_config.h"
#include <stdlib.h>
#include <errno.h>

void apply_endpoint_config (struct server_settings *settings, const char *config_path){
  char ip[sizeof(settings->ip)];

  DWORD ip_length = GetPrivateProfileStringA(
      "server", "host", settings->ip,
      ip, sizeof(ip), config_path
  );
  
  // Apply only a complete, valid IPv4 destination
  struct in_addr parsed_ip;
  if (ip_length > 0 && ip_length < sizeof(ip) - 1) {
      if (inet_pton(AF_INET, ip, &parsed_ip) == 1 &&
          parsed_ip.s_addr != INADDR_ANY && 
          parsed_ip.s_addr != INADDR_BROADCAST) {
        strcpy(settings->ip, ip);
      }
  }
  
  char port_text[16];
  DWORD port_length = GetPrivateProfileStringA(
    "server", "port", "",
    port_text, sizeof(port_text), config_path
  );
  if (port_length > 0 && port_length < sizeof(port_text) - 1) {
    char *end;
    errno = 0;

    long port = strtol(port_text, &end, 10);

    if (errno == 0 && end != port_text &&
      *end == '\0' && port > 0 && port <= 65535) {
      settings->port = (int)port;
    }
  }
}

int get_endpoint_config_path(char *path, size_t capacity)
{
  DWORD path_length = GetModuleFileNameA(NULL, path,capacity);
  if (path_length == 0 || path_length >= capacity) {
    return 0;
  }

  char *last_slash = strrchr(path, '\\'); //strrchr() searches a string for the last occurrence of a character and returns a pointer to it.
  if (last_slash == NULL) {
    return 0;
  }

  char *filename = last_slash + 1;

  size_t remaining_space = capacity - (filename - path);
  const char *ini_name = "client_endpoint.ini";
  if (strlen(ini_name) + 1 > remaining_space) {
      return 0;
  }

  strcpy(filename, ini_name);
  return 1;
}