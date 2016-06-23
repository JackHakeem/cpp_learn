#include "HonorProxy.h"
#include "mvc/Facade.h"
#include "view/tower/TowerMediator.h"
#include "control/AppFacade.h"
#include "vo/HonorScheduleManage.h"
#include "vo/HonorManage.h"

HonorProxy::HonorProxy()
{
	_isCreated = false;
}

HonorProxy::~HonorProxy()
{

}

/**
* 成就达成更新数据源
* */
void HonorProxy::updateHonorList(SCMD140* cmd)
{
	//var honorId:int = cmd.a_honorid.value;
 //   if(_honorList.hasOwnProperty(honorId)) return;
	//var obj:Object =new Object();
	//obj.id = honorId;
	//obj.award = false;
	//_honorList[obj.id] = obj;
	//HonorScheduleManage.getInstance().updateScheduleData(obj);
	//		
	//var honorGoods:HonorGoodVo = HonorManage.getInstance().getHonorGoodsVo(honorId);
	//if(honorGoods!=null){
	//	_lastTotalPiont =_roleTotalPint;
	//	_roleTotalPint += honorGoods.reward;
	//	if(honorGoods.title != ""){
	//		var arr:Array = honorGoods.title.split("|");
	//		var titleVo:HonorTitleVo = new HonorTitleVo();
	//		titleVo.titleId = honorGoods.honorsid;
	//		titleVo.explain = honorGoods.reamark;
	//		titleVo.titleName = arr[0];
	//		titleVo.picId = arr[1];
	//		titleVo.titleType = arr[2];
	//		_honorTitles.push(titleVo);
	//	}
	//}
	//if(_honorTitles.length > 1){
	//	_honorTitles.sortOn(["titleType","titleId"],Array.NUMERIC|Array.DESCENDING);
	//}
	//sendNotification(HonorMediator.HONONR_COMPLETED,honorId);	
}

void HonorProxy::createList(SCMD142* arr)
{
	_isCreated = true;
	handleHonorList(arr);	
	//sendNotification(HonorMediator.HONONR_CREAT_LIST);	
}

void HonorProxy::handleHonorList(SCMD142* arr)
{
	SCMD142* ahonorID = arr;
	//_roleTotalPint = ahonorID.a_currentpoint;
	//_roleHonorNameID = ahonorID.b_rolehononameid;
	//RoleManage.getInstance().roleInfo.playerBaseInfo.titleId = _roleHonorNameID;
	std::list<SCMD142::SCMD142Node1>::iterator it = ahonorID->c_idlist.begin();
	for ( ; it != ahonorID->c_idlist.end(); it++ )
	{
		SCMD142::SCMD142Node1 id = *it;
		int honorId = id.a_honorid;
		int honorAward = id.b_completed;

		HonorObject* obj = new HonorObject;
		obj->id = honorId;
		obj->award = honorAward;
		_honorList.insert( make_pair( honorId, obj ) );
		HonorScheduleManage::Instance()->updateScheduleData(obj);

		//HonorGoodVo* honorVo = HonorManage::Instance()->getHonorGoodsVo(honorId);
		//if(honorVo && honorVo->title != ""){
		//	var titleArr:Array = honorVo.title.split("|");
		//	var titleVo:HonorTitleVo = new HonorTitleVo();
		//	titleVo.titleId = honorVo.honorsid;
		//	titleVo.explain = honorVo.reamark;
		//	titleVo.titleName = titleArr[0];
		//	titleVo.picId = titleArr[1];
		//	titleVo.titleType = titleArr[2];
		//	_honorTitles.push(titleVo);
		//}
	}
	////增加一个Id为0的成就称号，称号名为“无”
	//var titleVoZero:HonorTitleVo = new HonorTitleVo();
	//titleVoZero.titleId = 0;
	//titleVoZero.explain = LangManager.getText("HOR006");
	//titleVoZero.titleName = LangManager.getText("COM623");
	//titleVoZero.picId = 0;
	//titleVoZero.titleType = 0;
	//_honorTitles.push(titleVoZero);

	//if(_honorTitles.length > 1){
	//	_honorTitles.sortOn(["titleType","titleId"],Array.NUMERIC|Array.DESCENDING);
	//}
	//for each(var point:SCMD142Node2 in ahonorID.d_pointlist){
	//	_honorPoint[point.a_wardpoint.value]= point.a_wardpoint.value;
	//}
}