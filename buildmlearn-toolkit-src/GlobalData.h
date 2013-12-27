#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QString>


class GlobalData
{
public:
    static GlobalData* getInstance();
private:
    GlobalData();
    static GlobalData* instance;
    static bool instanceFlag;


public: //static
    static const QString IO_LD;
    static const QString IO_ILD;
};

#endif // GLOBALDATA_H


