/*
 * https://www.hackerrank.com/challenges/queue-using-two-stacks/problem
 */

#include <stack>


class Queue
{
    Queue() {}

    void enqueue(const long data) {
        _aux_stack.push(data);
    }

    void dequeue() {
        if (_main_stack.empty()) {
            restore();
        }
        _main_stack.pop();
    }

    long top() {
        if (_main_stack.empty()) {
            restore();
        }
        return _main_stack.top();
    }

private:
    void restore() {
        while (!_aux_stack.empty()) {
            _main_stack.push(_aux_stack.top());
            _aux_stack.pop();
        }
    }

    std::stack<long> _main_stack;
    std::stack<long> _aux_stack;
};
