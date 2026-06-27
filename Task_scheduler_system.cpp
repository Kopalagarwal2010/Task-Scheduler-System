#include <iostream>
using namespace std;

class Task
{
public:
    int id;
    string title;
    string description;
    string deadline;
    bool completed;

    Task()
    {
        id = 0;
        title = "";
        description = "";
        deadline = "";
        completed = false;
    }

    Task(int i, string t, string desc, string d)
    {
        id = i;
        title = t;
        description = desc;
        deadline = d;
        completed = false;
    }

    void display()
    {
        cout << "Task ID      : " << id << endl;
        cout << "Title        : " << title << endl;
        cout << "Description  : " << description << endl;
        cout << "Deadline     : " << deadline << endl;

        if (completed)
            cout << "Status : Completed" << endl;
        else
            cout << "Status : Pending" << endl;

        cout << endl;
    }

    bool isValidDate()
    {
        // Format: DD-MM-YYYY

        if (deadline.length() != 10)
            return false;

        if (deadline[2] != '-' || deadline[5] != '-')
            return false;

        for (int i = 0; i < deadline.length(); i++)
        {
            if (i == 2 || i == 5)
                continue;

            if (deadline[i] < '0' || deadline[i] > '9')
                return false;
        }

        int day = stoi(deadline.substr(0, 2));
        int month = stoi(deadline.substr(3, 2));
        int year = stoi(deadline.substr(6, 4));

        if (month < 1 || month > 12)
            return false;

        if (year < 2026)
            return false;

        int daysInMonth;

        switch (month)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            daysInMonth = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;

        case 2:
            if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
                daysInMonth = 29;
            else
                daysInMonth = 28;
            break;

        default:
            daysInMonth = 31;
            break;
        }

        if (day < 1 || day > daysInMonth)
            return false;

        return true;
    }
};

class PriorityQueue
{
private:
    Task arr[100];
    int size;

public:
    PriorityQueue()
    {
        size = 0;
    }

    bool isEmpty()
    {
        if (size == 0)
            return true;
        return false;
    }

    bool isFull()
    {
        if (size == 100)
        {
            return true;
        }
        return false;
    }

    void insert(Task t)
    {
        if (isFull())
        {
            cout << "Priority Queue Full!" << endl;
            return;
        }

        int i = size - 1;
        while (i >= 0 && arr[i].deadline > t.deadline)
        {
            arr[i + 1] = arr[i];
            i--;
        }

        arr[i + 1] = t;
        size++;
    }

    Task remove()
    {
        if (isEmpty())
        {
            cout << "No Tasks Entered: " << endl;
            return Task();
        }

        Task temp = arr[0];

        for (int i = 0; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        size--;

        return temp;
    }

    Task peek()
    {
        if (isEmpty())
        {
            cout << "No Tasks Entered: " << endl;
            return Task();
        }
        return arr[0];
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No Tasks Entered: " << endl;
            return;
        }
        cout << "\nPending Tasks:\n";

        for (int i = 0; i < size; i++)
        {
            cout << "Task ID : " << arr[i].id << endl;
            cout << "Title   : " << arr[i].title << endl;
            cout << "Deadline: " << arr[i].deadline << endl;
            cout << endl;
        }
    }

    void deleteTask(int id)
    {
        if (isEmpty())
        {
            cout << "No Tasks Entered: " << endl;
            return;
        }

        int index = -1;

        for (int i = 0; i < size; i++)
        {
            if (arr[i].id == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return;

        for (int i = index; i < size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        size--;
    }
};

class Stack
{
private:
    Task arr[100];
    int top;

public:
    Stack()
    {
        top = -1;
    }

    bool isEmpty()
    {
        if (top == -1)
            return true;
        else
            return false;
    }

    bool isFull()
    {
        if (top == 99)
            return true;
        else
            return false;
    }

    void push(Task t)
    {
        if (isFull())
        {
            cout << "Stack Full" << endl;
            return;
        }
        top++;
        arr[top] = t;
    }

    Task pop()
    {
        if (isEmpty())
        {
            cout << "No Completed Tasks" << endl;
            return Task();
        }
        Task temp = arr[top];
        top--;
        return temp;
    }

    Task peek()
    {
        if (isEmpty())
        {
            cout << "No tasks Completed" << endl;
            return Task();
        }
        cout << "Last Task Completed: ";
        return arr[top];
    }

    void display()
    {
        if (isEmpty())
        {
            cout << "No Tasks Completed Yet" << endl;
            return;
        }
        cout << "\nCompleted Tasks (Latest First):\n";

        for (int i = top; i >= 0; i--)
        {
            cout << "Task ID: " << arr[i].id << endl;
            cout << "Title: " << arr[i].title << endl;
            cout << "Deadline: " << arr[i].deadline << endl;
            cout << endl;
        }
    }

    void deleteTask(int id)
    {
        if (isEmpty())
            return;

        int index = -1;

        for (int i = 0; i <= top; i++)
        {
            if (arr[i].id == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
            return;

        for (int i = index; i < top; i++)
        {
            arr[i] = arr[i + 1];
        }

        top--;
    }
};

class Scheduler
{
private:
    Task tasks[100];
    int count;
    int nextID;

    PriorityQueue pq;
    Stack completedStack;

public:
    Scheduler()
    {
        count = 0;
        nextID = 1;
    }

    void addTask()
    {
        if (count == 100)
        {
            cout << "Task List Full!" << endl;
            return;
        }

        string title;
        string description;
        string deadline;

        cout << "Enter Task Title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Enter Description: ";
        getline(cin, description);

        cout << "Enter Deadline (DD-MM-YYYY): ";
        getline(cin, deadline);

        Task t(nextID, title, description, deadline);

        if (!t.isValidDate())
        {
            cout << "Invalid Date!" << endl;
            return;
        }

        if (duplicateTask(title, deadline))
        {
            cout << "Task Already Exists!" << endl;
            return;
        }

        tasks[count] = t;
        count++;

        nextID++;

        pq.insert(t);

        cout << "Task Added Successfully!" << endl;
    }

    bool duplicateTask(string title, string deadline)
    {
        for (int i = 0; i < count; i++)
        {
            if (tasks[i].title == title &&
                tasks[i].deadline == deadline)
            {
                return true;
            }
        }

        return false;
    }

    void deleteTask()
    {
        if (count == 0)
        {
            cout << "No Tasks Entered!" << endl;
            return;
        }

        int id;
        cout << "Enter Task ID to delete: ";
        cin >> id;

        int index = -1;

        for (int i = 0; i < count; i++)
        {
            if (tasks[i].id == id)
            {
                index = i;
                break;
            }
        }

        if (index == -1)
        {
            cout << "Task Not Found!" << endl;
            return;
        }

        bool wasCompleted = tasks[index].completed;

        for (int i = index; i < count - 1; i++)
        {
            tasks[i] = tasks[i + 1];
        }
        count--;

        if (!wasCompleted)
        {
            pq.deleteTask(id);
        }
        else
        {
            completedStack.deleteTask(id);
        }

        cout << "Task Deleted Successfully!" << endl;
    }

    void searchTask()
    {
        if (count == 0)
        {
            cout << "No Tasks Entered!" << endl;
            return;
        }

        int choice;
        cout << "Search By:\n1. Task ID\n2. Title\nEnter choice: ";
        cin >> choice;

        bool found = false;

        if (choice == 1)
        {
            int id;
            cout << "Enter Task ID: ";
            cin >> id;

            for (int i = 0; i < count; i++)
            {
                if (tasks[i].id == id)
                {
                    tasks[i].display();
                    found = true;
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            string title;
            cout << "Enter Title: ";
            cin.ignore();
            getline(cin, title);

            for (int i = 0; i < count; i++)
            {
                if (tasks[i].title == title)
                {
                    tasks[i].display();
                    found = true;
                }
            }
        }
        else
        {
            cout << "Invalid Choice!" << endl;
            return;
        }

        if (!found)
            cout << "Task Not Found!" << endl;
    }

    void completeTask()
    {
        if (pq.isEmpty())
        {
            cout << "No Pending Tasks!" << endl;
            return;
        }

        Task t = pq.remove();
        t.completed = true;

        for (int i = 0; i < count; i++)
        {
            if (tasks[i].id == t.id)
            {
                tasks[i].completed = true;
                break;
            }
        }

        completedStack.push(t);

        cout << "Task Completed: " << t.title << endl;
    }

    void undoTask()
    {
        if (completedStack.isEmpty())
        {
            cout << "No Completed Tasks to Undo!" << endl;
            return;
        }

        Task t = completedStack.pop();
        t.completed = false;

        for (int i = 0; i < count; i++)
        {
            if (tasks[i].id == t.id)
            {
                tasks[i].completed = false;
                break;
            }
        }

        pq.insert(t);

        cout << "Task Undone: " << t.title << endl;
    }

    void viewNextTask()
    {
        if (pq.isEmpty())
        {
            cout << "No Pending Tasks!" << endl;
            return;
        }

        Task t = pq.peek();
        cout << "\nNext Task:\n";
        t.display();
    }

    void displayPendingTasks()
    {
        pq.display();
    }

    void displayCompletedTasks()
    {
        completedStack.display();
    }

    void displayAllTasks()
    {
        if (count == 0)
        {
            cout << "No Tasks Entered!" << endl;
            return;
        }

        cout << "\nAll Tasks:\n";
        for (int i = 0; i < count; i++)
        {
            tasks[i].display();
        }
    }
};

int main()
{
    Scheduler s;

    int choice;

    do
    {
        cout << "\n==== TASK SCHEDULER =====\n";
        cout << "1. Add Task\n";
        cout << "2. Delete Task\n";
        cout << "3. Search Task\n";
        cout << "4. View Next Task\n";
        cout << "5. Complete Next Task\n";
        cout << "6. Undo Last Completed Task\n";
        cout << "7. Display All Tasks\n";
        cout << "8. Display Pending Tasks\n";
        cout << "9. Display Completed Tasks\n";
        cout << "10. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s.addTask();
            break;

        case 2:
            s.deleteTask();
            break;

        case 3:
            s.searchTask();
            break;

        case 4:
            s.viewNextTask();
            break;

        case 5:
            s.completeTask();
            break;

        case 6:
            s.undoTask();
            break;

        case 7:
            s.displayAllTasks();
            break;

        case 8:
            s.displayPendingTasks();
            break;

        case 9:
            s.displayCompletedTasks();
            break;

        case 10:
            cout << "\nThank you for using Task Scheduler!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 10);

    return 0;
}
