#include "plan.h"

PLAN_CLASS::PLAN_CLASS(uint32_t days, uint32_t shifts, uint32_t technicians,
        uint32_t startDay)
        : numberOfDays(days), numberOfShifts(shifts), numberOfTechnicians(
                technicians), backtrackingDepth(0), backtrackingDepthMax(0), day_evo(
                0), shift_evo(0), startDay(startDay)
{
    createShiftTable();
    createTechnicianList();
    createShiftList();

    this->nullTechnician.setID(0);
    this->nullTechnician.setName("");
    this->nullTechnician.setCompetence(0);
}

PLAN_CLASS::~PLAN_CLASS(void)
{
    deleteShiftTable();
    deleteTechnicianList();
    deleteShiftList();
}

void PLAN_CLASS::createShiftTable(void)
{
    this->shiftTable = new TECHNICIAN_CLASS*[this->numberOfDays];

    for (uint32_t i = 0; i < this->numberOfDays; i++)
    {
        this->shiftTable[i] = new TECHNICIAN_CLASS[this->numberOfShifts];
    }
}

void PLAN_CLASS::deleteShiftTable(void)
{
    for (uint32_t i = 0; i < this->numberOfDays; i++)
    {
        delete[] this->shiftTable[i];
    }
    delete[] this->shiftTable;
}

void PLAN_CLASS::createTechnicianList(void)
{
    this->technicianList = new TECHNICIAN_CLASS[this->numberOfTechnicians];
}

void PLAN_CLASS::deleteTechnicianList(void)
{
    delete[] this->technicianList;
}

void PLAN_CLASS::createShiftList(void)
{
    this->shiftList = new COMPETENCES_TYPE[this->numberOfShifts];
    this->shiftList[0] = AUDIO_CHURCH;
    this->shiftList[1] = COMPUTER_CHURCH;
    this->shiftList[2] = CAMERA_CHURCH;
    this->shiftList[3] = TECHNIC_VH;
}

void PLAN_CLASS::deleteShiftList(void)
{
    delete[] this->shiftList;
}

bool PLAN_CLASS::solvePlan(void)
{
    uint32_t day = 0;
    uint32_t shift = 0;

    TECHNICIAN_CLASS activeTechnician;

    this->backtrackingDepth++;

    if (!findUnassigned(day, shift))
    {
        return true;
    }

    for (uint32_t tech_tmp = 0; tech_tmp < this->numberOfTechnicians;
            tech_tmp++)
    {
        activeTechnician = this->technicianList[tech_tmp];

        if (isSafe(shift, day, activeTechnician))
        {
            if (this->backtrackingDepth > this->backtrackingDepthMax)
            {
                printf("%d\n", this->backtrackingDepth);
                this->backtrackingDepthMax = this->backtrackingDepth;
            }
            this->shiftTable[day][shift] = activeTechnician;
            this->technicianList[tech_tmp].addShiftCount();
            if (solvePlan())
            {
                return true;
            }
            this->shiftTable[day][shift] = nullTechnician;
            this->technicianList[tech_tmp].subShiftCount();

        }
    }
    this->backtrackingDepth--;
    return false;

}

bool PLAN_CLASS::usedByShift(uint32_t day, TECHNICIAN_CLASS technician)
{
    for (uint32_t shift_tmp = 0; shift_tmp < this->numberOfShifts; shift_tmp++)
    {
        if (this->shiftTable[day][shift_tmp].getID() == technician.getID())
        {
            return true;
        }
    }
    return false;
}

bool PLAN_CLASS::usedWeekBefore(uint32_t day, TECHNICIAN_CLASS technician)
{
    if (day == 0)
    {
        return false;
    }

    for (uint32_t shift_tmp = 0; shift_tmp < this->numberOfShifts; shift_tmp++)
    {
        if (this->shiftTable[day - 1][shift_tmp].getID() == technician.getID())
        {
            return true;
        }
    }

    return false;
}

bool PLAN_CLASS::usedWeekAfter(uint32_t day, TECHNICIAN_CLASS technician)
{
    if (day == (numberOfDays - 1))
    {
        return false;
    }

    for (uint32_t shift_tmp = 0; shift_tmp < this->numberOfShifts; shift_tmp++)
    {
        if (this->shiftTable[day + 1][shift_tmp].getID() == technician.getID())
        {
            return true;
        }
    }

    return false;
}
bool PLAN_CLASS::isNotCompetent(uint32_t shift, TECHNICIAN_CLASS technician)
{
    if (technician.getCompetence() & (uint32_t) this->shiftList[shift])
    {
        return false;
    }
    return true;
}

bool PLAN_CLASS::isSafe(uint32_t shift, uint32_t day,
        TECHNICIAN_CLASS technician)
{
    if (isNotCompetent(shift, technician))
    {
        return false;
    }
    if (usedByShift(day, technician))
    {
        return false;
    }
    if (usedWeekBefore(day, technician))
    {
        return false;
    }
    if (usedWeekAfter(day, technician))
    {
        return false;
    }
    return true;

}

bool PLAN_CLASS::findUnassigned(uint32_t &day, uint32_t &shift)
{
    for (day = this->startDay; day < this->numberOfDays; day++)
    {
        for (shift = 0; shift < this->numberOfShifts; shift++)
        {
            if (this->shiftTable[day][shift].getID()
                    == this->nullTechnician.getID())
            {
                return true;
            }
        }
    }

    return false;
}

bool PLAN_CLASS::evolution(void)
{
    calculateMaxError();
    this->errorMax = this->error;
    for (uint32_t i = 0;
            i
                    < 10 * this->numberOfShifts * this->numberOfDays
                            * this->numberOfTechnicians; i++)
    {
        if (nextGeneration())
        {
            calculateMaxError();
        }
    }
//    for (uint32_t i = 0; i < 100000; i++)
//    {
//        if (nextGeneration())
//        {
//            calculateMaxError();
//
//            if (definitelyLessThan((float) this->error, (float) this->errorMax))
//            {
//                this->errorMax = this->error;
//            }
//            else
//            {
//                killGeneration();
//            }
//        }
//    }

    return true;
}

bool PLAN_CLASS::nextGeneration(void)
{
    searchMinShifts();
    searchMaxShifts();

    searchRandom(this->shift_evo, this->day_evo,
            this->technicianList[this->indexMaxShifts]);

    if (isSafe(this->shift_evo, this->day_evo,
            this->technicianList[this->indexMinShifts]))
    {
        this->shiftTable[this->day_evo][this->shift_evo] =
                this->technicianList[this->indexMinShifts];
        this->technicianList[this->indexMinShifts].addShiftCount();
        this->technicianList[this->indexMaxShifts].subShiftCount();

        return true;
    }

    return false;
}

void PLAN_CLASS::killGeneration(void)
{
    this->shiftTable[this->day_evo][this->shift_evo] =
            this->technicianList[this->indexMaxShifts];
    this->technicianList[this->indexMinShifts].subShiftCount();
    this->technicianList[this->indexMaxShifts].addShiftCount();
}

void PLAN_CLASS::searchMinShifts(void)
{
    do
    {
        this->indexMinShifts = rand() % this->numberOfTechnicians;
    }
    while (definitelyLessThan(this->meanShifts,
            this->technicianList[this->indexMinShifts].getShiftCount()));
}

void PLAN_CLASS::searchMaxShifts(void)
{
    do
    {
        this->indexMaxShifts = rand() % this->numberOfTechnicians;
    }
    while (definitelyLessThan(
            this->technicianList[this->indexMaxShifts].getShiftCount(),
            this->meanShifts));
}

void PLAN_CLASS::searchRandom(uint32_t &shift, uint32_t &day,
        TECHNICIAN_CLASS technician)
{
    uint32_t list_cnt = 0;
    uint32_t start_cnt = 0;
    uint32_t rand_index = 0;
    uint32_t** list = new uint32_t*[technician.getShiftCount()];

    for (uint32_t i = 0; i < technician.getShiftCount(); i++)
    {
        list[i] = new uint32_t[2];
    }

    for (uint32_t day_tmp = 0; day_tmp < this->numberOfDays; day_tmp++)
    {
        for (uint32_t shift_tmp = 0; shift_tmp < this->numberOfShifts;
                shift_tmp++)
        {
            if (this->shiftTable[day_tmp][shift_tmp].getID()
                    == technician.getID())
            {
                list[list_cnt][0] = day_tmp;
                list[list_cnt][1] = shift_tmp;
                list_cnt++;
                if (day_tmp < this->startDay)
                {
                    start_cnt++;
                }
            }
        }
    }

    do
    {
        rand_index = rand() % technician.getShiftCount();
    }
    while (rand_index < start_cnt);

    day = list[rand_index][0];
    shift = list[rand_index][1];

    for (uint32_t i = 0; i < technician.getShiftCount(); i++)
    {
        delete[] list[i];
    }
    delete[] list;
}

void PLAN_CLASS::calculateMaxError(void)
{
    double sumShifts = 0;
    double sumError = 0;

    this->meanShifts = 0;

    for (uint32_t i = 0; i < this->numberOfTechnicians; i++)
    {
        sumShifts += (double) this->technicianList[i].getShiftCount();
    }

    meanShifts = sumShifts / (double) numberOfTechnicians;

    for (uint32_t i = 0; i < this->numberOfTechnicians; i++)
    {
        sumError += fabs(
                (double) this->technicianList[i].getShiftCount()
                        - this->meanShifts);
    }

    this->error = sumError / (double) this->numberOfTechnicians;
}
