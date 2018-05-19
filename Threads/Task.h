#ifndef ____TASK___
#define ____TASK___

#include <functional>

class CTask
{
public:
	CTask(std::function<void(int)> f);
	virtual ~CTask();

	virtual void exec();

protected:
	std::function<void(int)> m_funcResult;
};

#endif