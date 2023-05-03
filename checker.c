#include <stdio.h>
#include <assert.h>

int TemperatureRange(temp){
  if(temperature < 0 || temperature > 45) {
    printf("Temperature out of range!\n");
    break;}
  else{
    return 0;
  }
}

int SocRange(soc){
  if(soc < 20 || soc > 80) {
    printf("State of Charge out of range!\n");
    break;}
  else{
    return 0;
  }
}

int ChrgRt(chargeRate){
  if(chargeRate > 0.8) {
    printf("Charge Rate out of range!\n");}
  else{
    return 0;}
} 

int batteryIsOk(float temperature, float soc, float chargeRate) {
  TemperatureRange(temperature);
  SocRange(soc);
  ChrgRt(chargeRate);

  return 1;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
