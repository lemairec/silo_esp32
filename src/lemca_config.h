#ifndef LEMCA_CONFIG_H_
#define LEMCA_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OUTIL_NAME "SONDE"

extern void printConfig();

const char * getWifiPass();
const char * getWifiSsid();

#ifdef __cplusplus
}
#endif

#endif
