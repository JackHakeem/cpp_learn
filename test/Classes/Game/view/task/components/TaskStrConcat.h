#ifndef _TASK_STR_CONCAT_H_
#define _TASK_STR_CONCAT_H_

#include "model/task/vo/TaskTipVo.h"
#include "BaseType.h"
#include "model/task/vo/TaskVo.h"

class TaskStrConcat
{
public:

	static bool checkTaskFinish(TaskTipVo * tips);
	static string getTaskTip(TaskVo *pTaskVo);
	static string getType0(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType1(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType2(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType3(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType4(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	/*static string getType5(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType6(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);*/
	static string getType7(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType8(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType9(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType10(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getType11(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);
	static string getDialog(TaskVo *pTaskVo, TaskTipVo *pTaskTipVo);

	// 20120611
	// Doyang.
	// Only one find path exist!
	static std::string conditionHtmlString( TaskVo *pTaskVo );
	static void findElement( string str );
	static void findNPC(TaskVo *pTaskVo);
};
#endif