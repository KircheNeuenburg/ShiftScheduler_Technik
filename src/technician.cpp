#include "technician.h"

TECHNICIAN_CLASS::TECHNICIAN_CLASS(void)
        : id(0), name(""), competence(0), shiftCount(0)
{
}

TECHNICIAN_CLASS::TECHNICIAN_CLASS(quint64 id)
        : id(id), name(""), competence(0), shiftCount(0)
{
}

TECHNICIAN_CLASS::TECHNICIAN_CLASS(quint64 id, QString name)
        : id(id), name(""), competence(0), shiftCount(0)
{
}

TECHNICIAN_CLASS::TECHNICIAN_CLASS(quint64 id, QString name,
        quint64 competence)
        : id(id), name(name), competence(competence), shiftCount(0)
{
}

TECHNICIAN_CLASS::~TECHNICIAN_CLASS()
{

}

quint64 TECHNICIAN_CLASS::getID(void)
{
    return this->id;
}

QString TECHNICIAN_CLASS::getName(void)
{
    return this->name;
}

quint64 TECHNICIAN_CLASS::getCompetence(void)
{
    return this->competence;
}

quint64 TECHNICIAN_CLASS::getShiftCount(void)
{
    return this->shiftCount;
}

void TECHNICIAN_CLASS::setID(quint64 id)
{
    this->id = id;
}

void TECHNICIAN_CLASS::setName(QString name)
{
    this->name = name;
}

void TECHNICIAN_CLASS::setCompetence(quint64 competence)
{
    this->competence = competence;
}

void TECHNICIAN_CLASS::setShiftCount(quint64 count)
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

bool TECHNICIAN_CLASS::operator==(TECHNICIAN_CLASS b)
{
    if (this->getID() == b.getID())
    {
        return true;
    }
    return false;
}
