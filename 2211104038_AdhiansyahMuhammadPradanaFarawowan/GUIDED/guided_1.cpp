#include <iostream>
#include <string>

struct Node
{
    int data;
    Node *next;
    Node *child;

    Node(int val)
    {
        data = val;
        next = nullptr;
        child = nullptr;
    }
};

class MultiLinkedList
{
private:
    Node *head;

public:
    MultiLinkedList()
    {
        head = nullptr;
    }

    void add_parent(int data)
    {
        Node *new_node = new Node(data);
        new_node->next = head;
        head = new_node;
    }

    void add_child(int parentData, int childData)
    {
        Node *parent = head;
        while (parent != nullptr && parent->data != parentData)
        {
            parent = parent->next;
        }
        if (parent != nullptr)
        {
            Node *new_child = new Node(childData);
            new_child->next = parent->child;
            parent->child = new_child;
        }
        else
        {
            std::cout << "Parent " << parentData << " not found!" << '\n';
        }
    }

    void print_all()
    {
        Node *current = head;
        while (current != nullptr)
        {
            std::cout << "Parent: " << current->data << " -> ";
            Node *child = current->child;
            while (child != nullptr)
            {
                std::cout << child->data << " ";
                child = child->next;
            }
            std::cout << '\n';
            current = current->next;
        }
    }

    // Destructor for mutli linked list
    ~MultiLinkedList()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;

            while (temp->child != nullptr)
            {
                Node *to_be_removed = temp->child;
                temp->child = temp->child->next;
                delete to_be_removed;
            }
            delete temp;
        }
    }
};

int main()
{
    MultiLinkedList the_list;

    the_list.add_parent(3);
    the_list.add_parent(5);
    the_list.add_parent(7);

    the_list.add_child(3, 415);
    the_list.add_child(3, 415);
    the_list.add_child(5, 899);
    the_list.add_child(5, 899);
    the_list.add_child(7, 721);
    the_list.add_child(1, 721);
    the_list.print_all();

    return 0;
}
