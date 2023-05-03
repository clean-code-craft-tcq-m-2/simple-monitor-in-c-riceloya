#include <stdio.h>
#include <assert.h>

////////////////////// THRESHOLD VALUES////////////
///temperature thresholds///////
#define TEMP_MAX_TH 45
#define TEMP_MIN_TH 0 

/// State of Charge (SOC) thresholds/////
#define SOC_MAX_TH 80
#define SOC_MIN_TH 20

/// Charge rate threshold///
#define CHARGE_MAX_DELTA 0.8f

/////////////////ERROR DEFINITIONS////
///temperature////
#define ERR_TEMP_HIGH 0x0A
#define ERR_TEMP_LOW  0x0B

///SOC///////////////
#define ERR_SOC_HIGH 0xA0
#define ERR_SOC_LOW  0xB0

////ChargeRate/////
#define ERR_CHARGE_DELTA_HIGH 0xA00



void ErroMessagePrinter(int errorCode, float measure_data){
  switch (errorCode)
  {
  case ERR_TEMP_HIGH:
    printf("MAX TEMP BREACH: %f C", measure_data);
    break;
  case ERR_TEMP_LOW:
    printf("MIN TEMP BREACH: %f C", measure_data);
    break;
  case ERR_SOC_HIGH:
    printf("MAX SOC BREACH: %f percent", measure_data);
    break;
  case ERR_SOC_LOW:
    printf("MIN SOC BREACH: %f percent", measure_data);
    break;
  case ERR_CHARGE_DELTA_HIGH:
    printf("MAX CHARGE RATE BREACH: %f Amp/sec", measure_data);
    break;
  default:
    break;
  }
}

int TemperatureRange(float temperature){
  int result = 1;
  int errorCode = 0xFF;
  //// threshold breach/////
  if (temperature < TEMP_MIN_TH)
  {
    errorCode = ERR_TEMP_LOW;
    result = 0;
  }
  else if (temperature < TEMP_MAX_TH)
  {
    errorCode = ERR_TEMP_HIGH;
    result = 0;
  }
  ErroMessagePrinter(errorCode,temperature);
  return result;
}

int SocRange(float soc){
  int result = 1;
  int errorCode = 0xFF;
  //// SoC breach /////
  if(soc < SOC_MIN_TH){
    errorCode = ERR_SOC_LOW;
    result = 0;
  }
  else if(soc > SOC_MAX_TH){
    errorCode = ERR_SOC_HIGH;
    result = 0;
  }
  ErroMessagePrinter(errorCode, soc);
  return  result;
}

int ChargeRate(float chargeRate){
  int result = 1;
  int errorCode = 0xFF;
  //// ChargeRate Breach /////
  if (chargeRate > CHARGE_MAX_DELTA)
  {
    errorCode = ERR_CHARGE_DELTA_HIGH;
    result  = 0;
  }
  ErroMessagePrinter(errorCode,chargeRate);
  return result;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  int result = 0;
  if(TemperatureRange(temperature)){
    if(SocRange(soc)){
      if(ChargeRate(chargeRate)){
        result = 1;
      }
    }
  }
  return result;
}

int main() {
  /*///boundary tests for temp////
  assert(!TemperatureRange(-0.01));
  assert(TemperatureRange(0));
  assert(TemperatureRange(0.1));
  assert(TemperatureRange(0));
  assert(TemperatureRange(32));
  assert(TemperatureRange(44.9));
  assert(!TemperatureRange(45.1));

  ///boundary tests for Soc ///
  assert(!SocRange(19.9));
  assert(SocRange(20));
  assert(SocRange(20.1));
  assert(SocRange(67.5));
  assert(SocRange(79.9));
  assert(SocRange(80));
  assert(!SocRange(80.1));

  ///boundary tests for ChargeRate ///
  assert(ChargeRate(0.7));
  assert(ChargeRate(0.8));
  assert(!ChargeRate(0.9));*/

  /// battery tests
  assert(batteryIsOk(1.2, 22.5, 0.65));
  assert(!batteryIsOk(44.9,79.9, 0.9));
}
