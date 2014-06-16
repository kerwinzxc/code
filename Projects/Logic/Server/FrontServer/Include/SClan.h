/******************************************************************************/
#ifndef _SCLAN_H_
#define _SCLAN_H_
/******************************************************************************/
#include "FrontServerPreqs.h"
#include "Clan.h"
#include "SItemManager.h"
#include "SBuffManager.h"
#include "SPlayerCharacter.h"
#include "SClanQuestManager.h"
#include "GeneralRecruitSystem.h"
#include "SGameObjectFactory.h"
#include "IDBuilderManager.h"

/******************************************************************************/
namespace MG
{
    /******************************************************************************/
    //�������
    //��Ҫ���������µĽ�ɫ
	/******************************************************************************/
    class SClan : public Clan, public IDObject
    {
    public:

        SClan();
        virtual	~SClan();

	public:  

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                    initialize( ClanData& clanData );
        virtual Bool                    unInitialize();

        virtual void                    update(Flt delta);

        virtual void                    clear();

        //-----------------------------------------------------------------------------------
        // Debug
        //-----------------------------------------------------------------------------------

        //��ӡ��Ϣ
        void                            print();


		//------------------------------------------------------------------------------------
		//	PlayerCharactor
		//------------------------------------------------------------------------------------

        Bool                            addPlayerCharacter( SPlayerCharacterPtr& charPtr, PlayerCharacterData& charData );
        void                            removePlayerCharacter(PlayerCharacterIdType charId);
        Bool                            getPlayerCharacter(SPlayerCharacterPtr& charPtr, PlayerCharacterIdType charId);
        Bool                            hasPlayerCharacter(PlayerCharacterIdType charId);
        Bool                            hasPlayerCharacter();
        I32                             getPlayerCharacterCount();
        void                            removeAllPlayerCharacter();

		//���佫
        Bool                            getMainPlayerCharacter( SPlayerCharacterPtr& charPtr );
        void                            setMainPlayerCharacter( PlayerCharacterIdType charId );
		Bool                			checkMainGenreal();
	
		//��ʦ
		Bool							getWiseGenreal( SPlayerCharacterPtr& charPtr );
		void                            setWiseGenreal( PlayerCharacterIdType charId );
		Bool                			checkWiseGenreal();

		//ͳ��
		Bool							getCommanderGenreal( SPlayerCharacterPtr& charPtr );
		void                            setCommanderGenreal( PlayerCharacterIdType charId );
		Bool                			checkCommanderGenreal();

		//��ǰ��ͼ�佫
		Bool							getCurGenreal( SPlayerCharacterPtr& charPtr );
		void                            setCurGenreal( PlayerCharacterIdType charId );
		Bool                			checkCurGenreal();

        //------------------------------------------------------------------------------------
        //	Item
        //------------------------------------------------------------------------------------

		SItemManager*					getItemManager();

        //------------------------------------------------------------------------------------
        //	Buff
        //------------------------------------------------------------------------------------
		SBuffManager*					getSBuffManager();

		//-----------------------------------------------------------------------------------
		// GeneralRecruit
		//-----------------------------------------------------------------------------------

		GeneralRecruitSystem*           getGeneralRecruitSystem();

		//-----------------------------------------------------------------------------------
		// Quest
		//-----------------------------------------------------------------------------------

		// �������������
		SClanQuestManager*	            getQuestManager();


		//2014.06.01
		SPlayer* getParentPlayer(){ return mParentPlayer;};
		void setParentPlayer(SPlayer* _player){ mParentPlayer = _player;};

		NetIdType getClientNetId();
		
	private:
        // ��ɫ
        SPlayerCharacterFactory                                 mPlayerCharacterFactory;
        std::map<PlayerCharacterIdType,SPlayerCharacterPtr>     mPlayerCharacterMap;
        RWLocker                                                mPlayerCharacterMapCs;
	
		// ��Ʒ������
        SItemManager						mItemManager;	
		
		//buff������
		SBuffManager						mSBuffManager;

		// �������������
		SClanQuestManager					mQuestManager;

		//�佫��ļϵͳ
		GeneralRecruitSystem				mGeneralRecruitSystem;

		//��ɫID����������
		IDBuilderManager					mCharacterIDBuilderManager;
	
		SPlayer*							mParentPlayer;
    };


    /******************************************************************************/
    //Clan������ָ��
    /******************************************************************************/
    class SClanPtr : public SharedPtr<SClan> 
    {
        friend class SClanFactory;

    protected:

        SClanFactory* mFactory;

    public:

        virtual ~SClanPtr() { release(); }
        SClanPtr() : SharedPtr<SClan>(),mFactory(NULL){}
        explicit SClanPtr(SClan* rep) : SharedPtr<SClan>(rep),mFactory(NULL){}
        SClanPtr(const SClanPtr& r) : SharedPtr<SClan>(r),mFactory(r.mFactory) {} 

        SClanPtr& operator=(const SClanPtr& r) 
        {
            if (pRep == r.pRep)
                return *this;

            SClanPtr tmp(r);
            if ( isNull() == false )
            {
                tmp.mFactory = mFactory;
            }

            swap(tmp);

            mFactory = r.mFactory;

            return *this;
        }

    protected:

        virtual void    destroy(void);

    };


}
#endif