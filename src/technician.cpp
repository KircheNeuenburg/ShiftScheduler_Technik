#include "technician.h"

TECHNICIAN_CLASS::TECHNICIAN_CLASS(void)
        : id(0), name(""), competence(0), shiftCount(0)
{
}

TECHNICIAN_CLASS::TECHNICIAN_CLASS(uint32_t id)
        : id(id), name(""), competence(0), shiftCount(0)
{
}

TECHNICIAN_CLASS::TECHNICIAN_CLASS(uint32_t id, string name)
        : id(id), name(""), competence(0), shiftCount(0)
{
}

TECHNICIAN_CLASS::TECHNICIAN_CLASS(uint32_t id, string name,
        uint32_t competence)
        : id(id), name(name), competence(competence), shiftCount(0)
{
}

TECHNICIAN_CLASS::~TECHNICIAN_CLASS()
{

}

uint32_t TECHNICIAN_CLASS::getID(void)
{
    return this->id;
}

string TECHNICIAN_CLASS::getName(void)
{
    return this->name;
}

uint32_t TECHNICIAN_CLASS::getCompetence(void)
{
    return this->competence;
}

uint32_t TECHNICIAN_CLASS::getShiftCount(void)
{
    return this->shiftCount;
}

void TECHNICIAN_CLASS::setID(uint32_t id)
{
    this->id = id;
}

void TECHNICIAN_CLASS::setName(string name)
{
    this->name = name;
}

void TECHNICIAN_CLASS::setCompetence(uint32_t competence)
{
    this->competence = competence;
}

void TECHNICIAN_CLASS::setShiftCount(uint32_t count)
{
    this->shiftCount = count;
}

void TECHNICIAN_CLASS::addShiftCount(void)
{
    this->shiftCount++;
}

void TECHNICIAN_CLASS::subShiftCount(void)
{
    this->shiftCount--;
}

bool operator==(TECHNICIAN_CLASS a, TECHNICIAN_CLASS b)
{
    if (a.getID() == b.getID())
    {
        return true;
    }
    return false;
}
