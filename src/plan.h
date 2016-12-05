#ifndef PLAN_CLASS_H
#define PLAN_CLASS_H

#include "global.h"
#include "technician.h"

class PLAN_CLASS
{
    public:
        uint32_t numberOfDays;
        uint32_t numberOfShifts;
        uint32_t numberOfTechnicians;

        uint32_t backtrackingDepth;
        uint32_t backtrackingDepthMax;

        TECHNICIAN_CLASS nullTechnician;
        TECHNICIAN_CLASS** shiftTable;
        TECHNICIAN_CLASS* technicianList;
        COMPETENCES_TYPE* shiftList;

        double error;
        double errorMax;
        double meanShifts;
        uint32_t indexMaxShifts;
        uint32_t indexMinShifts;
        uint32_t day_evo;
        uint32_t shift_evo;
        uint32_t startDay;

        void createShiftTable(void);
        void deleteShiftTable(void);
        void createTechnicianList(void);
        void deleteTechnicianList(void);
        void createShiftList(void);
        void deleteShiftList(void);
        bool solvePlan(void);
        bool usedByShift(uint32_t day, TECHNICIAN_CLASS technician);
        bool usedWeekBefore(uint32_t day, TECHNICIAN_CLASS technician);
        bool usedWeekAfter(uint32_t day, TECHNICIAN_CLASS technician);
        bool isNotCompetent(uint32_t shift, TECHNICIAN_CLASS technician);
        bool isSafe(uint32_t shift, uint32_t day, TECHNICIAN_CLASS technician);
        bool findUnassigned(uint32_t &day, uint32_t &shift);

        bool evolution(void);
        bool nextGeneration(void);
        void killGeneration(void);
        void searchMinShifts(void);
        void searchMaxShifts(void);
        void searchRandom(uint32_t &shift, uint32_t &day,
                TECHNICIAN_CLASS technician);
        void calculateMaxError(void);

        PLAN_CLASS(uint32_t days, uint32_t shifts, uint32_t technicians,
                uint32_t startDay);
        ~PLAN_CLASS(void);

};

#endif // !PLAN_CLASS_H
