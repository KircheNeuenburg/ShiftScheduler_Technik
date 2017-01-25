#ifndef TECHNICIAN_CLASS_H
#define TECHNICIAN_CLASS_H

#include <QObject>
#include "global.h"

class TECHNICIAN_CLASS
{

    private:

        quint64 id;
        QString name;
        quint64 competence;
        quint64 shiftCount;
    public:

        quint64 getID(void);
        QString getName(void);
        quint64 getCompetence(void);
        quint64 getShiftCount(void);
        void setID(quint64 id);
        void setName(QString name);
        void setCompetence(quint64 competence);
        void setShiftCount(quint64 count);
        void addShiftCount(void);
        void subShiftCount(void);

        TECHNICIAN_CLASS(void);
        TECHNICIAN_CLASS(quint64 id);
        TECHNICIAN_CLASS(quint64 id, QString name);
        TECHNICIAN_CLASS(quint64 id, QString name, quint64 competence);
        ~TECHNICIAN_CLASS();

        bool operator==(TECHNICIAN_CLASS b);

};

#endif // !TECHNICIAN_CLASS_H
