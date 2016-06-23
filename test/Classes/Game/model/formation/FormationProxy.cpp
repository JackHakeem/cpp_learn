#include "FormationProxy.h"

FormationProxy::FormationProxy()
{

}

FormationProxy::~FormationProxy()
{

}


/**
		 * 更新某个位置成员信息
		 * @param formation
		 * @param sitGrid
		 * @param info
		 * 
		 */		
void FormationProxy::updateTeamMemberInfo( int formation , int sitGrid ,PlayerInfoVo* info )
{
	/*if(info==null && _teamMemberDic[sitGrid]){
		delete _teamMemberDic[sitGrid];
	}else{
		_teamMemberDic[sitGrid] = info;
	}
	this.sendNotification(FormationMediator.TEAM_MEMBER_UPDATE, {formation:formation, sitGrid:sitGrid, info:info});*/
}


/**
		 *交换位置（可能两个位置都有人，也可能其中一个为空） 
		 * @param formation
		 * @param grid1
		 * @param grid2
		 * 
		 */	


void FormationProxy::changeTeamMemberSit( int formation ,int grid1 , int grid2 )
{
	/*if(_teamFormation != formation)return;
	var info:PlayerInfoVo = _teamMemberDic[grid1];

	if(_teamMemberDic.hasOwnProperty(grid2)) _teamMemberDic[grid1] = _teamMemberDic[grid2];
	else delete _teamMemberDic[grid1];

	if(info)  _teamMemberDic[grid2] = info;
	else delete _teamMemberDic[grid2];
	this.sendNotification(FormationMediator.TEAM_MEMBER_CHANGE_SIT,{formation:formation, grid1:grid1, grid2:grid2});
	}

	public function get teamFormation():int{
	return _teamFormation;
	}

	public function get teamMemberDic():Dictionary{
	return _teamMemberDic;
	}

	public function teamQuitHandle():void{
	isTeamCreate = false;
	_teamFormation = 0;
	_teamMemberDic = null;
	}*/
}

