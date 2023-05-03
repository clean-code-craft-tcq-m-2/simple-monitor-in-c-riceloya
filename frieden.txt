#include <stdio.h>
#include <assert.h>

#define TEMPERATURE_MAX_THRESHOLD              45
#define TEMPERATURE_MIN_THRESHOLD              0
#define TEMPERATURE_UPPER_WARNING_THRESHOLD    (TEMPERATURE_MAX_THRESHOLD * 0.95f)
#define TEMPERATURE_LOWER_WARNING_THRESHOLD    ((TEMPERATURE_MAX_THRESHOLD * 0.05f) + TEMPERATURE_MIN_THRESHOLD)

#define STATE_OF_CHARGE_MIN_THRESHOLD              20
#define STATE_OF_CHARGE_MAX_THRESHOLD              80
#define STATE_OF_CHARGE_UPPER_WARNING_THRESHOLD    (STATE_OF_CHARGE_MAX_THRESHOLD * 0.95f)
#define STATE_OF_CHARGE_LOWER_WARNING_THRESHOLD    ((STATE_OF_CHARGE_MAX_THRESHOLD * 0.05f) + STATE_OF_CHARGE_MIN_THRESHOLD)

#define CHARGE_RATE_MAX_THRESHOLD              0.8f
#define CHARGE_RATE_UPPER_WARNING_THRESHOLD    (CHARGE_RATE_MAX_THRESHOLD * 0.95f)

#define ERR_TEMPERATURE_TOO_LOW             0x01
#define ERR_TEMPERATURE_TOO_HIGH            0x02
#define ERR_TEMPERATURE_LOW_WARNING         0x04
#define ERR_TEMPERATURE_HIGH_WARNING        0x08
#define ERR_STATE_OF_CHARGE_TOO_LOW         0x10
#define ERR_STATE_OF_CHARGE_TOO_HIGH        0x20
#define ERR_STATE_OF_CHARGE_LOW_WARNING     0x40
#define ERR_STATE_OF_CHARGE_HIGH_WARNING    0x80
#define ERR_CHARGE_RATE_TOO_HIGH            0x100
#define ERR_CHARGE_RATE_HIGH_WARNING        0x200

#define LANGUAGE_ENGLISH    0
#define LANGUAGE_GERMAN     1

int printLanguage = LANGUAGE_ENGLISH;

void printErrorMessage(int errCode, float measurement)
{
    if (printLanguage == LANGUAGE_ENGLISH)
    {
        switch(errCode)
        {
            case ERR_TEMPERATURE_TOO_LOW:
                printf("Temperature is below its limit!\nTemperature: %f\n", measurement);
                break;
            case ERR_TEMPERATURE_TOO_HIGH:
                printf("Temperature is above its limit!\nTemperature: %f\n", measurement);
                break;
            case ERR_TEMPERATURE_LOW_WARNING:
                printf("Warning: Temperature is approaching its lower limit.\nTemperature: %f\n", measurement);
                break;
            case ERR_TEMPERATURE_HIGH_WARNING:
                printf("Warning: Temperature is approaching its upper limit.\nTemperature: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_TOO_LOW:
                printf("State of Charge is below its limit!\nState of Charge: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_TOO_HIGH:
                printf("State of Charge is above its limit!\nState of Charge: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_LOW_WARNING:
                printf("Warning: State of Charge is approaching its lower limit.\nState of Charge: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_HIGH_WARNING:
                printf("Warning: State of Charge is approaching its upper limit.\nState of Charge: %f\n", measurement);
                break;
            case ERR_CHARGE_RATE_TOO_HIGH:
                printf("Charge Rate is above its limit!\nCharge Rate: %f\n", measurement);
                break;
            case ERR_CHARGE_RATE_HIGH_WARNING:
                printf("Warning: Charge Rate is approaching its upper limit.\nCharge Rate: %f\n", measurement);
                break;
            default:
                break;
        }
    }
    else if (printLanguage == LANGUAGE_GERMAN)
    {
        switch(errCode)
        {
            case ERR_TEMPERATURE_TOO_LOW:
                printf("Die Temperatur liegt unter ihrem Grenzwert!\nTemperatur: %f\n", measurement);
                break;
            case ERR_TEMPERATURE_TOO_HIGH:
                printf("Die Temperatur liegt uber ihrem Grenzwert!\nTemperature: %f\n", measurement);
                break;
            case ERR_TEMPERATURE_LOW_WARNING:
                printf("Warnung: Die Temperatur nahert sich ihrem unteren Grenzwert.\nTemperatur: %f\n", measurement);
                break;
            case ERR_TEMPERATURE_HIGH_WARNING:
                printf("Warnung: Die Temperatur nahert sich ihrem oberen Grenzwert.\nTemperatur: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_TOO_LOW:
                printf("Der Ladezustand ist unter seinem Limit!\nLadezustand: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_TOO_HIGH:
                printf("Der Ladezustand liegt uber seinem Limit!\nLadezustand: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_LOW_WARNING:
                printf("Warnung: Der Ladezustand nahert sich seiner unteren Grenze.\nLadezustande: %f\n", measurement);
                break;
            case ERR_STATE_OF_CHARGE_HIGH_WARNING:
                printf("Warnung: Der Ladezustand nahert sich seiner Obergrenze.\nLadezustand: %f\n", measurement);
                break;
            case ERR_CHARGE_RATE_TOO_HIGH:
                printf("Die Laderate liegt uber dem Limit!\nLadestrom: %f\n", measurement);
                break;
            case ERR_CHARGE_RATE_HIGH_WARNING:
                printf("Warnung: Die Laderate nahert sich ihrer Obergrenze.\nLadestrom: %f\n", measurement);
                break;
            default:
                break;
        }
    }
}

int temperatureIsInRange(float temperature)
{
    int result = 1;
    int errCode = 0;
    if (temperature < TEMPERATURE_MIN_THRESHOLD)
    {
        errCode = ERR_TEMPERATURE_TOO_LOW;
        result = 0;
    }
    else if (temperature > TEMPERATURE_MAX_THRESHOLD)
    {
        errCode = ERR_TEMPERATURE_TOO_HIGH;
        result = 0;
    }
    // Early Warnings
    else if (temperature < TEMPERATURE_LOWER_WARNING_THRESHOLD)
    {
        errCode = ERR_TEMPERATURE_LOW_WARNING;
    }
    else if (temperature > TEMPERATURE_UPPER_WARNING_THRESHOLD)
    {
        errCode = ERR_TEMPERATURE_HIGH_WARNING;
    }
    printErrorMessage(errCode, temperature);
    return result;
}

int stateOfChargeIsInRange(float soc)
{
    int result = 1;
    int errCode = 0;
    if (soc < STATE_OF_CHARGE_MIN_THRESHOLD)
    {
        errCode = ERR_STATE_OF_CHARGE_TOO_LOW;
        result = 0;
    }
    else if (soc > STATE_OF_CHARGE_MAX_THRESHOLD)
    {
        errCode = ERR_STATE_OF_CHARGE_TOO_HIGH;
        result = 0;
    }
    // Early Warnings
    else if (soc < STATE_OF_CHARGE_LOWER_WARNING_THRESHOLD)
    {
        errCode = ERR_STATE_OF_CHARGE_LOW_WARNING;
    }
    else if (soc > STATE_OF_CHARGE_UPPER_WARNING_THRESHOLD)
    {
        errCode = ERR_STATE_OF_CHARGE_HIGH_WARNING;
    }
    printErrorMessage(errCode, soc);
    return result;
}

int chargeRateIsAboveLimit(float chargeRate)
{
    int result = 1;
    int errCode = 0;
    if (chargeRate > CHARGE_RATE_MAX_THRESHOLD)
    {
        errCode = ERR_CHARGE_RATE_TOO_HIGH;
        result = 0;
    }
    // Early Warning
    else if (chargeRate > CHARGE_RATE_UPPER_WARNING_THRESHOLD)
    {
        errCode = ERR_CHARGE_RATE_HIGH_WARNING;
    }
    printErrorMessage(errCode, chargeRate);
    return result;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int result = 0;
    if (temperatureIsInRange(temperature))
    {
        if (stateOfChargeIsInRange(soc))
        {
            if (chargeRateIsAboveLimit(chargeRate))
            {
                result = 1;
            }
        }
    }
    return result;
}

int main() {
    assert(!temperatureIsInRange(-0.1));
    assert(temperatureIsInRange(0));
    assert(temperatureIsInRange(0.1));
    assert(temperatureIsInRange(22));
    assert(temperatureIsInRange(44.9));
    assert(temperatureIsInRange(45));
    assert(!temperatureIsInRange(45.1));

    assert(!stateOfChargeIsInRange(19.9));
    assert(stateOfChargeIsInRange(20));
    assert(stateOfChargeIsInRange(20.1));
    assert(stateOfChargeIsInRange(50));
    assert(stateOfChargeIsInRange(79.9));
    assert(stateOfChargeIsInRange(80));
    assert(!stateOfChargeIsInRange(80.1));

    assert(chargeRateIsAboveLimit(0.7));
    assert(chargeRateIsAboveLimit(0.8));
    assert(!chargeRateIsAboveLimit(0.9));
    assert(chargeRateIsAboveLimit(0));
    assert(chargeRateIsAboveLimit(-1));

    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    assert(batteryIsOk(44, 79, 0.77));
    assert(batteryIsOk(1, 21, 0.76));

    printLanguage = LANGUAGE_GERMAN;
    assert(batteryIsOk(2.2, 23.9, 0.75));
    assert(!batteryIsOk(44.9, 79.9, 0.9));
}
