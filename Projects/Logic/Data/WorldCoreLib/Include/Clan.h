/******************************************************************************/
#ifndef _CLAN_H_
#define _CLAN_H_
/******************************************************************************/

#include "WorldCorePreqs.h"
#include "CLuaBinder.h"

/******************************************************************************/

namespace MG
{
	/******************************************************************************/
	//�������һ���˺Ŷ�Ӧһ���������
	/******************************************************************************/
    //��������
    struct ClanData
    {
		AccountIdType				accountId;                 //�ʺ�ID
		ClanIdType					clanId;                    //����ID
		ClanTemplateIDType			ClanTemplateId;			   //����ģ��ID	
		CLAN_STATUS_TYPE      		status;                    //״̬
		UInt    					loginnum;                  //��½����
		U64     					createtime;                //����ʱ��
		U64     					deletetime;                //ɾ��ʱ��
		U64     					onlinetime;                //����ʱ��
		U64     					logintime;                 //��¼ʱ��
		U64     					logouttime;                //�ǳ�ʱ��
		Str16						clanHomeLandName;          //���忤����
        Str16						clanName;                  //������
		Str16						clanMainName;			   //�峤��
		UInt						clanLevel;				   //����ȼ�
		UInt						clanExp[4];				   //��ǰ���徭��
		UInt						clanMoney[16];				//��ǰ����ӵ�еĽ�Ǯ
		U8      					ConstellationId;           //�ػ�����
		U8      					armyemblem;                //���
		U8      					bg;                        //����ͼ��
		U8      					armyemblemcolor;           //�����ɫ	
		U8      					bgcolor;                   //������ɫ 
        PlayerCharacterIdType		mainGenrealId;             //���佫ID
		PlayerCharacterIdType		wiseGenrealId;             //��ʦID
		PlayerCharacterIdType		commanderGenrealId;        //ͳ��ID
		PlayerCharacterIdType		curGenrealId;              //��ǰ�佫ID
        RegionIdType				regionID;                  //��ǰ��ע�ĵ�ͼ���
		REGION_OBJ_TYPE				regionType;                //��ͼ���� 
        U32     					clanbagSize;               //���屳���Ĵ�С
		U32							clanGameMoney;
        
        ClanData()
            :accountId(0)         
			,clanId(0)              
			,ClanTemplateId(0)		
			,status(CLAN_STATUS_TYPE_NOMAL)              
			,loginnum(0)            
			,createtime(0)         
			,deletetime(0)          
			,onlinetime(0)          
			,logintime(0)           
			,logouttime(0)         	
			,clanLevel(1)						
			,ConstellationId(0)           
			,armyemblem(0)        
			,bg(0)                 
			,armyemblemcolor(0)   
			,bgcolor(0)            
			,mainGenrealId(0)     
			,wiseGenrealId(0)     
			,commanderGenrealId(0) 
			,curGenrealId(0)       
			,regionID(0)                    
			,clanbagSize(0)  
        {    
			for (UInt i=0; i<4; i++)
			{
				clanExp[i] = 0;
			}
			for (UInt i=0; i<16; i++)
			{
				clanMoney[i] = 0;
			}
        }

        ClanData& operator = (const ClanData& A)
        {
			accountId						= A.accountId;           
			clanId							= A.clanId;             
			ClanTemplateId					= A.ClanTemplateId;		
			status							= A.status;             
			loginnum						= A.loginnum;           
			createtime						= A.createtime;         
			deletetime						= A.deletetime;         
			onlinetime						= A.onlinetime;         
			logintime						= A.logintime;          
			logouttime						= A.logouttime;         
			clanHomeLandName				= A.clanHomeLandName;   
			clanName						= A.clanName;           
			clanMainName					= A.clanMainName;		
			clanLevel						= A.clanLevel;							
			ConstellationId					= A.ConstellationId;           
			armyemblem						= A.armyemblem;         
			bg								= A.bg;                 
			armyemblemcolor					= A.armyemblemcolor;    
			bgcolor							= A.bgcolor;            
			mainGenrealId					= A.mainGenrealId;      
			wiseGenrealId					= A.wiseGenrealId;      
			commanderGenrealId				= A.commanderGenrealId; 
			curGenrealId					= A.curGenrealId;       
			regionID						= A.regionID;           
			regionType						= A.regionType;         
			clanbagSize						= A.clanbagSize;  
			
			for (UInt i=0; i<4; i++)
			{
				clanExp[i] = A.clanExp[i];
			}
			for (UInt i=0; i<16; i++)
			{
				clanMoney[i] = A.clanMoney[i];
			}
           
            return *this;
        }
    };
    /******************************************************************************/
	class Clan : public CLuaReference
	{   
	public:
		Clan();
		virtual ~Clan();

		//@{
		//������Ϣ
        //��ü���������Ϣ
        ClanData*                   getData(){return &mClanData;}

        //��ü��������Ϣ
		ClanIdType			        getClanID();
		void			            setClanID(const ClanIdType& id);

        PlayerIdType			    getAccountID();
        void			            setAccountID(const PlayerIdType& id);

        PlayerCharacterIdType		getMainGenrealID();
        void			            setMainGenrealID(const PlayerCharacterIdType& id);

        IdType                      getFocusRegionID();
		REGION_OBJ_TYPE	            getFocusRegionType();
        void	                    setFocusRegionAttr( RegionIdType regionId, REGION_OBJ_TYPE regionType);

		Str16&	                    getName();
		void			            setName(const Char16*& name);
        void                        setName(const Str16& name);

        Str16&                      getClanHomeLandName();
        void                        setClanHomeLandName(const Char16*& homelandname);
        void                        setClanHomeLandName(const Str16& homelandname);

        U8                          getStatus();
        void	                    setStatus(const U8& status);

		//���ü���������Ϣ��һ��ֻ���ڶ�ȡ���ݿ�֮������
		void                        setData(ClanData* clandata);

    protected:

        //��ʼ����Ʒ��λ�Ĵ�С��
        void			            initItemSiteSize();
        
	    //��ӡ��Ϣ
		virtual		void			print();

	protected:

        ClanData mClanData;

		//ս���������
		U64		mLastCampaignTime;		//�ϴη���ս��ʱ��
		U64		mCampaignNumToday;		//�����Ѿ�����ս�۵Ĵ���
	};

}
#endif