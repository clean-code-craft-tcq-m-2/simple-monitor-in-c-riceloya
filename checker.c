#include <stdio.h>
#include <assert.h>

int TemperatureRange(temperature){
  if(temperature < 0 || temperature > 45) {
    printf("Temperature out of range!\n");
    return 0;}
  else{
    printf("Temperature in range");
    return 1;
  }
}

int SocRange(soc){
  if(soc < 20 || soc > 80) {
    printf("State of Charge out of range!\n");
    return 0;}
  else{
    printf("Soc in Range");
    return 1;
  }
}

int ChrgRt(chargeRate){
  if(chargeRate > 0.8) { 
    printf("Charge Rate out of range!\n");
    return 0;}
  else{
    printf("Charge Rate in range");
    return 1;}
} 

int batteryIsOk(float temperature, float soc, float chargeRate) {
  TemperatureRange(temperature);
  SocRange(soc);
  ChrgRt(chargeRate);
}

int main() {
  batteryIsOk(25,70,0.7);
  batteryIsOk(50,85,0);
  //assert(batteryIsOk(25, 70, 0.7));
  //assert(!batteryIsOk(50, 85, 0));
}
