#ifndef TECHNICIAN_CLASS_H
#define TECHNICIAN_CLASS_H

#include "global.h"

class TECHNICIAN_CLASS
{
    private:

        uint32_t id;
        string name;
        uint32_t competence;
        uint32_t shiftCount;
    public:

        uint32_t getID(void);
        string getName(void);
        uint32_t getCompetence(void);
        uint32_t getShiftCount(void);
        void setID(uint32_t id);
        void setName(string name);
        void setCompetence(uint32_t competence);
        void setShiftCount(uint32_t count);
        void addShiftCount(void);
        void subShiftCount(void);

        TECHNICIAN_CLASS(void);
        TECHNICIAN_CLASS(uint32_t id);
        TECHNICIAN_CLASS(uint32_t id, string name);
        TECHNICIAN_CLASS(uint32_t id, string name, uint32_t competence);
        ~TECHNICIAN_CLASS();

};

#endif // !TECHNICIAN_CLASS_H
