#include <iostream>
#include <string>

using namespace std;

// Struktur Node untuk menyimpan data, pointer ke node berikutnya, dan pointer ke child
struct Node
{
    int data;
    Node *next;
    Node *child;

    // Constructor untuk inisialisasi node
    Node(int val) : data(val), next(nullptr), child(nullptr) {}
};

// Kelas MultiLinkedList untuk mengelola multi linked list
class MultiLinkedList
{
private:
    Node *head; // Pointer ke head list

public:
    // Constructor untuk menginisialisasi list kosong
    MultiLinkedList() : head(nullptr) {}

    // Menambahkan parent baru ke awal list
    void addParent(int data)
    {
        Node *newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Menambahkan child ke parent yang sesuai
    void addChild(int parentData, int childData)
    {
        Node *parent = head;

        // Mencari parent berdasarkan data
        while (parent != nullptr && parent->data != parentData)
        {
            parent = parent->next;
        }

        // Jika parent ditemukan, tambahkan child
        if (parent != nullptr)
        {
            Node *newChild = new Node(childData);
            newChild->next = parent->child;
            parent->child = newChild;
        }
        else
        {
            cout << "Parent not found!" << endl;
        }
    }

    // Menampilkan semua parent beserta child-nya
    void display()
    {
        Node *current = head;

        while (current != nullptr)
        {
            cout << "Parent: " << current->data << " -> ";

            Node *child = current->child;
            while (child != nullptr)
            {
                cout << child->data << " ";
                child = child->next;
            }

            cout << endl;
            current = current->next;
        }
    }

    // Destructor untuk membersihkan semua node
    ~MultiLinkedList()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;

            // Hapus semua child dari parent
            while (temp->child != nullptr)
            {
                Node *childTemp = temp->child;
                temp->child = temp->child->next;
                delete childTemp;
            }

            // Hapus parent
            delete temp;
        }
    }
};

// Fungsi utama untuk menguji MultiLinkedList
int main()
{
    MultiLinkedList mList;

    // Menambahkan parent
    mList.addParent(1);
    mList.addParent(2);
    mList.addParent(3);

    // Menambahkan child ke parent yang sesuai
    mList.addChild(1, 10);
    mList.addChild(1, 11);
    mList.addChild(2, 20);
    mList.addChild(2, 21);
    mList.addChild(3, 30);
    mList.addChild(3, 31);

    // Menampilkan hasil
    mList.display();

    return 0;
}
