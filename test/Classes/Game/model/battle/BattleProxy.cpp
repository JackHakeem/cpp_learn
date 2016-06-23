//
//  BattleProxy.cpp
//  HLQS_IPAD
//
//  Created by hui long on 12-3-1.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "BattleProxy.h"

static BattleProxy * m_pBattleInstance = NULL;       

BattleProxy::BattleProxy()
{
    
}
BattleProxy::~BattleProxy()
{
    SAFE_DELETE(m_pBattleInstance);
}

BattleProxy * BattleProxy::getInstance()
{
    if(!m_pBattleInstance)
    {
        m_pBattleInstance = new BattleProxy();
    }
    return m_pBattleInstance;
}
