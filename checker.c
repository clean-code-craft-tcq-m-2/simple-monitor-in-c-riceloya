#include <stdio.h>
#include <assert.h>

////////////////////// THRESHOLD VALUES////////////
///temperature thresholds///////
#define TEMP_MAX_TH 45
#define TEMP_MIN_TH 0 
/// temp warning thresholds////
#define TEMP_MAX_WARN_TH (TEMP_MAX_TH * 0.95f)
#define TEMP_MIN_WARN_TH (TEMP_MAX_TH*0.05f)

/// State of Charge (SOC) thresholds/////
#define SOC_MAX_TH 80
#define SOC_MIN_TH 20
////SOC warning thresholds ///
#define SOC_MAX_WAR_TH (SOC_MAX_TH*0.95f)
#define SOC_MIN_WAR_TH ((SOC_MIN_TH)+(SOC_MAX_TH*0.95f))

/// Charge rate threshold///
#define CHARGE_MAX_DELTA 0.8f
/// Charge rate warning threshold///
#define CHARGE_MAX_DELTA_WAR (CHARGE_MAX_DELTA*0.95f)

/////////////////ERROR DEFINITIONS////
///temperature////
#define ERR_TEMP_HIGH 0x01
#define ERR_TEMP_LOW  0x02
///temperature warning error
#define ERR_TEMP_HIGH_WAR 0x03
#define ERR_TEMP_LOW_WAR  0x04

///SOC///////////////
#define ERR_SOC_HIGH 0x10
#define ERR_SOC_LOW  0x20
///SOC warning error///
#define ERR_SOC_HIGH_WAR 0x30
#define ERR_SOC_LOW_WAR  0x40

////ChargeRate/////
#define ERR_CHARGE_DELTA_HIGH 0x100
////ChargeRate warning///
#define ERR_CHARGE_DELTA_HIGH_WAR 0x200

//language definition
 #define LANG_ENGLISH 0
 #define LANG_DEUTSCH 1

int sysLanguage =  LANG_ENGLISH;

void ErroMessagePrinter(int errorCode, float measure_data){
  if(sysLanguage == LANG_ENGLISH){
    switch (errorCode){
      case ERR_TEMP_HIGH:
        printf("MAX TEMP BREACH: %f C", measure_data);
        break;
      case ERR_TEMP_LOW:
        printf("MIN TEMP BREACH: %f C", measure_data);
        break;
      case ERR_TEMP_HIGH_WAR:
        printf("MAX TEMP REACH WARNING: %f C", measure_data);
        break;
      case ERR_TEMP_LOW_WAR:
        printf("MIN TEMP REACH WARNING: %f C", measure_data);
        break;
      case ERR_SOC_HIGH:
        printf("MAX SOC BREACH: %f percent", measure_data);
        break;
      case ERR_SOC_LOW:
        printf("MIN SOC BREACH: %f percent", measure_data);
        break;
      case ERR_SOC_HIGH_WAR:
        printf("MAX SOC REACH WARNING: %f percent", measure_data);
        break;
      case ERR_SOC_LOW_WAR:
        printf("MIN SOC REACH WARNING: %f percent", measure_data);
        break;
      case ERR_CHARGE_DELTA_HIGH:
        printf("MAX CHARGE RATE BREACH: %f Amp/sec", measure_data);
        break;
      case ERR_CHARGE_DELTA_HIGH_WAR:
        printf("MAX CHARGE RATE REACH WARNING: %f Amp/sec", measure_data);
        break;
      default:
        break;
    }
  }
  else if(sysLanguage == LANG_DEUTSCH){
    switch (errorCode){
      case ERR_TEMP_HIGH:
        printf("MAXIMALTEMPERATURVERLETZUNG: %f C", measure_data);
        break;
      case ERR_TEMP_LOW:
        printf("MINDESTTEMPERATURVERLETZUNG: %f C", measure_data);
        break;
      case ERR_TEMP_HIGH_WAR:
        printf("MAXIMALTEMPERATURWARNUNG: %f C", measure_data);
        break;
      case ERR_TEMP_LOW_WAR:
        printf("MINDESTTEMPERATURWARNUNG: %f C", measure_data);
        break;
      case ERR_SOC_HIGH:
        printf("MAXIMALE SOC-VERLETZUNG: %f prozent", measure_data);
        break;
      case ERR_SOC_LOW:
        printf("MINIMALE SOC-VERLETZUNG: %f prozent", measure_data);
        break;
      case ERR_SOC_HIGH_WAR:
        printf("MAXIMALE SOC-WARNUNG: %f prozent", measure_data);
        break;
      case ERR_SOC_LOW_WAR:
        printf("MINIMALE SOC-WARNUNG: %f prozent", measure_data);
        break;
      case ERR_CHARGE_DELTA_HIGH:
        printf("VERLETZUNG DER MAXIMALEN GEBÜHRENRATE: %f Amp/sek", measure_data);
        break;
      case ERR_CHARGE_DELTA_HIGH_WAR:
        printf("WARNUNG MAXIMALE LADERATE REICHWEITE: %f Amp/sek", measure_data);
        break;
      default:
        break;
    }
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
  else if (temperature > TEMP_MAX_TH)
  {
    errorCode = ERR_TEMP_HIGH;
    result = 0;
  }
  ////warning reach/// 
  else if(temperature < TEMP_MIN_WARN_TH)
  {
    errorCode = ERR_TEMP_LOW_WAR;
  }
  else if(temperature > TEMP_MAX_WARN_TH)
  {
    errorCode = ERR_TEMP_HIGH_WAR;
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
  else if(soc < SOC_MIN_WAR_TH){
    errorCode = ERR_SOC_LOW_WAR;
  }
  else if(soc < SOC_MAX_WAR_TH){
    errorCode = ERR_SOC_HIGH_WAR;
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
  else if (chargeRate > CHARGE_MAX_DELTA_WAR){
    errorCode =  ERR_CHARGE_DELTA_HIGH_WAR;
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
  ///boundary tests for temp////
  assert(!TemperatureRange(-0.01));
  assert(TemperatureRange(0));
  assert(TemperatureRange(0.1));
  assert(TemperatureRange(0));
  sysLanguage = LANG_DEUTSCH;
  assert(TemperatureRange(32));
  assert(TemperatureRange(44.9));
  assert(!TemperatureRange(45.1));
  sysLanguage = LANG_ENGLISH;
  ///boundary tests for Soc ///
  assert(!SocRange(19.9));
  assert(SocRange(20));
  assert(SocRange(20.1));
  assert(SocRange(67.5));
  sysLanguage = LANG_DEUTSCH;
  assert(SocRange(79.9));
  assert(SocRange(80));
  assert(!SocRange(80.1));

  ///boundary tests for ChargeRate ///
  assert(ChargeRate(0.7));
  assert(ChargeRate(0.8));
  assert(!ChargeRate(0.9));

  /// battery tests
  assert(batteryIsOk(1.2, 22.5, 0.65));
  assert(!batteryIsOk(44.9,79.9, 0.9));
}
