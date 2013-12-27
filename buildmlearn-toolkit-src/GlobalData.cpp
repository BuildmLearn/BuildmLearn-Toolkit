#include "GlobalData.h"

bool GlobalData::instanceFlag= false;
GlobalData* GlobalData::instance = 0;

const QString GlobalData::IO_LD = "##L##"; // Input output line delimiter
const QString GlobalData::IO_ILD = "##IL##"; // Input output in-line delimiter

GlobalData::GlobalData()
{

}

GlobalData* GlobalData::getInstance()
{
    if(! instanceFlag)
    {
        instance = new GlobalData();
        instanceFlag = true;
        return instance;
    }
    else
    {
        return instance;
    }
}
