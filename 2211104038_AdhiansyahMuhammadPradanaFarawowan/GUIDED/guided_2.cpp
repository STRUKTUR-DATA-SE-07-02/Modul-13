#include <iostream>
#include <string>

struct SimpleEmployee
{
    std::string name;
    SimpleEmployee *next;
    SimpleEmployee *subordinate;

    SimpleEmployee(std::string employee_name)
    {
        name = employee_name;
        next = nullptr;
        subordinate = nullptr;
    }
};

class SimpleEmployeeList
{
private:
    SimpleEmployee *head;

public:
    SimpleEmployeeList()
    {
        head = nullptr;
    }

    void add_employee(std::string name)
    {
        SimpleEmployee *new_employee = new SimpleEmployee(name);
        new_employee->next = head;
        head = new_employee;
    }

    void add_subordinate(std::string manager_name, std::string subordinate_name)
    {
        SimpleEmployee *manager = head;
        while (manager != nullptr && manager->name != manager_name)
        {
            manager = manager->next;
        }
        if (manager != nullptr)
        {
            SimpleEmployee *new_subordinate = new SimpleEmployee(subordinate_name);
            new_subordinate->next = manager->subordinate;
            manager->subordinate = new_subordinate;
        }
        else
        {
            std::cout << "Manager not found!" << '\n';
        }
    }

    void print_all()
    {
        SimpleEmployee *current = head;
        while (current != nullptr)
        {
            std::cout << "Manager: " << current->name << " -> ";
            SimpleEmployee *sub = current->subordinate;
            while (sub != nullptr)
            {
                std::cout << sub->name << " ";
                sub = sub->next;
            }
            std::cout << '\n';
            current = current->next;
        }
    }

    ~SimpleEmployeeList()
    {
        while (head != nullptr)
        {
            SimpleEmployee *temp = head;
            head = head->next;

            while (temp->subordinate != nullptr)
            {
                SimpleEmployee *subTemp = temp->subordinate;
                temp->subordinate = temp->subordinate->next;

                delete subTemp;
            }

            delete temp;
        }
    }
};

int main()
{
    SimpleEmployeeList the_list;

    the_list.add_employee("Shadow");
    the_list.add_employee("Oriana");
    the_list.add_employee("Midgar");

    the_list.add_subordinate("Shadow", "Nu");
    the_list.add_subordinate("Shadow", "Victoria");
    the_list.add_subordinate("Oriana", "Rose");

    the_list.add_subordinate("Midgar", "Alexia");
    the_list.add_subordinate("Midgar", "Iris");

    the_list.print_all();

    return 0;
}
