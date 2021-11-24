#include <bits/stdc++.h>

using namespace std;

class DoublyLinkedListNode {
    public:
        int data;
        DoublyLinkedListNode *next;
        DoublyLinkedListNode *prev;

        DoublyLinkedListNode(int node_data) {
            this->data = node_data;
            this->next = nullptr;
            this->prev = nullptr;
        }
};

class DoublyLinkedList {
    public:
        DoublyLinkedListNode *head;
        DoublyLinkedListNode *tail;

        DoublyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int node_data) {
            DoublyLinkedListNode* node = new DoublyLinkedListNode(node_data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
                node->prev = this->tail;
            }

            this->tail = node;
        }
};

void print_doubly_linked_list(DoublyLinkedListNode* node, string sep, ofstream& fout) {
    while (node) {
        fout << node->data;

        node = node->next;

        if (node) {
            fout << sep;
        }
    }
}

void free_doubly_linked_list(DoublyLinkedListNode* node) {
    while (node) {
        DoublyLinkedListNode* temp = node;
        node = node->next;

        free(temp);
    }
}

/*
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_DOUBLY_LINKED_LIST llist
 *  2. INTEGER data
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

// 2 4 6 8
// 5

int getPosition(DoublyLinkedListNode* head, int data)
{
    if (!head)
    {
        return 0;
    }

    int index = 0;
    DoublyLinkedListNode* temp = head;
    while (temp && temp->data < data)
    {
        ++index;
        temp = temp->next;
    }

    return index;
}

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* head, int data) 
{
    DoublyLinkedListNode* newNode = new DoublyLinkedListNode(data);

    if (!head)
    {
        head = newNode;
        return head;
    }

    int position = getPosition(head, data);
    if (position == 0)
    {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;

        return head;
    }


    DoublyLinkedListNode* prev = head;
    int i = 0;
    while (i < position - 1) 
    {
        ++i;
        prev = prev->next;
    }

    DoublyLinkedListNode* next = prev->next;
    newNode->prev = prev;
    newNode->next = next;

    prev->next = newNode;
    if (next)
    {
        next->prev = newNode;
    }

    return head;
}