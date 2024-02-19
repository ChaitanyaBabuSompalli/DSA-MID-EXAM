#include <iostream>
#include <string>

// Node structure to represent a task
struct Task {
    std::string description; // Description of the task
    Task* next; // Pointer to the next task

    // Constructor to initialize a task with a description
    Task(const std::string& desc) : description(desc), next(nullptr) {}
};

// To-Do List class
class ToDoList {
private:
    Task* head; // Pointer to the first task in the list

public:
    // Constructor to initialize an empty to-do list
    ToDoList() : head(nullptr) {}

    // Add a new task to the to-do list
    void addTask(const std::string& description) {
        Task* newTask = new Task(description);
        // If the list is empty or the new task comes before the current head task
        if (head == nullptr || description < head->description) {
            newTask->next = head;
            head = newTask;
        }
        else {
            Task* current = head;
            // Traverse the list to find the correct position to insert the new task
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

        // Traverse the list to find the task with the given description
        while (current != nullptr && current->description != description) {
            prev = current;
            current = current->next;
        }

        // If the task is not found
        if (current == nullptr) {
            std::cout << "Task not found." << std::endl;
            return;
        }

        // If the task to be removed is the head of the list
        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }

        // Delete the task
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

    // Destructor to free memory allocated for tasks
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

// Main function to execute the to-do list application
int main() {
    // Create an instance of the ToDoList class
    ToDoList toDoList;

    char choice;
    std::string taskDescription;

    // Main loop to interact with the to-do list
    do {
        // Display menu options
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
