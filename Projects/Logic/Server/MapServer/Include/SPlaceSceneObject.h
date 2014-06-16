
/******************************************************************************/

#ifndef _SATKSCENEOBJECT_H_
#define _SATKSCENEOBJECT_H_

/******************************************************************************/

#include "MapServerPreqs.h"
#include "SSceneObject.h"

/******************************************************************************/

namespace MG
{
    /******************************************************************************/
    //  ���ǳ���������
    /******************************************************************************/
    class SPlaceSceneObject : public SSceneObject
    {
    public:
        SPlaceSceneObject();
        virtual ~SPlaceSceneObject();

        //-----------------------------------------------------------------------------------
        // Main
        //-----------------------------------------------------------------------------------

        virtual Bool                initialize();
        virtual Bool                unInitialize();
        virtual void                clear();
        virtual void                update(Flt delta);

		virtual GameType			getGameType();

        //-----------------------------------------------------------------------------------
        // Campaign
        //-----------------------------------------------------------------------------------

		void                        setCampaign( SCampaignInRegionPtr& ptr ){}
        void                        getSCampaign( SCampaignInRegionPtr& ptr ){}

    private:

		CampaignIdType			mCampaignId;			// ս��
		U64						mCampaignStartTime;		//��ʼս��ʱ��
        
    };

	/******************************************************************************/
	//����ˡ����ǵ�ͼ������ָ��
	/******************************************************************************/

	class SPlaceSceneObjectPtr : public SharedPtr<SPlaceSceneObject> 
	{
		friend class SPlaceSceneObjectFactory;
	public:

		SPlaceSceneObjectFactory* mFactory;

	public:

		virtual ~SPlaceSceneObjectPtr() { release(); }
		SPlaceSceneObjectPtr() : SharedPtr<SPlaceSceneObject>(),mFactory(NULL){}
		explicit SPlaceSceneObjectPtr(SPlaceSceneObject* rep) : SharedPtr<SPlaceSceneObject>(rep),mFactory(NULL){}
		SPlaceSceneObjectPtr(const SPlaceSceneObjectPtr& r) : SharedPtr<SPlaceSceneObject>(r),mFactory(r.mFactory) {} 

		SPlaceSceneObjectPtr& operator=(const SPlaceSceneObjectPtr& r) 
		{
			if (pRep == r.pRep)
				return *this;

			SPlaceSceneObjectPtr tmp(r);
			if ( isNull() == false )
			{
				tmp.mFactory = mFactory;
			}

			swap(tmp);

			mFactory = r.mFactory;

			return *this;
		}

	protected:

		virtual void    destroy(void){}

	};

}

#endif	