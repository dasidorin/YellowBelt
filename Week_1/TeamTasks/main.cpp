#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <vector>
#include <exception>

using namespace std;

enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

void PrintTasksInfo(const TasksInfo& tasks) {

    cout << "NEW: ";
    if (tasks.count(TaskStatus::NEW)) {
        cout << tasks.at(TaskStatus::NEW);
    } else {
        cout << "No tasks in NEW status";
    }
    cout << endl;

    cout << "IN_PROGRESS: ";
    if (tasks.count(TaskStatus::IN_PROGRESS)) {
        cout << tasks.at(TaskStatus::IN_PROGRESS);
    } else {
        cout << "No tasks in IN_PROGRESS status";
    }
    cout << endl;

    cout << "TESTING: ";
    if (tasks.count(TaskStatus::TESTING)) {
        cout << tasks.at(TaskStatus::TESTING);
    } else {
        cout << "No tasks in TESTING status";
    }
    cout << endl;


    cout << "DONE: ";
    if (tasks.count(TaskStatus::DONE)) {
        cout << tasks.at(TaskStatus::DONE);
    } else {
        cout << "No tasks in DONE status";
    }
    cout << endl << endl;

}

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

void AddNewTasks(TeamTasks& tasks, string developer, int count) {
    for (int i = 0; i < count; ++i) {
        tasks.AddNewTask(developer);
    }
}

int main() {
    TeamTasks tasks;

    TasksInfo updated, untouched;
    cout << "Add 5: " << endl;
    AddNewTasks(tasks, "Alice", 5);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    cout << "Perform 5: " << endl;
    tie(updated, untouched) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl << "Updated: " << endl;
    PrintTasksInfo(updated);
    cout << endl << "Untouched: " << endl;
    PrintTasksInfo(untouched);

    cout << "Perform 5: " << endl;
    tie(updated, untouched) = tasks.PerformPersonTasks("Alice", 5);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl << "Updated: " << endl;
    PrintTasksInfo(updated);
    cout << endl << "Untouched: " << endl;
    PrintTasksInfo(untouched);

    cout << "Perform 1: " << endl;
    tie(updated, untouched) = tasks.PerformPersonTasks("Alice", 1);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl << "Updated: " << endl;
    PrintTasksInfo(updated);
    cout << endl << "Untouched: " << endl;
    PrintTasksInfo(untouched);

    cout << "Add 5: " << endl;
    AddNewTasks(tasks, "Alice", 5);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

    cout << "Perform 2: " << endl;
    tie(updated, untouched) = tasks.PerformPersonTasks("Alice", 2);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl << "Updated: " << endl;
    PrintTasksInfo(updated);
    cout << endl << "Untouched: " << endl;
    PrintTasksInfo(untouched);

    cout << "Perform 4: " << endl;
    tie(updated, untouched) = tasks.PerformPersonTasks("Alice", 4);
    PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));
    cout << endl << "Updated: " << endl;
    PrintTasksInfo(updated);
    cout << endl << "Untouched: " << endl;
    PrintTasksInfo(untouched);
    return 0;
}
