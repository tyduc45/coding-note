/*
 * @lc app=leetcode id=641 lang=cpp
 *
 * [641] Design Circular Deque
 */

// @lc code=start
#include <list>
class MyCircularDeque {
public:
    std::list<int> deque;
    int size;
    int limit;
    MyCircularDeque(int k) {
        size = 0;
        limit = k;
    }
    
    bool insertFront(int value) {
        if(isFull()){
            return false;
        }
        deque.push_front(value);
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        if(isFull())
        {
            return false;
        }
        deque.push_back(value);
        size++;
        return true;
    }
    
    bool deleteFront() {
        if(isEmpty()){
            return false;
        }
        deque.pop_front();
        size--;
        return true;
    }
    
    bool deleteLast() {
        if(isEmpty()){
            return false;
        }
        deque.pop_back();
        size--;
        return true;
    }
    
    int getFront() {
        return isEmpty() ? -1 : deque.front();
    }
    
    int getRear() {
        return isEmpty() ? -1 : deque.back();
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == limit;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */
// @lc code=end

