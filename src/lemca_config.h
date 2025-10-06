#ifndef LEMCA_CONFIG_H_
#define LEMCA_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define OUTIL_NAME "SONDE"

extern void printConfig();

const char * getWifiPass();
const char * getWifiSsid();
const char * getCompany();
const char * getBalise();
int getWifiS();

#ifdef __cplusplus
}
#endif

#endif
