/*
   AirQuality library v1.0
   2010 Copyright (c) Seeed Technology Inc.  All right reserved.

   Original Author: Bruce.Qin

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */
#include "AirQualitySensor.h"

const int AirQualitySensor::FORCE_SIGNAL   = 0;
const int AirQualitySensor::HIGH_POLLUTION = 1;
const int AirQualitySensor::LOW_POLLUTION  = 2;
const int AirQualitySensor::FRESH_AIR      = 3;

AirQualitySensor::AirQualitySensor(int pin)
    : _pin(pin), _voltageSum(0), _volSumCount(0)
{
    // do nothing
}

bool AirQualitySensor::init(void)
{
    int initVoltage = analogRead(_pin);

    if (10 < initVoltage && initVoltage < 798)
    {
        _currentVoltage = initVoltage;
        _lastVoltage = _currentVoltage;

        _standardVoltage = initVoltage;
        _lastStdVolUpdated = millis();

        return true;
    }
    else {
        return false;
    }
}

int AirQualitySensor::slope(void)
{
    _lastVoltage = _currentVoltage;
    _currentVoltage = analogRead(_pin);

    _voltageSum += _currentVoltage;
    _volSumCount += 1;

    updateStandardVoltage();
    if (_currentVoltage - _lastVoltage > 400 || _currentVoltage > 700)
    {
        return AirQualitySensor::FORCE_SIGNAL;
    }
    else if ((_currentVoltage - _lastVoltage > 400 && _currentVoltage < 700)
             || _currentVoltage - _standardVoltage > 150)
    {
        return AirQualitySensor::HIGH_POLLUTION;
    }
    else if ((_currentVoltage - _lastVoltage > 200 && _currentVoltage < 700)
             || _currentVoltage - _standardVoltage > 50)
    {
        return AirQualitySensor::LOW_POLLUTION;
    }
    else {
        return AirQualitySensor::FRESH_AIR;
    }

    return -1;
}

int AirQualitySensor::getValue(void)
{
    return _currentVoltage;
}

void AirQualitySensor::updateStandardVoltage(void)
{
    if (millis() - _lastStdVolUpdated > 500000)
    {
        _standardVoltage = _voltageSum / _volSumCount;
        _lastStdVolUpdated = millis();

        _voltageSum = 0;
        _volSumCount = 0;
    }
}
