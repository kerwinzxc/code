//****************************************************************************************************
#include "stdafx.h"
#include "UIDelegate.h"
#include "UITest.h"
//****************************************************************************************************
namespace MG
{
    UIDelegate::UIDelegate()
    {

    }
    //-------------------------------------------------------------------------------
    UIDelegate::~UIDelegate()
    {

    }
    //-------------------------------------------------------------------------------
    bool UIDelegate::loadLayout()
    {
        if ( UITest::GetInstance().loadLayout() == false )
            return false;
        return true;
    }
}