/*
 * mString.cpp
 *
 *  Created on: 21 дек. 2021 г.
 *      Author: ARHIN
 */

#include "mString.h"


char* mUtoa(Uint32 value, char *buffer, bool clear)
{
    buffer += 11;
    if (clear)
        *--buffer = 0;
    do
    {
        *--buffer = value % 10 + '0';
        value /= 10;
    }
    while (value != 0);
    return buffer;
}

char* mLtoa(int32 value, char *buffer, bool clear)
{
    bool minus = value < 0;
    if (minus)
        value = -value;
    buffer = mUtoa(value, buffer, clear);
    if (minus)
        *--buffer = '-';
    return buffer;
}

char* mFtoa(double value, Uint16 decimals, char *buffer)
{
    int32 mant = (int32) value;
    value -= mant;
    Uint32 exp = 1;
    while (decimals--)
        exp *= 10;
    exp *= (float) value;
    buffer = ltoa(mant, buffer, DEC);
    char len = strlen(buffer);
    *(buffer + len++) = '.';
    ltoa(exp, buffer + len++, DEC);
    return buffer;
}
