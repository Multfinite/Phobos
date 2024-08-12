#include <Common/Processable.hpp>
#include <New/Entity/AttachmentClass.h>
#include <Utilities/Macro.h>

#include <map>
#include <list>

struct AITaskEntry
{
	bool OneTime;
	task_ptr Task;
};

std::map<ProcessStage, std::list<AITaskEntry>> Tasks;

void Enqueue(ProcessStage stage, task_ptr const& task)
{
	Tasks[stage].emplace_back(false, task);
}

void EnqueueOnce(ProcessStage stage, task_ptr const& task)
{
	Tasks[stage].emplace_back(true, task);
}

void Dequeue(ProcessStage stage, task_ptr const& task)
{
	Tasks[stage].remove_if([&task](AITaskEntry const& x) { return x.Task.get() == task.get(); });
}

inline FORCEINLINE void ExecuteTasks(ProcessStage stage)
{
	std::list<decltype(Tasks)::value_type::second_type::iterator> toRemove;
	auto& entries = Tasks[stage];
	for (auto it = entries.begin(); it != entries.end(); ++it)
	{
		auto& entry = *it;
		(*entry.Task.get())();
		if (entry.OneTime)
			toRemove.push_back(it);
	}
	for (auto& it : toRemove)
		entries.erase(it);
}

DEFINE_HOOK(0x55B5FF, LogicClass_AI_Objects, 0x6)
{
	GET(LogicClass*, pThis, EDI);

	std::list<decltype(Tasks)::value_type::second_type::iterator> toRemove;

	ExecuteTasks(ProcessStage::Pre);

	for (ObjectClass* o : *pThis)
		o->AI();

	ExecuteTasks(ProcessStage::Post);

	return 0x55B61B;
}

DEFINE_HOOK(0x55B6B3, LogicClass_AI_After, 0x5)
{
	for (auto const& attachment : AttachmentClass::Array)
		attachment->AI();

	return 0;
}
