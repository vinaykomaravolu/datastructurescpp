#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class LinkedListNode
{
public:
    T val;
    LinkedListNode<T> *next;
    LinkedListNode(T val, LinkedListNode<T> *next = nullptr)
    {
        this->val = val;
        this->next = next;
    }
};

template <typename T>
class LinkedList
{
public:
    LinkedList()
    {
    }

    void push(T val)
    {
        LinkedListNode<T> *node = new LinkedListNode<T>(val);
        if (!head)
        {
            head = node;
            tail = head;
            this->count++;

            return;
        }
        tail->next = node;
        tail = node;
        this->count++;
    }

    void pop()
    {
        if (!head)
        {
            return;
        }
        if (head && this->count == 1)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
            this->count--;
            return;
        }
        LinkedListNode<T> *curr = head;
        while (curr->next)
        {
            if (curr->next == tail)
            {
                delete tail;
                curr->next = nullptr;
                tail = curr;
                this->count--;
                return;
            }
            curr = curr->next;
        }
    }

    T front()
    {
        if (!tail)
        {
            throw invalid_argument("Linked list empty");
        }
        return tail->val;
    }

    void insert(T val, int index)
    {
        if (!head)
        {
            LinkedListNode<T> *node = new LinkedListNode<T>(val);
            head = node;
            tail = head;
            this->count++;
            return;
        }
        if (index > this->count || index < 0)
        {
            throw invalid_argument("index out of bounds");
        }
        LinkedListNode<T> *node = new LinkedListNode<T>(val);
        if (index == 0)
        {
            node->next = head;
            head = node;
            this->count++;
        }
        else if (index == this->count)
        {
            tail->next = node;
            tail = node;
            this->count++;
        }
        else
        {
            int i = 1;
            LinkedListNode<T> *curr = head->next;
            LinkedListNode<T> *prev = head;
            while (curr)
            {
                if (i == index)
                {
                    prev->next = node;
                    node->next = curr;
                    this->count++;
                    return;
                }
                curr = curr->next;
                prev = prev->next;
                i++;
            }
        }
    }

    void remove(int index)
    {
        if (!head)
        {
            return;
        }
        if (index == 0)
        {
            LinkedListNode<T> *curr = head->next;
            delete head;
            head = curr;
            this->count--;
        }
        else if (index == this->count)
        {
            this->pop();
        }
        else
        {
            int i = 1;
            LinkedListNode<T> *curr = head->next;
            LinkedListNode<T> *prev = head;
            while (curr)
            {
                if (i == index)
                {
                    prev->next = curr->next;
                    delete curr;
                    this->count--;
                    return;
                }
                curr = curr->next;
                prev = prev->next;
                i++;
            }
        }
    }

    void display()
    {
        LinkedListNode<T> *curr = head;
        cout << endl;
        while (curr)
        {
            cout << curr->val << " ";
            curr = curr->next;
        }
        cout << endl;
    }

    int size()
    {
        return this->count;
    }

    bool empty()
    {
        return this->count == 0;
    }

private:
    int count = 0;
    LinkedListNode<T> *head = nullptr;
    LinkedListNode<T> *tail = nullptr;
};