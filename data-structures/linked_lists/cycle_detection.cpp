/*
 * https://www.hackerrank.com/challenges/detect-whether-a-linked-list-contains-a-cycle/problem
 */

#include <set>


struct SinglyLinkedListNode
{
    SinglyLinkedListNode(int node_data) {
        this->data = node_data;
        this->next = nullptr;
    }

    int data;
    SinglyLinkedListNode *next;
};


bool has_cycle(SinglyLinkedListNode* head) {
    std::set<SinglyLinkedListNode*> visited;

    SinglyLinkedListNode* curr = head;
    while(curr) {
        if (visited.find(curr) != visited.end()) {
            return true;
        }
        visited.insert(curr);
        curr = curr->next;
    }

    return false;
}
