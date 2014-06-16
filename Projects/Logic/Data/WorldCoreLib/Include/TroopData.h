//*****************************************************************************************************
#ifndef _TROOPDATA_H
#define _TROOPDATA_H
//*****************************************************************************************************
#include "CharacterData.h"
//*****************************************************************************************************
namespace MG
{
    //*****************************************************************************************************
    //TroopData
    struct TroopData : public CharacterData
    { 	
        U32                mSoldierNum;      //ʿ������		

        //------------------------------------------------------------------------
        TroopData()
            :mSoldierNum(1)
        {
            
        }

        //------------------------------------------------------------------------
        TroopData& operator=(const TroopData& A)
        {
            if (this == &A)
            {
                return *this;
            }

            CharacterData::operator =(A);

            mSoldierNum  = A.mSoldierNum;

            return *this;
        }  

    };
}
//*****************************************************************************************************
#endif
//*****************************************************************************************************