/*
 Usage: ./sendB <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    
    /*
     output PIN is hardcoded for testing purposes
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 0;
    char* systemCodeArg = argv[1];
    int unitCode = atoi(argv[2]);
    int command  = atoi(argv[3]);
    
    if (wiringPiSetup () == -1) return 1;
    printf("sending systemCodeArg[%s] unitCode[%i] command[%i]\n", systemCodeArg, unitCode, command);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.enableTransmit(PIN);
    int systemCode = 0;

    if (systemCodeArg[0] == 'A' ) {
        systemCode = 1; 	
    } else if (systemCodeArg[0] == 'B') {
        systemCode = 2;
    } else if (systemCodeArg[0] == 'C') {
	systemCode = 3;
    } else if (systemCodeArg[0] == 'D') {
        systemCode = 4;
    } else if (systemCodeArg[0] == 'E') {
        systemCode = 5;
    } else {
	printf("systemcode[%s] is unsupported\n", systemCodeArg);
        return -1; 
    }
    
    switch(command) {
        case 1:
            mySwitch.switchOn(systemCode, unitCode);
            break;
        case 0:
            mySwitch.switchOff(systemCode, unitCode);
            break;
        default:
            printf("command[%i] is unsupported\n", command);
            return -1;
    }
    return 0;
}
