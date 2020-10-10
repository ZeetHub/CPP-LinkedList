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
static int insertSlot(LinkedList<T> list, int p)//This function is used only when dealing with a sorted list. Also note that the list is assed here by value. 
{
    //return a pointer to the preceding element after which node p is to be inserted. 
    int found=0;
    int prev=NIL;
    while(list.head != NIL && !found)
    {
        if(list.array->base[list.head].data < list.array->base[p].data)
        {
            prev = list.head;
            list.head = list.array->base[list.head].next; //Why wouldn't this distroy the list as the head is traversing with each loop?
        }
        else
        {
            found = 1;
        }
    }
    return prev;
}



template <class T>
static void insertNode(LinkedList<T> &list, int p, int prev)
{
    //insert a new node pointed by p after a node pointed by prev
    if(list.head == NIL)
    {
        list.array->base[p].next = NIL;//vs list.array.base[p]->next = NIL;
        list.head=list.tail=p;
    }
    else if(prev == NIL)
    {
        list.array->base[p].next = list.head;//vs list.array.base[p]->next = list.head;
        list.head = p;
    }
    else
    {
        list.array->base[p].next = list.array->base[prev].next;
        list.array->base[prev].next = p;
        if(prev == list.tail)
            list.tail = p;
    }
    
}

///////////////////////////////////////////////////
template <class T>
bool insert(LinkedList<T> &list, T newData)//function that the user of the program uses
{
    int p=NIL, prev;
    p=getNode(*(list.array));
    if(p != NIL)
    {
        list.array->base[p].data = newData;
        if(list.sorted == false)
            prev = list.tail;
        else
            prev = insertSlot(list, p);
        insertNode(list, p, prev);
        return true;
    }
    else
        return false;
}

/////////////////////////////////////////////////////
template <class T>
static int deleteNode(LinkedList<T> &list, int prev)
{
    int p;
    //Delete the node preceded by the node pointed by prev
    //If prev=-1, then delete the node pointed by the head
    if(list.head==list.tail)
    {
        p=list.head;
        list.head=list.tail=NIL;
    }
    else if(prev == NIL)
    {
        p=list.head;
        list.head = list.array->base[list.head].next;
    }
    else
    {
        p=list.array->base[prev].next;
        list.array->base[prev].next = list.array->base[p].next;//Does this work?
        if(list.array->base[prev].next == list.tail)
            list.tail = prev;
    }
    return p;
}

template <class T>
static bool nodeToDelete(LinkedList<T>&list, T targetData, int &prev)//This function efficiently works for unsorted list. Modify this to work on a sorted list too.
{
    int found, newHead;
    prev = NIL;
    found = false;
    while(!found && list.head !=NIL)
    {
        if(list.array->base[list.head].data != targetData)
        {
            prev = list.head;
            list.head = list.array->base[list.head].next;
        }
        else
        {
            found = true;
        }
    }

    return found;
}

template <class T>
bool remove(LinkedList<T> &list, T targetData)
{
    int p, prev;
    if(nodeToDelete(list, targetData, prev))
    {
        p=deleteNode(list, prev);
        returnNode(*(list.array), p);
        return true;
    }

    return false;
}