#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <exception>

using namespace std;


// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return tasks.at(person);
    }

    void AddNewTask(const string& person) {
        tasks[person][TaskStatus::NEW] += 1;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
        TasksInfo updated_tasks, untouched_tasks;

        if (tasks.count(person)) {
            while (tasks[person][TaskStatus::NEW] && task_count) {
                updated_tasks[TaskStatus::IN_PROGRESS]++;
                tasks[person][TaskStatus::NEW]--;
                task_count--;
            }
            if (tasks[person][TaskStatus::NEW] == 0) {
                tasks[person].erase(TaskStatus::NEW);
            } else {
                untouched_tasks[TaskStatus::NEW] = tasks[person][TaskStatus::NEW];
            }

            while (tasks[person][TaskStatus::IN_PROGRESS] && task_count) {
                updated_tasks[TaskStatus::TESTING]++;
                tasks[person][TaskStatus::IN_PROGRESS]--;
                task_count--;
            }
            if (tasks[person][TaskStatus::IN_PROGRESS] == 0) {
                tasks[person].erase(TaskStatus::IN_PROGRESS);
            } else {
                untouched_tasks[TaskStatus::IN_PROGRESS] = tasks[person][TaskStatus::IN_PROGRESS];
            }

            if (updated_tasks.count(TaskStatus::IN_PROGRESS) && updated_tasks.at(TaskStatus::IN_PROGRESS) != 0) {
                tasks[person][TaskStatus::IN_PROGRESS] += updated_tasks[TaskStatus::IN_PROGRESS];
            }

            while (tasks[person][TaskStatus::TESTING] && task_count) {
                updated_tasks[TaskStatus::DONE]++;
                tasks[person][TaskStatus::TESTING]--;
                task_count--;
            }
            if (tasks[person][TaskStatus::TESTING] == 0) {
                tasks[person].erase(TaskStatus::TESTING);
            } else {
                untouched_tasks[TaskStatus::TESTING] = tasks[person][TaskStatus::TESTING];
            }
            if (updated_tasks.count(TaskStatus::TESTING) && updated_tasks.at(TaskStatus::TESTING) != 0) {
                tasks[person][TaskStatus::TESTING] += updated_tasks[TaskStatus::TESTING];
            }

            if (updated_tasks.count(TaskStatus::DONE) && updated_tasks.at(TaskStatus::DONE) != 0) {
                tasks[person][TaskStatus::DONE] += updated_tasks[TaskStatus::DONE];
            }
        }
        return tie(updated_tasks, untouched_tasks);
    }
private:
    map <string, TasksInfo> tasks;
};

