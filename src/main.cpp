
#include <QCoreApplication>

#include "global.h"
#include "plan.h"
#include "shifttable.h"



#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <string>
#include <math.h>
#include <limits>
#include <time.h>



int main(int argc, char *argv[])
{

    if(argc == 0)
    {
        std::cout << "Error: No excelsheet was selected" << std::endl;
        return -1;
    }
    if(argc > 1)
    {
        std::cout << "Error: to many arguments" << std::endl;
        return -1;
    }




    PLAN_CLASS plan;



    plan.readPreviousShifts();

    if (plan.solvePlan())
    {
        std::cout << "Erfolg Backtrack Solver" << std::endl;


        if (plan.evolution())
        {
            std::cout << "Erfolg Evolution Solver" << std::endl;
            plan.outputToFile();


        }
        else
        {
            std::cout << "Fehler" << std::endl;

        }

    }
    else
    {
        std::cout << "Fehler" << std::endl;
    }

    return 0;
}

bool definitelyLessThan(qreal a, qreal b)
{
    return (b - a)
            > ((fabs(a) < fabs(b) ? fabs(b) : fabs(a))
                    * std::numeric_limits<qreal>::epsilon());
}

