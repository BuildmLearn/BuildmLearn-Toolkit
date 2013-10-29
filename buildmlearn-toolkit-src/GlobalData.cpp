#include "GlobalData.h"

bool GlobalData::instanceFlag= false;
GlobalData* GlobalData::instance = 0;

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
