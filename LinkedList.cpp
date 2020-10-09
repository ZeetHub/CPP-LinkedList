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
