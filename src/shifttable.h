#ifndef SHIFTTABLE_H
#define SHIFTTABLE_H

#include "global.h"
#include <QObject>

class ShiftTable
{
public:
    QXlsx::Document* m_excelSheet;

    quint64 getShifts(void);
    QList<TECHNICIAN_CLASS> initTechnicians(void);
    quint64 initDays(void);
    quint64 initStartDay();
    void fillTable(QString technicianName, quint64 rowTable, quint64 colTable);
    QString readTable(quint64 rowTable, quint64 colTable);
    void fillStats(quint64 index, QString technicianName, quint64 numberOfShifts);

signals:
    void signal_addedTechnician(TECHNICIAN_CLASS technician);
    void signal_addedShift(QString name);

public:
    ShiftTable();
};

#endif // SHIFTTABLE_H
