#include "common.h"
#include "Component.h"

int num = 0;
int ClassManager::GetNewId()
{
    return num++;
}
