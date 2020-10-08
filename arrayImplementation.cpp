#include<iostream>
using namespace std;

const int NIL = -1;

template <class T>
struct node//Create a node
{
    T data;
    int next;
};

template <class T>
struct BaseArray//Create a dynamic array to hold the linked list
{
    node<T> *base;
    int capacity;
    int available;
};

template <class T>
bool initializeBaseArray(BaseArray<T> &array, int capacity)//Function initializes the base array
{
    array.base = new(nothrow)node<T>[capacity];
    if(array.base)
    {
        array.capacity = capacity;
        for(int i=0;i<=array.capacity-2;i++)
        {
            array.base[i].next = i+1;
        }
        array.base[array.capacity-1].next = NIL;
        array.available = 0;
        return true;
    }

    return false;
}

template <class T>
bool isFull(BaseArray<T> array)//Function checks if the base array is full or not
{
    return array.available == NIL;
}

template <class T>
int getNode(BaseArray<T> &array)
{
    int p=NIL; 
    if(array.available != NIL)  //if(!isFull(array))
    {
        p=array.available; // P takes the address[index] of the released node from the available linked list
        array.available = array.base[array.available].next;
    }

    return p;
}

template <class T>
void returnNode(BaseArray<T> &array, int p) // p is the index of which node we would like to delete
{
    array.base[p].next = array.available;
    array.available = p;
}

template<class T>
bool resizeBaseArray(BaseArray<T> &array, int capacity)
{
    T *resize = new(nothrow)
}