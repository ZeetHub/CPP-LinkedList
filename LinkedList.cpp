#include<iostream>
using namespace std;
#include "arrayImplementation.cpp"

template <class T>
struct LinkedList
{
    BaseArray<T> array;
    int head;
    int tail;
    bool sorted;
};

template <class T>
void createList(LinkedList<T> &list, BaseArray<T> *base, bool sorted=false)
{
    list.array=base;
    list.head=list.tail=NIL;
    list.sorted=sorted;
}

template <class T>
int isEmpty(LinkedList<T> list)
{
    return list.head == NIL;
}

template <class T>
void insertNode(LinkedList<T> &list, int p, int prev)
{
    //insert a new node pointed by p after a node pointed by prev
    if(list.head ==NIL)
    {
        list.array->base[p].next = NIL;//vs list.array.base[p]->next = NIL;
        list.head=list.tail=p;
    }
    else if(prev==NIL)
    {
        list.array->base[p].next = list.head;
        list.head = p;
    }
}

