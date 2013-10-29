#ifndef GLOBALDATA_H
#define GLOBALDATA_H

class GlobalData
{
public:
    static GlobalData* getInstance();
private:
    GlobalData();
    static GlobalData* instance;
    static bool instanceFlag;
};

#endif // GLOBALDATA_H


