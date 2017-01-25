#ifndef GLOBAL_H
#define GLOBAL_H

#include <QObject>
#include <QTextStream>

#include <QtXlsx>


#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <QString>
#include <math.h>
#include <limits>

#include "technician.h"

using namespace std;

typedef enum COMPETENCES_TYPE
{
    COMPUTER_CHURCH = 0x02,
    CAMERA_CHURCH = 0x04,
    AUDIO_CHURCH = 0x01,
    TECHNIC_VH = 0x08

} COMPETENCES_TYPE;

//QTextStream qout(stdout);

bool definitelyLessThan(qreal a, qreal b);


#endif // !GLOBAL_H
