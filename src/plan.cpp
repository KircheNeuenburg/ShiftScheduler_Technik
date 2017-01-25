#include "plan.h"

PLAN_CLASS::PLAN_CLASS(void)
        : backtrackingDepth(0), backtrackingDepthMax(0), day_evo(
                0), shift_evo(0)
{

    createShiftList(m_excel.getShifts());
    this->numberOfDays = m_excel.initDays();
    this->startDay = m_excel.initStartDay();

    createTechnicianList();
    createShiftTable();


    this->nullTechnician.setID(0);
    this->nullTechnician.setName((QString)"");
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

    QList<TECHNICIAN_CLASS> tmp_List;

    for(auto i=0;i<this->shiftList.size();i++)
    {
        tmp_List.append(this->nullTechnician);
    }



    for (auto i = 0; i < this->numberOfDays; i++)
    {
        this->shiftTable.append(tmp_List);
    }
}

void PLAN_CLASS::deleteShiftTable(void)
{

}

void PLAN_CLASS::createTechnicianList(void)
{

    this->technicianList = this->m_excel.initTechnicians();



}

void PLAN_CLASS::deleteTechnicianList(void)
{
    //delete[] this->technicianList;
}

void PLAN_CLASS::createShiftList(quint64 numberOfShifts)
{
    for (auto i = 0; i < numberOfShifts; i++)
    {
        this->shiftList.append(1 << i);
    }

}

void PLAN_CLASS::deleteShiftList(void)
{
    //delete[] this->shiftList;
}

bool PLAN_CLASS::solvePlan(void)
{
    quint64 day = 0;
    quint64 shift = 0;

    TECHNICIAN_CLASS activeTechnician;

    QList<TECHNICIAN_CLASS> tmpTechnicianList(this->technicianList);

    this->backtrackingDepth++;

    if (!findUnassigned(day, shift))
    {
        return true;
    }

    while (!tmpTechnicianList.isEmpty())
    {


        activeTechnician = tmpTechnicianList[rand() % tmpTechnicianList.size()];

        if (isSafe(shift, day, activeTechnician))
        {
            if (this->backtrackingDepth > this->backtrackingDepthMax)
            {
               this->backtrackingDepthMax = this->backtrackingDepth;
            }
            this->shiftTable[day][shift] = activeTechnician;

            this->technicianList[this->technicianList.indexOf(activeTechnician)].addShiftCount();
            if (solvePlan())
            {
                return true;
            }
            this->shiftTable[day][shift] = nullTechnician;
            this->technicianList[this->technicianList.indexOf(activeTechnician)].subShiftCount();

        }
        tmpTechnicianList.removeOne(activeTechnician);
    }
    this->backtrackingDepth--;
    return false;

}

bool PLAN_CLASS::usedByShift(quint64 day, TECHNICIAN_CLASS technician)
{
    for (quint64 shift_tmp = 0; shift_tmp < this->shiftList.size(); shift_tmp++)
    {
        if (this->shiftTable[day][shift_tmp].getID() == technician.getID())
        {
            return true;
        }
    }
    return false;
}

bool PLAN_CLASS::usedWeekBefore(quint64 day, TECHNICIAN_CLASS technician)
{
    if (day == 0)
    {
        return false;
    }

    for (quint64 shift_tmp = 0; shift_tmp < this->shiftList.size(); shift_tmp++)
    {
        if (this->shiftTable[day - 1][shift_tmp].getID() == technician.getID())
        {
            return true;
        }
    }

    return false;
}

bool PLAN_CLASS::usedWeekAfter(quint64 day, TECHNICIAN_CLASS technician)
{
    if (day == (numberOfDays - 1))
    {
        return false;
    }

    for (quint64 shift_tmp = 0; shift_tmp < this->shiftList.size(); shift_tmp++)
    {
        if (this->shiftTable[day + 1][shift_tmp].getID() == technician.getID())
        {
            return true;
        }
    }

    return false;
}
bool PLAN_CLASS::isNotCompetent(quint64 shift, TECHNICIAN_CLASS technician)
{
    if (technician.getCompetence() & (quint64) this->shiftList[shift])
    {
        return false;
    }
    return true;
}

bool PLAN_CLASS::isSafe(quint64 shift, quint64 day,
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

bool PLAN_CLASS::findUnassigned(quint64 &day, quint64 &shift)
{
    for (day = this->startDay; day < this->numberOfDays; day++)
    {
        for (shift = 0; shift < this->shiftList.size(); shift++)
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
    for (quint64 i = 0;
            i
                    < 10 * this->shiftList.size() * this->numberOfDays
                            * this->technicianList.size(); i++)
    {
        if (nextGeneration())
        {
            calculateMaxError();
        }
    }
    for (auto i = 0; i < 100000; i++)
    {
        if (nextGeneration())
        {
            calculateMaxError();

            if (definitelyLessThan((float) this->error, (float) this->errorMax))
            {
                this->errorMax = this->error;
            }
            else
            {
                killGeneration();
            }
        }
    }

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
        this->indexMinShifts = rand() % this->technicianList.size();
    }
    while (definitelyLessThan(this->meanShifts,
            this->technicianList[this->indexMinShifts].getShiftCount()));
}

void PLAN_CLASS::searchMaxShifts(void)
{
    do
    {
        this->indexMaxShifts = rand() % this->technicianList.size();
    }
    while (definitelyLessThan(
            this->technicianList[this->indexMaxShifts].getShiftCount(),
            this->meanShifts));
}

void PLAN_CLASS::searchRandom(quint64 &shift, quint64 &day,
        TECHNICIAN_CLASS technician)
{
    quint64 list_cnt = 0;
    quint64 start_cnt = 0;
    quint64 rand_index = 0;
    //quint64** list = new quint64*[technician.getShiftCount()];

    //for (quint64 i = 0; i < technician.getShiftCount(); i++)
    //{
    //    list[i] = new quint64[2];
    //}

    QList<QList<quint64>> list;
    for(auto i=0;i<technician.getShiftCount();i++)
    {
        QList<quint64> tmp;
        tmp.append(0);
        tmp.append(0);
        list.append(tmp);
    }

    for (quint64 day_tmp = 0; day_tmp < this->numberOfDays; day_tmp++)
    {
        for (quint64 shift_tmp = 0; shift_tmp < this->shiftList.size();
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

//    for (quint64 i = 0; i < technician.getShiftCount(); i++)
//    {
//        delete[] list[i];
//    }
//    delete[] list;
}

void PLAN_CLASS::calculateMaxError(void)
{
    qreal sumShifts = 0;
    qreal sumError = 0;

    this->meanShifts = 0;

    for (auto i = 0; i < this->technicianList.size(); i++)
    {
        sumShifts += (qreal) this->technicianList[i].getShiftCount();
    }

    meanShifts = sumShifts / (qreal) technicianList.size();

    for (auto i = 0; i < this->technicianList.size(); i++)
    {
        sumError += fabs(
                (qreal) this->technicianList[i].getShiftCount()
                        - this->meanShifts);
    }

    this->error = sumError / (qreal) this->technicianList.size();
}


void PLAN_CLASS::outputToFile(void)
{
    for (auto row = this->startDay; row < this->numberOfDays; row++)
    {
        for (auto col = 0; col < this->shiftList.size(); col++)
        {
            m_excel.fillTable(this->shiftTable[row][col].getName(),row,col);
        }
    }

    for(auto i=0; i < this->technicianList.count();i++)
    {
        auto technician = this->technicianList.at(i);
        m_excel.fillStats(i,technician.getName(),technician.getShiftCount());
    }
}


void PLAN_CLASS::readPreviousShifts(void)
{
    for (auto row = 0; row < this->numberOfDays - this->startDay; row++)
    {
        for (auto col = 0; col < this->shiftList.size(); col++)
        {
            QString name = m_excel.readTable(row,col);
            auto indexTechList = 0;
            TECHNICIAN_CLASS technician;
            foreach(technician,this->technicianList)
            {
                if(technician.getName() == name)
                {
                    indexTechList = this->technicianList.indexOf(technician);
                    this->technicianList[indexTechList].addShiftCount();
                    this->shiftTable[row][col] = this->technicianList.at(indexTechList);
                }
            }



        }
    }
}
