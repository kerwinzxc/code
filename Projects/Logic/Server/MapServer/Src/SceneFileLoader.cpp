
/******************************************************************************/
#include "stdafx.h"
#include "SceneFileLoader.h"
#include "GameFileDefine.h"
//#include "MapResourceInfo.h"
#include "PointTemplate.h"

/******************************************************************************/
//#define ATTACKER_BORN	"AttackerBorn"
//#define DEFENSER_BORN	"DefenserBorn"
//
//#define ATTACKER_BUILDING_BORN	"AttackerBuidingBorn"
//#define DEFENSER_BUILDING_BORN	"DefenserBuidingBorn"
//
//#define NORMAL_JUMP			"NORMAL"
//
//#define JUMP_POINT			"Point"	//��ת��

#define SCENE_XML		"Scene.xml"


/******************************************************************************/
namespace MG
{
	/******************************************************************************/
	SceneFileObject::SceneFileObject()
		:id(0)
	{
		memset(pathName, 0, sizeof(pathName));
	}

	void SceneFileObject::addStaticList(StaticObjectXml* staticObj)
	{
		mStaticList.push_back(*staticObj);
	}	

	void SceneFileObject::addNormalJumpPos(PointXml* point)
	{
		mRpgNormalJumpPos.push_back(*point);
	}

	void SceneFileObject::addTranslatePos(PointXml* point)
	{
		mRpgTranslatePos.push_back(*point);
	}

	void SceneFileObject::addRelivePos(PointXml* point)
	{
		mRpgRelivePos.push_back(*point);
	}

	void SceneFileObject::addCampAttackPos(CampInfoXml* campInfo)
	{
		campAttackerPos.push_back(*campInfo);
	}

	void SceneFileObject::addCampDefenserPos(CampInfoXml* campInfo)
	{
		campDefenserPos.push_back(*campInfo);
	}

	void SceneFileObject::addAttackerGeneralPos(PointXml* point)
	{
		mSlgAttackerGeneralPos.push_back(*point);
	}

	void SceneFileObject::addDefenserGeneralPos(PointXml* point)
	{
		mSlgDefenserGeneralBornPos.push_back(*point);
	}

	void SceneFileObject::addAttackerTroopPos(PointXml* point)
	{
		mSlgAttackerTroopBornPos.push_back(*point);
	}

	void SceneFileObject::addDefenserTroopPos(PointXml* point)
	{
		mSlgDefenserTroopBornPos.push_back(*point);
	}
	
	void SceneFileObject::addAttackerCampBornPos(PointXml* point)
	{
		mSlgAttackerCampBornPos.push_back(*point);
	}

	void SceneFileObject::addDefenserCampBornPos(PointXml* point)
	{
		mSlgDefenserCampBornPos.push_back(*point);
	}	

	void SceneFileObject::addAttackerGeneralRelivePos(PointXml* point)
	{
		mSlgAttackerGeneralRelivePos.push_back(*point);
	}

	void SceneFileObject::addDefenserGeneralRelivePos(PointXml* point)
	{
		mSlgDefenserGeneralRelivePos.push_back(*point);
	}

	void SceneFileObject::addThirdPartCharacter(ThirdPartCharacterInfoXml* thirdPartCharacter)
	{
		thirdPartCharacterList.push_back(*thirdPartCharacter);
	}

	void SceneFileObject::addMonsterInfo(MonsterInfoXml* monster)
	{
		mMonsterList.push_back(*monster);
	}

	void SceneFileObject::addPlaceInfo(PlaceInfoXml* place)
	{
		mPlaceList.push_back(*place);
	}

	void SceneFileObject::addNPCInfo(NPCInfoXml* npc)
	{
		mNpcList.push_back(*npc);
	}

	void SceneFileObject::addBuildingInfo(BuildingInfoXml* building)
	{
		mBuildingList.push_back(*building);
	}

	PointXml SceneFileObject::getRandAlivePoint()
	{
		Int Num = mRpgRelivePos.size();

		if (0 == Num)
		{
			DEBUG_ASSERT_LOG(0,"�����Ϊ��");
		}
		if (Num == 1)
		{
			return (mRpgRelivePos.at(0));
		}

		Int index = rand()%(Num-1);
		return (mRpgRelivePos.at(index));
	}

	PointXml SceneFileObject::getRandNormalJumpPoint()
	{
		Int Num = mRpgNormalJumpPos.size();

		if (0 == Num)
		{
			DEBUG_ASSERT_LOG(0,"��ת��Ϊ��");
		}
		if (Num == 1)
		{
			return (mRpgNormalJumpPos.at(0));
		}

		Int index = rand()%(Num-1);
		return (mRpgNormalJumpPos.at(index));
	}

	PointXml SceneFileObject::getCampaignCampPos(FORCE force, Int pointId)
	{
		std::vector<PointXml>* campPosList = NULL;
		if (FORCE_ATTACK == force)
		{
			campPosList = &mSlgAttackerCampBornPos;
		}
		else if(FORCE_DEFENSE == force)
		{
			campPosList =  &mSlgDefenserCampBornPos;
		}
		else
		{
			DEBUG_ASSERT_LOG(0, "SceneFileObject::getCampaignCampPos force����");
		}

		DYNAMIC_ASSERT(NULL != campPosList && POSITION_MAX == campPosList->size());

		for (std::vector<PointXml>::iterator iter = campPosList->begin(); iter != campPosList->end(); ++iter)
		{
			if (pointId == iter->PointId)
			{
				return (*iter);
			}
		}

		return PointXml();
	}

	PointXml SceneFileObject::getCampaignTroopPos(FORCE force, Int pointId)
	{
		std::vector<PointXml>* troopPosList = NULL;
		if (FORCE_ATTACK == force)
		{
			troopPosList = &mSlgAttackerTroopBornPos;
		}
		else if(FORCE_DEFENSE == force)
		{
			troopPosList =  &mSlgDefenserTroopBornPos;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		//DYNAMIC_ASSERT(NULL != troopPosList && POSITION_MAX == troopPosList->size());

		for (std::vector<PointXml>::iterator iter = troopPosList->begin(); iter != troopPosList->end(); ++iter)
		{
			if (pointId == iter->PointId)
			{
				return (*iter);
			}
		}

		return PointXml();
	}

	PointXml SceneFileObject::getCampaignCampPosByForce(FORCE force, Int index)
	{
		std::vector<PointXml>* campPosList = NULL;
		if (FORCE_ATTACK == force)
		{
			campPosList = &mSlgAttackerCampBornPos;
		}
		else if(FORCE_DEFENSE == force)
		{
			campPosList =  &mSlgDefenserCampBornPos;
		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

		DYNAMIC_ASSERT(NULL != campPosList && POSITION_MAX == campPosList->size());

		return (campPosList->at(index));
	}

	PointXml SceneFileObject::getJumpPosFromSceneFileObj(JUMP_TYPE jumpType, Byte jumpIndex,Int pointId)
	{
		switch(jumpType)
		{

		case JUMP_NORMAL:
			{
				if (0 == pointId)
				{
					//���ѡһ��λ��
					return getRandNormalJumpPoint();
				}
				else
				{
					//�����ת�� �����ѡһ��
					std::vector<PointXml> outPointList;
					getNormalJumpPointListByPointId(&outPointList, pointId);
					Int posNum = (Int)outPointList.size();
					if (0 == posNum)
					{
						DEBUG_ASSERT_LOG(0,"����� Ϊ�� 0 == posNum");
						assert(0);
						return PointXml();
					}
					if (posNum == 1)
					{
						return (outPointList.at(0));
					}

					Int index = rand()%(posNum-1);
					return (outPointList.at(index));
				}
			}
			break;

		case JUMP_BORN:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		case JUMP_ATTACK:
			{
				DYNAMIC_ASSERT(jumpIndex >= 0 && jumpIndex < POSITION_MAX);
				DYNAMIC_ASSERT(POSITION_MAX == mSlgAttackerGeneralPos.size());
				return (mSlgAttackerGeneralPos.at(jumpIndex));
			}
			break;
		case JUMP_DEFENSE:
			{
				DYNAMIC_ASSERT(jumpIndex >= 0 && jumpIndex < POSITION_MAX);
				DYNAMIC_ASSERT(POSITION_MAX == mSlgDefenserGeneralBornPos.size());
				return (mSlgDefenserGeneralBornPos.at(jumpIndex));
			}
			break;
		default:
			{
				DYNAMIC_ASSERT(0);
			}
			break;
		}
		return PointXml();
	}

	void SceneFileObject::getNormalJumpPointListByPointId(std::vector<PointXml>* outPointList, const Int pointId)
	{
		if (mRpgNormalJumpPos.empty())
		{
			DEBUG_ASSERT_LOG(0,"sceneFileObj->normalJumpPos.empty()");
			assert(0);
			return;
		}

		for (std::vector<PointXml>::iterator iter = mRpgNormalJumpPos.begin(); iter != mRpgNormalJumpPos.end(); ++iter)
		{
			if (iter->PointId == pointId)
			{
				outPointList->push_back(*iter);
			}
		}

		DYNAMIC_ASSERT(outPointList->empty() == false);
	}

	/******************************************************************************/
	SceneFileLoader::SceneFileLoader()
	{
		mSceneXmlDoc	= MG_NEW tinyxml2::XMLDocument;
	}

	//-----------------------------------------------------------------------
	SceneFileLoader::~SceneFileLoader()
	{
		MG_SAFE_DELETE( mSceneXmlDoc );
		for (listSceneFileObjectIter iter = mListSceneFileObject.begin(); iter != mListSceneFileObject.end(); ++iter)
		{
			if (*iter)
			{
				MG_SAFE_DELETE(*iter);
			}
		}
		mListSceneFileObject.clear();
	}

	//-----------------------------------------------------------------------
	SceneFileObject* SceneFileLoader::getSceneFileObjectByPath(CChar16* path)
	{
		return NULL;
#if 0
		if(NULL == path)
		{
			return NULL;
		}
		//�Ƿ��ȡ�����ļ��� ����ֱ�ӷ���
		SceneFileObject* sceneFileObject = findSceneFileObjectByPath(path);
		if (NULL != sceneFileObject)
		{
			return sceneFileObject;
		}

		//��Ҫ��ȡ
		SceneFileObject* newSceneFileObject = MG_NEW SceneFileObject();
		wcscpy_s(newSceneFileObject->pathName, MAX_ART_MAP_RES_PATH_NAME, path);
		

		//ת��·���ĸ�ʽ
		std::string strPath;
		MGStrOp::toString(path, strPath);

		std::string strSceneFilePath = strPath + "\\" + SCENE_XML;

		//ͨ�����������Ӧ��Ϣ
		loadSceneFile(strSceneFilePath.c_str(),newSceneFileObject);

		mListSceneFileObject.push_back(newSceneFileObject);
		return newSceneFileObject;
#endif
	}

	//-----------------------------------------------------------------------
	SceneFileObject* SceneFileLoader::findSceneFileObjectByPath(CChar16* path)
	{
		for (listSceneFileObjectIter iter = mListSceneFileObject.begin(); iter != mListSceneFileObject.end(); ++iter)
		{
			SceneFileObject* sceneFile = *iter;
			if (0 == wcscmp(sceneFile->pathName, path))
			{
				return sceneFile;
			}
		}

		return NULL;
	}

	//-----------------------------------------------------------------------
	void SceneFileLoader::loadSceneFile(CChar8* path, SceneFileObject* object)
	{
		std::string path_str = path;
		if ( mSceneXmlDoc->LoadFile(path_str.c_str()) != XML_NO_ERROR )
		{
			//// MG_CN_MODIFY
			//IMGFileSystem *packManager = EngineMain::getInstance().getfileSystem();
			//if (packManager)
			//{				
			//	MG::MGDataCharStream charStream = packManager->getFileChar(path);
			//	if (mSceneXmlDoc->LoadFile(charStream.buffer, charStream.size) != XML_NO_ERROR)
			//	{
			//		MG_MESSAGE("SceneFileLoader::loadSceneFile Error!");
			//		DYNAMIC_ASSERT(false);
			//		return;
			//	}
			//}
			//else
			//{
			//	MG_MESSAGE("SceneFileLoader::loadSceneFile Error!");
			//	DYNAMIC_ASSERT(false);
			//	return;
			//}
		}

		Str8 version; 
		XMLElement* rootElm = mSceneXmlDoc->RootElement();
		if (rootElm)
		{
			version = XML_GET_ATTRIBUTE(rootElm,"Version");

			//create component
			{
				XMLNode* parentNode       = rootElm;
				XMLNode* currNode         = parentNode->FirstChild();
				XMLNode* firstSiblingNode = currNode;
				XMLNode* nextNode         = NULL;

				while( currNode )
				{
					//TODO:
					std::string formatType = XML_GET_VALUE(currNode);

					if (formatType == "EntityGroup")
					{
						loadEntityGroup(currNode->ToElement(),object);
					}

					//@ parallel 
					nextNode    = currNode->NextSibling();
					if (nextNode&&nextNode==firstSiblingNode)
					{
						break;
					}
					currNode = nextNode;
				}
			}
		}
	}

	//-----------------------------------------------------------------------
	void SceneFileLoader::loadEntityGroup(XMLElement * groupElm, SceneFileObject* object)
	{
		XMLNode* parentNode       = groupElm;
		XMLNode* currNode         = parentNode->FirstChild();
		XMLNode* firstSiblingNode = currNode;
		XMLNode* nextNode         = NULL;

		while( currNode )
		{
			loadEntity(currNode->ToElement(),object);

			//@ parallel 
			nextNode    = currNode->NextSibling();
			if (nextNode&&nextNode==firstSiblingNode)
			{
				break;
			}
			currNode = nextNode;
		}
	}

	//-----------------------------------------------------------------------
	Bool SceneFileLoader::isFocusEntityGroup(Str group)
	{
		if (group.empty())
		{
			return false;
		}

		if ( group == SCENE_OBJECT_GROUP_STR_STATIC || 
			 group == SCENE_OBJECT_GROUP_STR_PLACE ||
			 group == SCENE_OBJECT_GROUP_STR_POINT || 
			 group == SCENE_OBJECT_GROUP_STR_NPC || 
			 group == SCENE_OBJECT_GROUP_STR_MONSTER || 
			 group == SCENE_OBJECT_GROUP_STR_TROOP || 
			 group == SCENE_OBJECT_GROUP_STR_REGION || 
			 group == SCENE_OBJECT_GROUP_STR_BUILDING )
		{
			return true;
		}

		return false;
	}

	//-----------------------------------------------------------------------
	void SceneFileLoader::loadEntity(XMLElement * elm, SceneFileObject* object)
	{
		//����
		Str8 groupName;
		XmlHelper::getAttribute( elm, groupName, "Group" );
		
		if ( isFocusEntityGroup(groupName) == false )
		{
			return;
		}

		//λ��
		Vec3 pos;
		Vec3XmlFormat::load(elm, "Position", pos);
		
		//����
		Vec4 orientation = Vec4(1,0,0,0);
		Vec4XmlFormat::load(elm, "Orientation", orientation);

		//���ط�ʽ
		Byte appearType = 0;
		XMLElement* childAttr = XmlHelper::getChild(elm, "AppearParam");
		if ( childAttr )
		{
			XmlHelper::getAttribute(childAttr, appearType, "Value");
		}

		std::map<Str,Str> customAttr;
		// �Զ������
		{
			XMLElement* customAttrs = XmlHelper::getChild(elm, "CustomAttrs");
			if (customAttrs)
			{
				XMLNode* parentNode       = customAttrs;
				XMLNode* currNode         = parentNode->FirstChild();
				XMLNode* firstSiblingNode = currNode;
				XMLNode* nextNode         = NULL;

				while( currNode )
				{
					//TODO:
					std::string formatType  = XML_GET_VALUE(currNode);
					std::string attr        = XML_GET_ATTRIBUTE(currNode->ToElement(),"Value");

					customAttr[formatType] = attr;

					//@ parallel 
					nextNode    = currNode->NextSibling();
					if (nextNode&&nextNode==firstSiblingNode)
					{
						break;
					}
					currNode = nextNode;
				}
			}
		}

		loadEntity((CharAppearType)appearType, groupName,pos,orientation, customAttr,object);
	}

	//-----------------------------------------------------------------------
	void SceneFileLoader::loadEntity(CharAppearType appearType, const Str& group, const Vec3& pos, const Vec4& orientation, std::map<Str,Str>& customAttr, SceneFileObject* object)
	{
		DYNAMIC_ASSERT(appearType < CAT_SLG_SCENE_MAX);

		const Vec3 dir = orientation.quaternionCross(Vec3(0,0,-1));

		if (group == SCENE_OBJECT_GROUP_STR_STATIC)
		{
			StaticObjectXml tempStaticObj;
			tempStaticObj.pos = pos;
			//tempStaticObj.templateId = templateId;
			object->addStaticList(&tempStaticObj);
			
		}
		else if(group == SCENE_OBJECT_GROUP_STR_PLACE)
		{
			PlaceInfoXml tempPlace;
			tempPlace.pos = pos;
			object->addPlaceInfo(&tempPlace);
		}
		else if(group == SCENE_OBJECT_GROUP_STR_POINT)
		{
			PointXml tempJumpPoint;
			tempJumpPoint.pos = pos;
			tempJumpPoint.dir = dir;
			
			//��ȡ PointID
			{
				std::map<Str,Str>::iterator iterPointId= customAttr.find("PointID");
				if (iterPointId != customAttr.end())
				{
					MGStrOp::toI32(iterPointId->second.c_str(), tempJumpPoint.PointId);
					DYNAMIC_ASSERT(tempJumpPoint.PointId > 0);
				}
			}
			
			//��ȡ UseType
			{
				int useType;
				std::map<Str,Str>::iterator iterUseType = customAttr.find("UseType");
				if (iterUseType != customAttr.end())
				{
					MGStrOp::toI32(iterUseType->second.c_str(), useType);
				}

				switch(useType)
				{
				case point_rpg_jump_in:		//�����
				case point_rpg_jump_out:	//������
					{
						object->addNormalJumpPos(&tempJumpPoint);
					}
					break;
				case point_rpg_translate:	//���͵�
					{
						object->addTranslatePos(&tempJumpPoint);
					}
					break;
				case point_rpg_revive:		//�����
					{
						object->addRelivePos(&tempJumpPoint);
					}
					break;
				case point_slg_born_attacker_general:	//���������������
					{
						object->addAttackerGeneralPos(&tempJumpPoint);
					}
					break;
				case point_slg_born_attacker_troop:		//���������ӳ�����
					{
						object->addAttackerTroopPos(&tempJumpPoint);
					}
					break;
				case point_slg_born_defender_general:	//���ط����������
					{
						object->addDefenserGeneralPos(&tempJumpPoint);
					}
					break;
				case point_slg_born_defender_troop:		//���ط����ӳ�����
					{
						object->addDefenserTroopPos(&tempJumpPoint);
					}
					break;
				case point_slg_born_attacker_camp:
					{
						object->addAttackerCampBornPos(&tempJumpPoint);
					}
					break;
				case point_slg_born_defender_camp:
					{
						object->addDefenserCampBornPos(&tempJumpPoint);
					}
					break;
				case point_slg_relive_attacker_general:
					{
						object->addAttackerGeneralRelivePos(&tempJumpPoint);
					}
					break;
				case point_slg_relivedefender_general:
					{
						object->addDefenserGeneralRelivePos(&tempJumpPoint);
					}
					break;
				default:
					{
						DYNAMIC_ASSERT(0);
					}
					break;

				}
			}
		}
		else if(group == SCENE_OBJECT_GROUP_STR_NPC)
		{
			NPCInfoXml tempNPC;
			tempNPC.pos = pos;

			std::map<Str,Str>::iterator iter= customAttr.find("CharID");
			if (iter != customAttr.end())
			{
				MGStrOp::toI32(iter->second.c_str(), tempNPC.charId);
				DYNAMIC_ASSERT(tempNPC.charId > 0);
			}

			object->addNPCInfo(&tempNPC);
		}
		else if(group == SCENE_OBJECT_GROUP_STR_MONSTER)
		{
			MonsterInfoXml tempMonster;
			tempMonster.pos = pos;
			tempMonster.dir = dir;
			tempMonster.appearType = appearType;
			
			std::map<Str,Str>::iterator iter= customAttr.find("CharID");
			if (iter != customAttr.end())
			{
				MGStrOp::toI32(iter->second.c_str(), tempMonster.charTemplateId);
				DYNAMIC_ASSERT(tempMonster.charTemplateId > 0);
			}

			object->addMonsterInfo(&tempMonster);
		}
		else if(group ==SCENE_OBJECT_GROUP_STR_TROOP)
		{

		}
		else if(group == SCENE_OBJECT_GROUP_STR_REGION)
		{
			
		}
		else if(group == SCENE_OBJECT_GROUP_STR_BUILDING)
		{
			I32 tempCharId		= -1;
			I32 tempBuildType	= -1;
			I32 tempForce		= -1;
			CHAR_BUILD_TYPE buildType = CHAR_BUILD_TYPE_NULL;

			//���� CharID
			{
				std::map<Str,Str>::iterator iter = customAttr.find("CharID");
				if (iter != customAttr.end())
				{
					MGStrOp::toI32(iter->second.c_str(), tempCharId);
					DYNAMIC_ASSERT(tempCharId > 0);
				}
			}

			//���� BuildType
			{
				std::map<Str,Str>::iterator iter = customAttr.find("BuildType");
				if (iter != customAttr.end())
				{
					MGStrOp::toI32(iter->second.c_str(), tempBuildType);
					buildType = (CHAR_BUILD_TYPE)tempBuildType;
					DEBUG_ASSERT_LOG(buildType > CHAR_BUILD_TYPE_NULL && buildType < CHAR_BUILD_TYPE_MAX,
									"buildType > CHAR_BUILD_TYPE_NULL && buildType < CHAR_BUILD_TYPE_MAX");
					DYNAMIC_ASSERT(buildType > CHAR_BUILD_TYPE_NULL && buildType < CHAR_BUILD_TYPE_MAX);
					
				}
			}

			//���� Forces
			{
				std::map<Str,Str>::iterator iter = customAttr.find("Forces");
				if (iter != customAttr.end())
				{
					MGStrOp::toI32(iter->second.c_str(), tempForce);
				}
			}
			
			//������
			switch(tempBuildType)
			{
			case CHAR_BUILD_TYPE_NOT_FIGHT:		//1~ϵͳ����(���μ�ս��)
			case CHAR_BUILD_TYPE_NORMAL:		//2~һ�㽨��(������)
			case CHAR_BUILD_TYPE_FIGHT:			//3~ս������(�ṥ��)��
			case CHAR_BUILD_TYPE_WALL:			//4~��ǽ֮ǽ
			case CHAR_BUILD_TYPE_CORNER:		//5~��ǽ֮ת��
			case CHAR_BUILD_TYPE_BAR:			//6~��ǽ֮��¥
			case CHAR_BUILD_TYPE_TURRET:		//7~��ǽ֮��¥
			case CHAR_BUILD_TYPE_GATE:			//8~��ǽ֮����
			case CHAR_BUILD_TYPE_BRIDGE:		//9~��ǽ֮����
			case CHAR_BUILD_TYPE_RIVER:			//10~��ǽ֮���Ǻ�
				{
					BuildingInfoXml tempBuilding;
					tempBuilding.templateId		= tempCharId;
					tempBuilding.buildingType	= buildType;
					tempBuilding.pos			= pos;
					tempBuilding.dir			= dir;
					tempBuilding.appearType		= appearType;
					object->addBuildingInfo(&tempBuilding);
				}
				break;
			case CHAR_BUILD_TYPE_BARRACKS:		//11~��Ӫ
				{
					CampInfoXml tempCamp;

					tempCamp.templateId		= tempCharId;
					tempCamp.pos			= pos;
					tempCamp.dir			= dir;
					tempCamp.isHeadQuarter	= false;
					tempCamp.appearType		= appearType;

					if(FORCE_ATTACK == tempForce)
					{
						object->addCampAttackPos(&tempCamp);
					}
					else if(FORCE_DEFENSE == tempForce)
					{
						object->addCampDefenserPos(&tempCamp);
					}
					else
					{
						DYNAMIC_ASSERT(0);
					}
				}
				break;
			case CHAR_BUILD_TYPE_HEADQUARTERS:	//12~��Ӫ
				{
					CampInfoXml tempCamp;

					tempCamp.templateId		= tempCharId;
					tempCamp.pos			= pos;
					tempCamp.dir			= dir;
					tempCamp.isHeadQuarter	= true;
					tempCamp.appearType		= appearType;

					if(FORCE_ATTACK == tempForce)
					{
						object->addCampAttackPos(&tempCamp);
					}
					else if(FORCE_DEFENSE == tempForce)
					{
						object->addCampDefenserPos(&tempCamp);
					}
					else
					{
						DYNAMIC_ASSERT(0);
					}
				}
				break;
			default:
				{
					DYNAMIC_ASSERT(0);
				}
				break;
			}

		}
		else
		{
			DYNAMIC_ASSERT(0);
		}

	}


	
}