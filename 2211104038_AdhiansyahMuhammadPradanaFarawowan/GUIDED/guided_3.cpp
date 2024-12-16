#include <iostream>
#include <string>

struct Employee
{
    std::string name;
    Employee *next;
    Employee *subordinate;

    Employee(std::string empName)
    {
        name = empName;
        next = nullptr;
        subordinate = nullptr;
    }
};

class EmployeeList
{
private:
    Employee *head;

public:
    EmployeeList()
    {
        head = nullptr;
    }

    void add_employee(std::string name)
    {
        Employee *new_employee = new Employee(name);
        new_employee->next = head;
        head = new_employee;
    }

    void add_subordinate(std::string manager_name, std::string subordinate_name)
    {
        Employee *manager = head;
        while (manager != nullptr && manager->name != manager_name)
        {
            manager = manager->next;
        }
        if (manager != nullptr)
        {
            Employee *new_subordinate = new Employee(subordinate_name);
            new_subordinate->next = manager->subordinate;
            manager->subordinate = new_subordinate;
        }
        else
        {
            std::cout << "Manager not found!" << '\n';
        }
    }

    void delete_employee(std::string name)
    {
        // Huh
        Employee **current = &head;
        while (*current != nullptr && (*current)->name != name)
        {
            current = &((*current)->next);
        }

        if (*current != nullptr)
        {
            Employee *to_be_deleted = *current;
            *current = (*current)->next;

            while (to_be_deleted->subordinate != nullptr)
            {
                Employee *subTemp = to_be_deleted->subordinate;
                to_be_deleted->subordinate = to_be_deleted->subordinate->next;
                delete subTemp;
            }
            delete to_be_deleted;
            std::cout << "Employee " << name << " deleted." << '\n';
        }
        else
        {
            std::cout << "Employee " << name << " not found!" << '\n';
        }
    }

    void delete_subordinate(std::string manager_name, std::string subordinate_name)
    {
        Employee *manager = head;
        while (manager != nullptr && manager->name != manager_name)
        {
            manager = manager->next;
        }

        if (manager != nullptr)
        {
            // Huh
            Employee **current_subordinate = &(manager->subordinate);
            while (*current_subordinate != nullptr && (*current_subordinate)->name != subordinate_name)
            {
                current_subordinate = &((*current_subordinate)->next);
            }

            if (*current_subordinate != nullptr)
            {
                Employee *to_be_deleted = *current_subordinate;
                *current_subordinate = (*current_subordinate)->next;

                delete to_be_deleted;
                std::cout << "Subordinate " << subordinate_name << " deleted from " << manager_name << '\n';
            }
            else
            {
                std::cout << "Subordinate " << subordinate_name << " not found!" << '\n';
            }
        }
        else
        {
            std::cout << "Manager " << manager_name << " not found!" << '\n';
        }
    }

    void print_all()
    {
        Employee *current = head;
        while (current != nullptr)
        {
            std::cout << "Manager: " << current->name << " -> ";
            Employee *sub = current->subordinate;
            while (sub != nullptr)
            {
                std::cout << sub->name << ", ";
                sub = sub->next;
            }
            std::cout << '\n';
            current = current->next;
        }
    }

    ~EmployeeList()
    {

        while (head != nullptr)
        {
            Employee *temp = head;
            head = head->next;

            while (temp->subordinate != nullptr)
            {
                Employee *subTemp = temp->subordinate;
                temp->subordinate = temp->subordinate->next;
                delete subTemp;
            }
            delete temp;
        }
    }
};

int main()
{
    EmployeeList boring_list;

    boring_list.add_employee("Lelouch");
    boring_list.add_employee("Schneizel");
    boring_list.add_employee("Diethard");

    boring_list.add_subordinate("Lelouch", "Kallen");
    boring_list.add_subordinate("Lelouch", "Ohgi");
    boring_list.add_subordinate("Schneizel", "Cornelia");

    std::cout << "Initial employee list:" << '\n';
    boring_list.print_all();

    boring_list.delete_subordinate("Lelouch", "Kallen");
    boring_list.delete_employee("Diethard");

    std::cout << "Updated employee list:" << '\n';
    boring_list.print_all();

    return 0;
}
