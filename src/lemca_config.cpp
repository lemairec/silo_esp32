#include "lemca_config.h"

#include "common/util.h"

#include <string>

#include <stdio.h>


const char * version = "22.12.02";

const char *company = "dizy";
const char *balise = "test";
int nb_minutes = 1;

const char *ssid = "Livebox-lemaire";
const char *pass = "lejard54";

const char * getWifiPass(){
    return pass;
}

const char * getWifiSsid(){
    return ssid;
}

const char * getCompany(){
    return company;
}

const char * getBalise(){
    return balise;
}

int getWifiS(){
    return nb_minutes*60;
}


void printConfig(){
    lc_DebugPrint("*** config\n");
    lc_DebugPrint("*\n");
    lc_DebugPrint("* version : %s\n", version);
    lc_DebugPrint("* company : %s\n", company);
    lc_DebugPrint("* balise : %s\n", balise);
    lc_DebugPrint("* nb_minutes : %i\n", nb_minutes);
    lc_DebugPrint("* ssid : %s\n", ssid);
    lc_DebugPrint("* pass : %s\n", pass);
    lc_DebugPrint("*\n");
    lc_DebugPrint("*** end config\n");
    
}
