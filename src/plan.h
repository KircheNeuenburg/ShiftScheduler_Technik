#ifndef PLAN_CLASS_H
#define PLAN_CLASS_H

#include <QObject>

#include "global.h"
#include "technician.h"
#include "shifttable.h"

class PLAN_CLASS
{
    public:
        quint64 numberOfDays;
        //quint64 numberOfShifts;
        //quint64 numberOfTechnicians;

        quint64 backtrackingDepth;
        quint64 backtrackingDepthMax;

        TECHNICIAN_CLASS nullTechnician;
        QList<QList<TECHNICIAN_CLASS>> shiftTable;
        QList<TECHNICIAN_CLASS> technicianList;
        QList<quint64> shiftList;

        qreal error;
        qreal errorMax;
        qreal meanShifts;
        quint64 indexMaxShifts;
        quint64 indexMinShifts;
        quint64 day_evo;
        quint64 shift_evo;
        quint64 startDay;

        ShiftTable m_excel;

        void createShiftTable(void);
        void deleteShiftTable(void);
        void createTechnicianList(void);
        void deleteTechnicianList(void);
        void createShiftList(quint64 numberOfShifts);
        void deleteShiftList(void);
        bool solvePlan(void);
        bool usedByShift(quint64 day, TECHNICIAN_CLASS technician);
        bool usedWeekBefore(quint64 day, TECHNICIAN_CLASS technician);
        bool usedWeekAfter(quint64 day, TECHNICIAN_CLASS technician);
        bool isNotCompetent(quint64 shift, TECHNICIAN_CLASS technician);
        bool isSafe(quint64 shift, quint64 day, TECHNICIAN_CLASS technician);
        bool findUnassigned(quint64 &day, quint64 &shift);

        bool evolution(void);
        bool nextGeneration(void);
        void killGeneration(void);
        void searchMinShifts(void);
        void searchMaxShifts(void);
        void searchRandom(quint64 &shift, quint64 &day,
                TECHNICIAN_CLASS technician);
        void calculateMaxError(void);

        void outputToFile(void);
        void readPreviousShifts(void);

        PLAN_CLASS(void);
        ~PLAN_CLASS(void);

};

#endif // !PLAN_CLASS_H
