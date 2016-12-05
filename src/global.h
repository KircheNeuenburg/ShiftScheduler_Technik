#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <string>
#include <math.h>
#include <limits>

using namespace std;

typedef enum COMPETENCES_TYPE
{
    COMPUTER_CHURCH = 0x01,
    CAMERA_CHURCH = 0x02,
    AUDIO_CHURCH = 0x04,
    TECHNIC_VH = 0x08,
    COMPUTER_DUTYFREE = 0x10,
    AUDIO_DUTYFREE = 0x20,
    NO_AUDIO = 0x0B,
    ALL = 0xFF,
} COMPETENCES_TYPE;

bool definitelyLessThan(double a, double b);

#endif // !GLOBAL_H
