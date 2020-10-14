/* Name: Zerihun Tilahun Eshete
   ID: TD 3767 */

#include<cstdlib>
#include<iomanip>
const int NIL = -1;

//BASE ARRAY
template <class T>
struct node//Create a node
{
    T data;
    int next;
};

template <class T>
struct BaseArray
{
    node<T> *base;
    int capacity;
    int available;
};

//LINKEDLIST
template <class T>
struct LinkedList
{
    BaseArray<T> *array;
    int head;
    int tail;
    bool sorted;
};

//BASE ARRAY
template <class T>
bool initializeBaseArray(BaseArray<T> &array, int capacity);
template <class T>
bool isFull(BaseArray<T> array);
template <class T>
int getNode(BaseArray<T> &array);
template <class T>
void returnNode(BaseArray<T> &array, int p);
template <class T>
bool resizeBaseArray(BaseArray<T> &array, int newCapacity);
template <class T>
void returnList(BaseArray<T> &array, int listHead, int listTail);
template <class T>
void destroyBaseArray(BaseArray<T> &array);

//LINKEDLIST
// template <class T>
// void createList(LinkedList<T> &list, BaseArray<T>*base, bool sorted=false);
template <class T>
int isEmpty(LinkedList<T> list);
template <class T>
static void insertNode(LinkedList<T> &list, int p, int prev);
template <class T>
static int insertSlot(LinkedList<T> list, int p);
template <class T>
bool insert(LinkedList<T> &list, T newData);
template <class T>
static int deleteNode(LinkedList<T> &list, int prev);
template <class T>
static bool nodeToDelete(LinkedList<T>list, T targetData, int &prev);
template <class T>
bool remove(LinkedList<T> &list, T targetData);
template <class T>
void displayList(LinkedList<T> list);



template <class T>
bool initializeBaseArray(BaseArray<T> &array, int capacity)
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
bool isFull(BaseArray<T> array)
{
    return array.available == NIL;
}

template <class T>
int getNode(BaseArray<T> &array)
{
    int p=NIL;
    if(!isFull(array))
    {
        p=array.available; 
        array.available = array.base[array.available].next;
    }
    // else
    // {
    //     char accept;
    //     cout<<"Size full. Would you like to double the current space?(y/Y/n/N) ";
    //     cin>>accept;
    //     if(accept == 'y' || accept == 'Y')
    //         if(resizeBaseArray(array, 5))
    //             getNode(array);
    // }
    

    return p;
}

template <class T>
void returnNode(BaseArray<T> &array, int p) 
{
    array.base[p].next = array.available;
    array.available = p;
}

template<class T>
bool resizeBaseArray(BaseArray<T> &array, int newCapacity)
{
    BaseArray<T> temp;
    temp.base = new(nothrow)BaseArray<T>[newCapacity];
    if(temp.base)
    {
        for(int i=0;i<array.capacity;i++)
        {
            temp.base[i].data = array.base[i].data;
            temp.base[i].next = array.base[i].next;
        }

        delete []array.base;

        BaseArray<T> array;
        array.base = new(nothrow)BaseArray<T>[newCapacity];
        for(int i=0;i<array.capacity;i++)
        {
            array.base[i].data = temp.base[i].data;
            array.base[i].next = temp.base[i].next;
        }
        for(int i = array.capacity-1;i<newCapacity-1;i++)
        {
            array.base[i].next = i+1;
        }
        array.base[newCapacity-1].next = NIL;
        array.available = array.capacity;
        array.capacity = newCapacity;

        delete []temp.base;
        return true;
    }
    
    return false;

}

template <class T>
void returnList(BaseArray<T> &array, int listHead, int listTail)
{
    listTail = array.available; 
    array.available = listHead;
}

template<class T>
void destroyBaseArray(BaseArray<T> &array)
{
    delete [] array.base;
}

//LINKEDLIST
template <class T>
void createList(LinkedList<T> &list, BaseArray<T>*base, bool sorted=false)
{
    list.array = base;
    list.head=list.tail=NIL;
    list.sorted=sorted;
}

template <class T>
int isEmpty(LinkedList<T> list)
{
    return list.head == NIL;
}

template <class T>
static void insertNode(LinkedList<T> &list, int p, int prev)
{
    if(list.head == NIL)
    {
        list.array->base[p].next = NIL;
        list.head=list.tail=p;
    }
    else if(prev == NIL)
    {
        list.array->base[p].next = list.head;
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
            list.head = list.array->base[list.head].next;
        }
        else
        {
            found = 1;
        }
    }
    return prev;
}


template <class T>
bool insert(LinkedList<T> &list, T newData)
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

template <class T>
static int deleteNode(LinkedList<T> &list, int prev)
{
    int p;
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
        list.array->base[prev].next = list.array->base[p].next;
        if(list.array->base[prev].next == list.tail)
            list.tail = prev;
    }
    return p;
}

template <class T>
static bool nodeToDelete(LinkedList<T>list, T targetData, int &prev)
{
    int found = false, notInList = false;
    prev = NIL;
    if(list.sorted == true)
    {   
        while(!found && !notInList)
        {
            if(list.array->base[list.head].data < targetData)
            {
                prev = list.head;
                list.head = list.array->base[list.head].next;
                if(list.head == NIL)
                {
                    notInList = true;
                    return notInList;
                }
            }
            else if(list.array->base[list.head].data == targetData)
            {
                found = true;
            }
            else
            {
                notInList = true;
                return notInList;
            }
        }
    }
    else
    {
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
///////////////////////////////////////////////////////////////////////////
int menu()
{
    int choice, invalid=0;
    do
    {
        if(invalid == 1)
        {
            cout<<setfill('-')<<setw(50)<<'-'<<setfill(' ')<<endl;
            cout << "Invalid choice! Please select an appropriate number: "<<endl;
        }
        else
        {
            cout<<setfill('-')<<setw(50)<<'-'<<setfill(' ')<<endl;
            cout<< "Choose from the menu below: "<<endl;
        }
        cout<< "1. Add float\n2. Remove float\n3. Search\n4. Update\n5. Display\n6. Count\n7. Clear\n8. Copy\n9. Exit\n";
        cout<< "Enter the number of your choice: ";
        cin>>choice;
        if(choice < ADD_FLOAT || choice > EXIT)
            invalid = 1;
        else
            invalid = 0;
        system("cls");
    } while (invalid == 1);

    return choice;
    
}

template <class T>
void displayList(LinkedList<T> list)
{
    while(list.head != NIL)
    {
        cout<<list.array->base[list.head].data<<endl;
        cout<<list.array->base[list.head].next<<endl;
        list.head = list.array->base[list.head].next;
    }

}