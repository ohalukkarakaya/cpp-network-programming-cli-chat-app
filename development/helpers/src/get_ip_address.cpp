#include "../include/get_ip_address.h"

std::string get_ip_address() {
  struct ifaddrs *interfaces = nullptr;
  std::string ip_address;

  if (getifaddrs(&interfaces) == -1) {
    perror("getifaddrs");
    return "";
  }

  for (struct ifaddrs *iface = interfaces; iface != nullptr;
       iface = iface->ifa_next) {
    if (iface->ifa_addr->sa_family == AF_INET) { // IPv4
      char ip[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, &((struct sockaddr_in *)iface->ifa_addr)->sin_addr, ip, sizeof(ip));
      ip_address = ip;
      break;
    }
  }

  freeifaddrs(interfaces);
  return ip_address;
}
