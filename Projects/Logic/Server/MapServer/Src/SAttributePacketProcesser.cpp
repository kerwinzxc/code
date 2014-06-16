//*******************************************************************************************************
#include "stdafx.h"
#include "SAttributePacketProcesser.h"
#include "SWorldManager.h"
#include "SCharacter.h"
#include "MapServerMain.h"
#include "SFightMainManager.h"
#include "SSceneGridManager.h"
//*******************************************************************************************************
namespace MG
{
    MG::Bool SAttributePacketProcesser::processFrontServerPacket( I32 id, NetEventRecv* packet )
    {
        if ( packet->getChannel() == GNPC_ATTRIBUTE )
        {
            GameNetPacketData* data = (GameNetPacketData*)(packet->getData());

            switch (data->type)
            {
            case PT_ATTR_F2M_ATTR_LEVEL:
                recvUpLevel( id, (PT_ATTR_F2M_ATTR_LEVEL_DATA*)data->data );
                break;
            }

            return true;
        }
        return false;
    }
    //-----------------------------------------------------------------------------------------------
    void SAttributePacketProcesser::syncCharacterHPMPSPToClient( SCharacter* sender, SCharacter* master, Byte reducetype, UInt val, Byte resType, Int hateValue )
    {
		if(sender != master)
		{
			ATTACK_RESULT_TYPE resultType = (ATTACK_RESULT_TYPE)resType;
			if(resultType == ATTACK_RESULT_TYPE_HURT_CHANGE_RECOVER)
			{
				SFightMainManager::getInstance().addAndUpdateFightOnUseAuxiliarySkill(master, sender, hateValue);
			}
			else if(resultType == ATTACK_RESULT_TYPE_HURT)
			{
				SFightMainManager::getInstance().addAndUpdateFightOnUseAttackSkill(master, sender, hateValue);
			}
		}

        NetTranspondSendDataBufferPtr dataPtr  ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer(dataPtr,MG_GAME_NET_PACKET_BIG_MAX_SIZE);

        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
        if(packet)
        {
            packet->type = PT_ATTR_S2C_ATTR_HPMPSP;
            packet->channel = GNPC_ATTRIBUTE;

            PT_ATTR_S2C_ATTR_HPMPSP_DATA* sendData = (PT_ATTR_S2C_ATTR_HPMPSP_DATA*)packet->data;
            if(sendData)
            {
                sendData->damageType = reducetype;
                sendData->Id = sender->getID();
                sendData->val = val;
                sendData->objType = sender->getType();
                sendData->resultType = resType;
				sendData->hateVal = hateValue;
				sendData->masterId = master->getID();
				sendData->masterType = master->getType();
                SRegionObjectBase* regionObjectBase;// = sender->getCurrentRegionObject();

                if ( regionObjectBase )
				{
		//			NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, GameNetPacketData_INFO::headSize + PT_ATTR_S2C_ATTR_HPMPSP_INFO::dataSize, 
		//				master->getSceneObjectInSceneGridsManager()->currSceneGrid, NULL, regionObjectBase, 0);
				}
            }
        }
    }

    //-----------------------------------------------------------------------------------------------
    void SAttributePacketProcesser::sendCharacterDamageToFrontServer( SCharacter* sender, Byte reducetype, UInt val, Byte resType )
    {
        //����Ǿ��ӣ������͡�
        if ( sender->getType() !=  GOT_PLAYERCHARACTER ) return;

		SPlayerCharacter* senderCharacter = (SPlayerCharacter*)sender;
		NetIdType frontServerId = senderCharacter->getPlayerIdentifyInfo()->frontServerId;

        //�����ɫ���ˣ��ָ����������ᷢ�ʹ���Ϣ��
        if ( resType == ATTACK_RESULT_TYPE_HURT  ||  resType == ATTACK_RESULT_TYPE_RECOVER  ||  resType == ATTACK_RESULT_TYPE_DEAD )
            sendCharacterHPMPSPToFrontServer(frontServerId, sender, reducetype, val, resType);
    }

    //-----------------------------------------------------------------------------------------------
    void SAttributePacketProcesser::sendCharacterCureToFrontServer( SCharacter* sender, Byte reducetype, UInt val, Byte resType )
    {
        //����Ǿ��ӣ������͡�
        if ( sender->getType() !=  GOT_PLAYERCHARACTER ) return;

		SPlayerCharacter* senderCharacter = (SPlayerCharacter*)sender;
		NetIdType frontServerId = senderCharacter->getPlayerIdentifyInfo()->frontServerId;

        //����hp�� sp�� mp��
        sendCharacterHPMPSPToFrontServer(frontServerId, sender, reducetype, val, resType); 
    }

    //-----------------------------------------------------------------------------------------------
    void SAttributePacketProcesser::sendCharacterHPMPSPToFrontServer( NetIdType id, SCharacter* sender, Byte reducetype, UInt val, Byte resType )
    {
		if ( sender->getType() != GOT_PLAYERCHARACTER ) return;

        GameNetSendDataBufferPtr dataPtr;
        MapServerMain::getInstance().getServerLauncher()->getServerSendDataBuffer( dataPtr );

        GameNetPacketData* packet       = (GameNetPacketData*) dataPtr->getLogicData();
        if(packet)
        {
            packet->type = PT_ATTR_M2F_ATTR_HPMPSP;
            packet->channel = GNPC_ATTRIBUTE;

            PT_ATTR_M2F_ATTR_HPMPSP_DATA* sendData = (PT_ATTR_M2F_ATTR_HPMPSP_DATA*)packet->data;
            if(sendData)
            {
				sendData->accountId = sender->getAccountId();
                sendData->Id =  sender->getID();
                sendData->resultType = resType;
                sendData->damageType = reducetype;
                sendData->value = val;

				const Int dataSize = GameNetPacketData_INFO::headSize + PT_ATTR_M2F_ATTR_HPMPSP_DATA_INFO::dataSize;
				MapServerMain::getInstance().getServerLauncher()->sendServer(dataPtr, dataSize,id);
					
                //dataPtr->send(GameNetPacketData_INFO::headSize + PT_ATTR_M2F_ATTR_HPMPSP_DATA_INFO::dataSize, id);
            }
        }
    }
	//-----------------------------------------------------------------------------------------------
	void SAttributePacketProcesser::syncUpLevelToClient( SPlayerCharacter* pSPlayerCharacter, U32 level, Byte levelType )
	{
		NetTranspondSendDataBufferPtr dataPtr ;
        NetTranspondPacketProcesser::getInstance().getClientTranspondSendDataBuffer(dataPtr,MG_GAME_NET_PACKET_BIG_MAX_SIZE);

		GameNetPacketData* packet       = (GameNetPacketData*) dataPtr.getTranspondData();
		if(packet)
		{
			packet->type = PT_ATTR_M2C_ATTR_LEVEL;
			packet->channel = GNPC_ATTRIBUTE;

			PT_ATTR_M2C_ATTR_LEVEL_DATA* sendData = (PT_ATTR_M2C_ATTR_LEVEL_DATA*)packet->data;
			if(sendData)
			{
				sendData->accountId = pSPlayerCharacter->getAccountId();
				sendData->charId	= pSPlayerCharacter->getID();
				sendData->levelType = levelType;
				sendData->level		= level;
				sendData->hp		= pSPlayerCharacter->getHp();
				sendData->hpMax		= pSPlayerCharacter->getMaxHp();
				sendData->mp		= pSPlayerCharacter->getMp();
				sendData->mpMax		= pSPlayerCharacter->getMaxMp();

				SRegionObjectBase* tempRegion;// = pSPlayerCharacter->getCurrentRegionObject();

				if ( tempRegion )
				{
					Int dataSize = GameNetPacketData_INFO::headSize + PT_ATTR_M2C_ATTR_LEVEL_DATA_INFO::dataSize;
					NetTranspondPacketProcesser::getInstance().broadcastClientTranspondPackToFrontServer(dataPtr, dataSize, tempRegion);
				}
			}
		}
	}
	//-----------------------------------------------------------------------------------------------
	void SAttributePacketProcesser::recvUpLevel( I32 id, PT_ATTR_F2M_ATTR_LEVEL_DATA* pData )
	{
		SPlayerCharacter* pSPlayerCharacter = NULL;//SWorldManager::getInstance().getPlayerCharacterFromMemory(pData->charId);
		DYNAMIC_ASSERT(pSPlayerCharacter);
		
		//ֻ����ת���ȼ���ս���ȼ���
		//Ŀǰֻ����ս���ȼ���
		pSPlayerCharacter->setLevel(pData->level);
		syncUpLevelToClient(pSPlayerCharacter, pData->level, pData->levelType);
	}
}