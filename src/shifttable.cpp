#include "shifttable.h"

ShiftTable::ShiftTable(QString excelSheet)
{
    m_excelSheet = new QXlsx::Document(excelSheet);
}


quint64 ShiftTable::getShifts(void)
{
    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();
    m_excelSheet->selectSheet("competences");

    auto tmp_maxShifts = 0;
    auto stop = false;

    for(auto i=2;i<1024 && stop == false;i++)
    {
        if(m_excelSheet->read(1,i).toString().isEmpty())
        {
            stop = true;
            tmp_maxShifts = i-2;
        }
    }

    m_excelSheet->selectSheet(tmp_sheet->sheetName());

    return tmp_maxShifts;
}

QList<TECHNICIAN_CLASS> ShiftTable::initTechnicians(void)
{

    QList<TECHNICIAN_CLASS> techList;
    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();
    m_excelSheet->selectSheet("competences");

    auto tmp_maxShiftsIndex = 0;
    auto tmp_maxTechniciansIndex = 0;
    auto stop = false;

    for(auto i=2;i<1024 && stop == false;i++)
    {
        if(m_excelSheet->read(1,i).toString().isEmpty())
        {
            stop = true;
            tmp_maxShiftsIndex = i-1;
        }
    }
    stop = false;

    for(auto i=2;i<1024 && stop == false;i++)
    {
        if(m_excelSheet->read(i,1).toString().isEmpty())
        {
            stop = true;
            tmp_maxTechniciansIndex = i-1;
        }
    }

    for(auto i = 2; i<= tmp_maxTechniciansIndex;i++)
    {
        TECHNICIAN_CLASS new_technician;

        new_technician.setName(m_excelSheet->read(i,1).toString());

        for(auto j=2; j<= tmp_maxShiftsIndex;j++)
        {
            if(!m_excelSheet->read(i,j).toString().isEmpty())
            {
                new_technician.setCompetence(new_technician.getCompetence() | (0x1 << (j-2)));
            }
        }

        new_technician.setID(i-1);

        techList.append(new_technician);

    }

    m_excelSheet->selectSheet(tmp_sheet->sheetName());
    return techList;


    m_excelSheet->selectSheet("schedule");

    auto tmp_maxFilledIndex = 0;
    auto tmp_maxDateIndex = 0;
    stop = false;

    for(auto i=2;i<1024 && stop == false;i++)
    {
        if(m_excelSheet->read(i,1).toString().isEmpty())
        {
            stop = true;
            tmp_maxDateIndex = i-1;
        }
    }
    stop = false;

    for(auto i=2;i<=tmp_maxDateIndex;i++)
    {
        for(auto j=2; j <= tmp_maxShiftsIndex && stop == false;j++)
        {

            if(!m_excelSheet->read(i,j).toString().isEmpty())
            {
                stop = true;
                tmp_maxFilledIndex++;
            }
        }
        stop = false;
    }




    m_excelSheet->selectSheet(tmp_sheet->sheetName());
}

quint64 ShiftTable::initDays()
{
    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();



    m_excelSheet->selectSheet("schedule");


    auto tmp_maxDateIndex = 0;
    auto stop = false;

    for(auto i=2;i<1024 && stop == false;i++)
    {
        if(m_excelSheet->read(i,1).toString().isEmpty())
        {
            stop = true;
            tmp_maxDateIndex = i-2;
        }
    }





    m_excelSheet->selectSheet(tmp_sheet->sheetName());
    return tmp_maxDateIndex;
}

quint64 ShiftTable::initStartDay()
{
    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();



    m_excelSheet->selectSheet("schedule");

    auto tmp_maxFilledIndex = 0;
    auto tmp_maxDateIndex = 0;
    auto stop = false;

    for(auto i=2;i<1024 && stop == false;i++)
    {
        if(m_excelSheet->read(i,1).toString().isEmpty())
        {
            stop = true;
            tmp_maxDateIndex = i-1;
        }
    }
    stop = false;

    auto tmp_maxShiftsIndex = getShifts() +1;
    for(auto i=2;i<=tmp_maxDateIndex;i++)
    {
        for(auto j=2; j <= tmp_maxShiftsIndex && stop == false;j++)
        {

            if(!m_excelSheet->read(i,j).toString().isEmpty())
            {
                stop = true;
                tmp_maxFilledIndex++;
            }
        }
        stop = false;
    }




    m_excelSheet->selectSheet(tmp_sheet->sheetName());
    return tmp_maxFilledIndex;
}


void ShiftTable::fillTable(QString technicianName, quint64 rowTable, quint64 colTable)
{
    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();
    m_excelSheet->selectSheet("schedule");
    QXlsx::Format format;
    format.setNumberFormat("yyyy-mm-dd");
    m_excelSheet->setColumnFormat(1,format);

    m_excelSheet->write(rowTable + 2, colTable + 2, technicianName);
    m_excelSheet->save();


    m_excelSheet->selectSheet(tmp_sheet->sheetName());

}

QString ShiftTable::readTable(quint64 rowTable, quint64 colTable)
{
    QString technicianName;

    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();
    m_excelSheet->selectSheet("schedule");


    technicianName = m_excelSheet->read(rowTable + 2, colTable + 2).toString();

    m_excelSheet->selectSheet(tmp_sheet->sheetName());

    return technicianName;
}

void ShiftTable::fillStats(quint64 index, QString technicianName, quint64 numberOfShifts)
{
    QXlsx::Worksheet* tmp_sheet = m_excelSheet->currentWorksheet();
    m_excelSheet->selectSheet("stats");

    m_excelSheet->write(index, 1, technicianName);
    m_excelSheet->write(index,2,numberOfShifts);
    m_excelSheet->save();

    m_excelSheet->selectSheet(tmp_sheet->sheetName());
}

