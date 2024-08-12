#pragma once

#include <concepts>
#include <functional>

enum class ProcessStage : uint8_t
{
	  Pre = 0
	, Post = 1
};

using task = std::function<void()>;
using task_ptr = std::shared_ptr<task>;

/*!
* @brief Enqueue a long-term task into AI/Process cycle.
*/
void Enqueue(ProcessStage stage, task_ptr const& task);
/*!
* @brief Enqueue a one-time task into AI/Process cycle.
*/
void EnqueueOnce(ProcessStage stage, task_ptr const& task);
/*!
* @brief Remove a task into AI/Process cycle.
*/
void Dequeue(ProcessStage stage, task_ptr const& task);
