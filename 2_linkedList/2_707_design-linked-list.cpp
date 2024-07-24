// 707. 设计链表
// https://leetcode.cn/problems/design-linked-list/
// 中等
// 你可以选择使用单链表或者双链表，设计并实现自己的链表。
// 单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针 / 引用。
// 如果是双向链表，则还需要属性 prev 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。

// 实现 MyLinkedList 类：
// MyLinkedList() 初始化 MyLinkedList 对象。
// int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1 。
// void addAtHead(int val) 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
// void addAtTail(int val) 将一个值为 val 的节点追加到链表中作为链表的最后一个元素。
// void addAtIndex(int index, int val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将 不会插入 到链表中。
// void deleteAtIndex(int index) 如果下标有效，则删除链表中下标为 index 的节点。

// 示例：
// 输入
// ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
// [[], [1], [3], [1, 2], [1], [1], [1]]
// 输出
// [null, null, null, null, 2, null, 3]
// 解释
// MyLinkedList myLinkedList = new MyLinkedList();
// myLinkedList.addAtHead(1);
// myLinkedList.addAtTail(3);
// myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
// myLinkedList.get(1);              // 返回 2
// myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
// myLinkedList.get(1);              // 返回 3

// 提示：
// 0 <= index, val <= 1000
// 请不要使用内置的 LinkedList 库。
// 调用 get、addAtHead、addAtTail、addAtIndex 和 deleteAtIndex 的次数不超过 2000 。


// 707. 设计链表
// 在链表类中实现这些功能：
// get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回 - 1。
// addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
// addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
// addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val 的节点。
// 如果 index 等于链表的长度，则该节点将附加到链表的末尾。
// 如果 index 大于链表长度，则不会插入节点。
// 如果 index 小于 0，则在头部插入节点。
// deleteAtIndex (index)：如果索引 index 有效，则删除链表中的第 index 个节点。

#include <iostream>
using namespace std;

class MyLinkedList {
public:
    MyLinkedList() {

    }
    
    int get(int index) {

    }
    
    void addAtHead(int val) {

    }
    
    void addAtTail(int val) {

    }
    
    void addAtIndex(int index, int val) {

    }
    
    void deleteAtIndex(int index) {

    }
};


class MyLinkedList
{
    // 定义链表节点
    struct ListNode
    {
        int val;
        ListNode * next;
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x, ListNode * next) : val(x), next(next) {}
    };
private:
    int _size;
    ListNode * _dummyHead;
public:
    MyLinkedList()
    {
        _size = 0;
        _dummyHead = new ListNode();
    }
    // 获取链表中第 index 个节点的值。如果索引无效，则返回 - 1。
    int get(int index)
    {
        if(index >= _size || index < 0)
        {
            return -1;
        }
        ListNode * current = _dummyHead;
        while(index--)
        {
            current = current->next;
        }
        return current->next->val;
    }

    // 在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
    void addAtHead(int val)
    {
        _size++;
        ListNode * newNode = new ListNode(val);
        newNode->next = _dummyHead->next;
        _dummyHead->next = newNode;
    }

    // 在链表最后面添加一个节点
    void addAtTail(int val)
    {
        _size++;
        ListNode * newNode = new ListNode(val);
        ListNode * current = _dummyHead;
        while(current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }

    // 在第index个节点之前插入一个新节点，例如index为0，那么新插入的节点为链表的新头节点。
    // 如果index 等于链表的长度，则说明是新插入的节点为链表的尾结点
    // 如果index大于链表的长度，则返回空
    // 如果index小于0，则置为0，作为链表的新头节点。
    void addAtIndex(int index, int val)
    {
        if(index > _size)
        {
            return;
        }
        if(index < 0)
        {
            index = 0;
        }
        ListNode * newNode = new ListNode(val);
        ListNode * current = _dummyHead;
        while(index--)
        {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
        _size++;
    }

    // deleteAtIndex (index)：如果索引 index 有效，则删除链表中的第 index 个节点。
    void deleteAtIndex(int index)
    {
        if(index >= _size || index < 0)
        {
            return;
        }
        ListNode * current = _dummyHead;
        while(index--)
        {
            current = current->next;
        }
        ListNode * temp = current->next;
        current->next = current->next->next;
        delete temp;
        _size--;
    }

};




// 20:05--20:09(读题)--20:54--21:21(改错)--21:43(调试改错，提交后遇到如下错误)--21:54
// 输入
// ["MyLinkedList","addAtHead","addAtHead","addAtHead","addAtIndex","deleteAtIndex","addAtHead","addAtTail","get","addAtHead","addAtIndex","addAtHead"]
// [[],[7],[2],[1],[3,0],[2],[6],[4],[4],[4],[5,0],[6]]
// 输出
// [null,null,null,null,null,null,null,null,-1,null,null,null]
// 预期结果
// [null,null,null,null,null,null,null,null,4,null,null,null]

class MyLinkedList {
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* node) : val(x), next(node) {}
    };
    int _size;
    ListNode* _head;

public:

    // MyLinkedList() 初始化 MyLinkedList 对象。
    MyLinkedList() {
        _size = 0;
        // 头节点是个虚拟节点
        _head = new ListNode();     // ***
    }

    // int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1 。
    int get(int index) {
        if(index >= _size || index < 0) {    //  >=     ***
            return -1;
        }
        ListNode* cur = _head;  // 一直更新到 index 前一个节点
        while(index > 0) {
            cur = cur->next;
            index--;
        }
        return cur->next->val;
    }

    // void addAtHead(int val) 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
    void addAtHead(int val) {
        ListNode* newNode = new ListNode(val);
        newNode->next = _head->next;
        _head->next = newNode;
        _size++;
    }
    
    // void addAtTail(int val) 将一个值为 val 的节点追加到链表中作为链表的最后一个元素。
    void addAtTail(int val) {
        if(_size == 0) {
            addAtHead(val);
        }
        else {
            ListNode* cur = _head;
            while(cur->next != nullptr) {   // 一直更新到末尾
                cur = cur->next;
            }
            cur->next = new ListNode(val);
            _size++;
        }
    }
    
    // void addAtIndex(int index, int val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。
    // 如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将 不会插入 到链表中。
    void addAtIndex(int index, int val) {
        if(index > _size || index < 0) {   // >
            return;
        }
        else if(index == 0) {       // 可以处理没有节点时的情况
            addAtHead(val);
        }
        else {
            ListNode* cur = _head;  // 一直更新到 index 的前一个节点
            while(index > 0) {
                cur = cur->next;
                index--;
            }
            ListNode* temp = cur->next; // ***
            cur->next = new ListNode(val);
            cur->next->next = temp;
            _size++;
        }
    }
    
    // void deleteAtIndex(int index) 如果下标有效，则删除链表中下标为 index 的节点。
    void deleteAtIndex(int index) {
        if(index >= _size || index < 0) {   // >=
            return;
        }
        else {
            ListNode* cur = _head;  // 一直更新到 index 的前一个节点
            while(index > 0) {
                cur = cur->next;
                index--;
            }
            ListNode* temp = cur->next;
            cur->next = cur->next->next;
            _size--;
            delete temp;
        }
    }
};