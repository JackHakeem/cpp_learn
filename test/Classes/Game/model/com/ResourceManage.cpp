#include "ResourceManage.h"
#include "vo/ResType.h"

ResourceManage::ResourceManage()
{

}

ResourceManage::~ResourceManage()
{
	RESOURCEVOITER it;

	for ( it = _resDic.begin(); it != _resDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_resDic.clear();

	for ( it = _resSkillDic.begin(); it != _resSkillDic.end(); it++ )
	{
		CC_SAFE_DELETE( it->second );
	}
	_resSkillDic.clear();
	
}

ResourceVo * ResourceManage::getRes( int type, int iResID )
{
	RESOURCEVOITER it;

	switch ( type )
	{
	case ResType::MODEL_TYPE:
		{
			it = _resDic.find( iResID );

			if ( it != _resDic.end() )
			{
				return it->second;
			}
		}
		break;
	case ResType::SKILL_TYPE:
		{
			it = _resSkillDic.find( iResID );

			if ( it != _resSkillDic.end() )
			{
				return it->second;
			}
		}
		break;
	case ResType::FORMATION_TYPE:
		break;
	}

	return 0;
}

 void ResourceManage::setRes( ResourceVo * pResourceVo )
{
	if (!pResourceVo) return;

	if ( pResourceVo->type == ResType::MODEL_TYPE )
	{
		pResourceVo->setUrl();
		_resDic.insert(  make_pair( pResourceVo->id, pResourceVo )  );
	}
	else if ( pResourceVo->type == ResType::SKILL_TYPE )
	{
		pResourceVo->setUrl();
		_resSkillDic.insert(  make_pair( pResourceVo->id, pResourceVo )  );
	}
	else
	{

	}
}

 ResourceVo * ResourceManage::getDefaultModel(int id)
 {
	 ResourceVo* resVo = new ResourceVo();
	 resVo->id = id;
	 resVo->type = ResType::MODEL_TYPE;
	 resVo->timer = 125;
	 resVo->nameY = -125;
	 return resVo;
 }

 ResourceVo * ResourceManage::getDefaultSkill(int id)
 {
	 ResourceVo* resVo = new ResourceVo();
	 resVo->id = id;
	 resVo->type = ResType::SKILL_TYPE;
	 resVo->timer = 84;
	 resVo->blendMode = "normal";
	 return resVo;
 }

std::string ResourceManage::skillUrl()
 {
	 string skillUrl = "assets/mapassets/simpleskill";
	 return skillUrl;
 }