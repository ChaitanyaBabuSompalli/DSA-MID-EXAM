#include <iostream>
#include <string>

// Node structure to represent a task
struct Task {
    std::string description;
    Task* next;

    Task(const std::string& desc) : description(desc), next(nullptr) {}
};

// To-Do List class
class ToDoList {
private:
    Task* head;

public:
    ToDoList() : head(nullptr) {}

    // Add a new task to the to-do list
    void addTask(const std::string& description) {
        Task* newTask = new Task(description);
        if (head == nullptr || description < head->description) {
            newTask->next = head;
            head = newTask;
        }
        else {
            Task* current = head;
            while (current->next != nullptr && description > current->next->description) {
                current = current->next;
            }
            newTask->next = current->next;
            current->next = newTask;
        }
    }

    // Remove a task from the to-do list
    void removeTask(const std::string& description) {
        Task* current = head;
        Task* prev = nullptr;

        while (current != nullptr && current->description != description) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Task not found." << std::endl;
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }

        delete current;
    }

    // Display all tasks in the to-do list
    void displayTasks() {
        Task* current = head;
        std::cout << "To-Do List:" << std::endl;
        while (current != nullptr) {
            std::cout << "- " << current->description << std::endl;
            current = current->next;
        }
    }

    // Destructor to free memory
    ~ToDoList() {
        Task* current = head;
        while (current != nullptr) {
            Task* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
};

int main() {
    ToDoList toDoList;

    char choice;
    std::string taskDescription;

    do {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Add a task" << std::endl;
        std::cout << "2. Remove a task" << std::endl;
        std::cout << "3. Display tasks" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case '1':
            std::cout << "Enter task description: ";
            std::cin.ignore(); // Clear the input buffer
            std::getline(std::cin, taskDescription);
            toDoList.addTask(taskDescription);
            break;
        case '2':
            std::cout << "Enter task description to remove: ";
            std::cin.ignore(); // Clear the input buffer
            std::getline(std::cin, taskDescription);
            toDoList.removeTask(taskDescription);
            break;
        case '3':
            toDoList.displayTasks();
            break;
        case '4':
            std::cout << "Exiting program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != '4');

    return 0;
}
