#include "EffectHelps.h"
#include "model/com/ResourceManage.h"
#include "manager/SourceCacheManage.h"
#include "model/scene/vo/BuffTypeVo.h"
#include "view/scene/components/ImageTxt.h"
#include "view/scene/components/FightSkillTextField.h"
#include "view/scene/components/FightAoyiTextField.h"
#include "view/scene/components/FightSpecialFontField.h"
#include "view/scene/components/LiveThing.h"
#include "ScaleUtil.h"
#include "manager/GlobalManage.h"

/**
* getSkillEffectMC
* @param id
* @return 
*/
BitmapMovieClip* EffectHelps::getSkillEffectMC( int resId, float interval)
{
	//Kenfly 20121108 : modify
	//string _assetURL = ResourceManage::Instance()->skillUrl();

	//char fmt[54];
	//sprintf( fmt, "/effect-%d.plist", /*pListId*/resId );
	//string path = _assetURL + fmt;

	//sprintf( fmt, "%d/image0", resId );
	//string frame =  std::string(fmt) + "%d.png";


	if ( GlobalScale::Instance()->getStandardWidth()== 480 )
	{
		if (!g_pGlobalManage->m_bBattleEffectOn)
		{
			return 0;
		}
	}

	BitmapMovieClip* effectMC = new BitmapMovieClip();
	int res = effectMC->loadPvrCommonAsync(resId, 30, interval);

	if (res == -1)
	{
		CC_SAFE_RELEASE(effectMC);
		return 0;
	}
	else
	{
		return effectMC;
	}


	//BitmapMovieClip* effectMC = 0;

	//CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA8888 );

	//effectMC = SourceCacheManage::Instance()->loadPVRCommon( resId, 30, interval, true );

	//CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );

	//return effectMC;

	//End Kenfly 20121108
}

/**
* 添加Buff效果
* @param sp
* @param buffType
* @param delay
* @return 
* 
*/
TweenLiteObject* EffectHelps::addBuffEffect( CCNode* hiter, int buffType, float delay/* = 0.2*/ )
{
	return 0;
}

BitmapMovieClip* EffectHelps::getBuffEffect( int type )
{
	BitmapMovieClip* obj = 0;
	//obj = getSkillEffectMC( EffectHelps::DIZZY );
	switch(type)
	{
	case BuffTypeVo::BUFF_TYPE_DIZZY:
		obj = getSkillEffectMC( EffectHelps::DIZZY );
		break;
		//				case BuffTypeVo.BUFF_TYPE_TRAP:
		//					obj = getSkillEffectMC(EffectHelps.DIZZY);
		//					break;
		//				case BuffTypeVo.DOT_TYPE_BLEED:
		//					obj = getSkillEffectMC(EffectHelps.DIZZY);
		//					break;
		//				case BuffTypeVo.DOT_TYPE_BURN:	
		//					obj = getSkillEffectMC(EffectHelps.DIZZY);
		//					break;
		//				case BuffTypeVo.DOT_TYPE_POISONING:
		//					obj = getSkillEffectMC(EffectHelps.DIZZY);
		//					break;
	}
	return obj;
}





void EffectHelps::getEffectEx(LiveThing* sp, bool iscrit, int damage, int value, float vx, float vy, float delay, float duration)
{
	if(damage!=0 && sp!=0)
	{
		ImageTxt* txt = new ImageTxt();
		txt->init();

	 	int damageType = damage<0 ? ImageTxt::BLOOD_DOWN : ImageTxt::BLOOD_UP;

		std::string name = "";
	
		txt->createTxt(damageType , sp->arraySeat,  damage, iscrit);

        sp->addChild(txt, 200);
//		if (sp->getChildByTag(LiveThing::FightingTar_ImageTxt))
//		{
//			//创建
//			sp->addChild(txt, 200, LiveThing::FightingTar_ImageTxt2);
//		}
//		else
//		{
//			//创建
//			sp->addChild(txt, 200, LiveThing::FightingTar_ImageTxt);
//		}
		
		txt->release();
		txt->doAction();
		CCLog("ImageTxt add");
	}
}

/**
	* 技能名称  
	* @param sp
	* @param str
	* @param vx
	* @param vy
	* @param delay
	* @return 
	* 
	*/		
TweenLiteObject* EffectHelps::getSkillName(CCNode* sp, SkillVo& skill, float vx, float vy, float delay, float duration)
{


	if (skill.nameid<=0)
	{

		
		if (skill.id == 1)
		{
			TweenLiteObject* obj  = EffectHelps::getMCNameEffect(sp, FightSpecialFontField::FANJI, 100, 20, 0.1f);
			
			return obj;
		}
		//
		if (sp->getChildByTag(LiveThing::FightingTar_SkillName))
			return 0;//还存在证明之前的还没播放完毕,此特效不播放了

		FightSkillTextField* txt = new FightSkillTextField();
		txt->init();
		if (!txt->createTxt(skill.name, skill.id))
		{
			txt->release();
			return 0;
		}

		TweenLiteObjectVars* vars = new TweenLiteObjectVars;
		vars->delay = delay;

		//创建
		sp->addChild(txt, 201, LiveThing::FightingTar_SkillName);
	
		txt->release();
		
		TweenLiteObject* tweenLite = new TweenLiteObject( 0, 0, vars );
		tweenLite->registerCallback( callfunc_selector(FightSkillTextField::doAction), txt );
		return tweenLite;
	
	}
	else 
	{
		if (skill.nameid == 1)
		{
			TweenLiteObject* obj  = EffectHelps::getMCNameEffect(sp, FightSpecialFontField::FANJI, 100, 20, 0.1f);
			
			return obj;
		}
		//
		if (sp->getChildByTag(LiveThing::FightingTar_AoyiSkillName))
			return 0;//还存在证明之前的还没播放完毕,此特效不播放了
		
		FightAoyiTextField* txt = new FightAoyiTextField();
		txt->init();
		if (!txt->createTxt(skill.nameid))
		{
			txt->release();
			return 0;
		}

		TweenLiteObjectVars* vars = new TweenLiteObjectVars;
		vars->delay = delay;

		//创建
		sp->addChild(txt, 201, LiveThing::FightingTar_AoyiSkillName);
	
		txt->release();
		
		TweenLiteObject* tweenLite = new TweenLiteObject( 0, 0, vars );
		tweenLite->registerCallback( callfunc_selector(FightAoyiTextField::doAction), txt );
		return tweenLite;		
	}
	
}

void EffectHelps::getSkillNameEx(LiveThing* sp, SkillVo& skill, float vx, float vy, float delay, float duration)
{
	if (skill.nameid<=0)
	{	
		if (skill.id == 1)
		{
			EffectHelps::getMCNameEffectEx(sp, FightSpecialFontField::FANJI, 100, 20, 0.1f);
		
			return;
		}
		//
		//if (sp->getChildByTag(LiveThing::FightingTar_SkillName))
		//	return;//还存在证明之前的还没播放完毕,此特效不播放了

		FightSkillTextField* txt = new FightSkillTextField();
		txt->init();
		if (!txt->createTxt(skill.name, skill.id))
		{
			txt->release();
			return;
		}

		//创建
		sp->addChild(txt, 201);
		txt->release();
		txt->doAction();
		CCLog("Skill add");
	}
	else 
	{
		if (skill.nameid == 1)
		{
			EffectHelps::getMCNameEffectEx(sp, FightSpecialFontField::FANJI, 100, 20, 0.1f);

			return;
		}
		//
	//	if (sp->getChildByTag(LiveThing::FightingTar_AoyiSkillName))
	//		return;//还存在证明之前的还没播放完毕,此特效不播放了
		
		FightAoyiTextField* txt = new FightAoyiTextField();
		txt->init();
		if (!txt->createTxt(skill.nameid))
		{
			txt->release();
			return;
		}


		//创建
		sp->addChild(txt, 201);
		txt->release();
		txt->doAction();
		CCLog("AOYI add");
	}
}

/**
	* 获取 MovieClip 的播放效果
	* @param sp
	* @param mcName
	* @param Number
	* @param y
	* @param startFun
	* @return 
	* 
	*/		
TweenLiteObject* EffectHelps::getMCNameEffect(CCNode* sp, int mcName, float x, float y, float delay)
{
	//if (sp->getChildByTag(LiveThing::FightingTar_SkillName))
	//	return 0;//还存在证明之前的还没播放完毕,此特效不播放了

	FightSpecialFontField* txt = new FightSpecialFontField();
	txt->init();
	if (!txt->createTxt(mcName))
	{
		txt->release();
		return 0;
	}

	TweenLiteObjectVars* vars = new TweenLiteObjectVars;
	vars->delay = 0.3f;
	//vars->onStartParams.addObject( sp );
	//vars->onStartParams.addObject( txt );


	//创建
	sp->addChild(txt, 201);//, LiveThing::FightingTar_SkillName
	
	txt->release();
		
	TweenLiteObject* tweenLite = new TweenLiteObject( 0, 0, vars );
	tweenLite->registerCallback( callfunc_selector(FightSpecialFontField::doAction), txt );
	return tweenLite;

}


void EffectHelps::getMCNameEffectEx(LiveThing* sp, int mcName, float x, float y, float delay)
{
	FightSpecialFontField* txt = new FightSpecialFontField();
	txt->init();
	if (!txt->createTxt(mcName))
	{
		txt->release();
		return;
	}

	//创建
	sp->addChild(txt, 201);
	
	txt->release();
	txt->doAction();

}


/**
	* MP值的改变.没有效果 
	* @param sp
	* @param mp
	* @param delay
	* @return 
	* 
	*/		
void EffectHelps::getMPEffectEx(LiveThing* sp, int mp, float delay, float duration, int diff)
{
	if(diff > 0)
	{
		ImageTxt* txt = new ImageTxt();
		txt->init();

	 	int damageType = ImageTxt::MP_UP;
	
		txt->createTxt(damageType , sp->arraySeat, diff, false);

		sp->addChild(txt, 199);
		
		txt->release();
		txt->doAction();
		CCLog("ImageTxt add");

		//var txt:ImageTxt = new ImageTxt();
		//var damageType:int = ImageTxt.MP_UP;
		//var name:String = "addire_add";
		//var vx:int = 0;
		//var vy:int = -50;
		//		
		//txt.createTxt(name, damageType , String(Math.abs(diff)));
		//txt.x = vx - (txt.width >> 1);
		//txt.y = vy;
 	//			
		//tl = new TweenLiteObject(txt, duration, {y:vy - 100, 
		//	ease:Back.easeOut,  /*回落*/
		//	delay:delay,
		//	onStart:onStartTxtMp,
		//	onStartParams:[sp,txt,mp],
		//	onComplete:onMpTweenComplete, 
		//	onCompleteParams:[sp, txt]});
		//		
		//function onStartTxtMp(sp:LiveThing, txt:ImageTxt, mp:int):void{
		//	sp.mp = mp;
		//	sp.addChild(txt);
		//}
		//		
		//function onMpTweenComplete(sp:LiveThing, imageTxt:ImageTxt):void{
		//	if (sp!= null && sp.contains(imageTxt))
		//	{
		//		sp.removeChild(imageTxt);
		//		imageTxt = null;
		//	}
		//}
		//		
	}
	else{
	/*			
		tl = new TweenLiteObject (sp, 0.1, {delay:delay,
			onStart:onStartTxt1,
			onStartParams:[sp,mp]});
			
		function onStartTxt1(sp:LiveThing,mp:int):void{
			sp.mp = mp;
		}*/
	}
}

/**
	* 添加Buff效果  
	* @param sp
	* @param buffType
	* @param delay
	* @return 
	* 
	*/		
void EffectHelps::addBuffEffectEx(LiveThing* hiter, int buffType)
{
	if ( hiter && hiter->getParent())
	{
		if (hiter->getChildByTag(BuffTypeVo::XUAN_YUN))
			return;
	}
	//现在只有眩晕特效
	BitmapMovieClip* effectMC = EffectHelps::getBuffEffectEx( buffType );
	//设置特效位置已经被ADDCHILD以及无尽RUN
	if ( hiter && hiter->getParent() && effectMC )
	{
		effectMC->setPosition(ccp(POSX(3), POSX(115)));
	/*	rntPos.y = POSX(640) - rntPos.y;
		rntPos.y += 44.0f;
		if (src->arraySeat >= 9)
			rntPos.y += 30.0f;*/

		hiter->addChild( effectMC, 1000, BuffTypeVo::XUAN_YUN );
		effectMC->release();

		effectMC->runActionPVRCommonRepeat();
	}
	else
		CC_SAFE_RELEASE(effectMC); //Kenfly 20121110
}

BitmapMovieClip* EffectHelps::getBuffEffectEx(int type)
{
	switch(type)
	{
	case BuffTypeVo::BUFF_TYPE_DIZZY:
			{
				BitmapMovieClip* effectMC = EffectHelps::getSkillEffectMC(203, 0.08f);
				return effectMC;
			}
			
			break;
//				case BuffTypeVo.BUFF_TYPE_TRAP:
//					obj = getSkillEffectMC(EffectHelps.DIZZY);
//					break;
//				case BuffTypeVo.DOT_TYPE_BLEED:
//					obj = getSkillEffectMC(EffectHelps.DIZZY);
//					break;
//				case BuffTypeVo.DOT_TYPE_BURN:	
//					obj = getSkillEffectMC(EffectHelps.DIZZY);
//					break;
//				case BuffTypeVo.DOT_TYPE_POISONING:
//					obj = getSkillEffectMC(EffectHelps.DIZZY);
//					break;
	}
	return 0;
}