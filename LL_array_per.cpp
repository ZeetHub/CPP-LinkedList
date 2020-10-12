#include<iostream>

using namespace std;

const int MAX = 100;
const int NIL = -1;

//1. Create a compound data type named node using structure to hold varaibles of double primitive type and next of int primitive type. Recall a linkedlist is a collection of nodes with each node having data and next part. See below:
struct node
{
    double data;
    int next;
};

void createList(node list[], int &head, int &avail)
{
    //3.3.1. At first, the head, which points the entry to the linked list should point to an invalid index(say NIL, see line 6). This means that the data linkedlist is empty. On the other hand the available can point at any index on the array because the array structure is free all in all. However, for convinience, we can have it to point to the first index (index 0).
    head = NIL;
    avail = 0;

    //3.3.2. In the current condition, we are saying that the data linkedlist is empty and the avaiable linkedlist whose "head"(avail) points to the first index says we have one free space. However, as the controller of the memory structure, we know that at the beginning, all space is free. So after the "head" of the available linkedlist points to the first node's index, the first node's(array element's) next variable should point to the second, the second to the third and so on until one node before the last. The last node points to NIL to show end of available linkedlist.
    for(int i=0;i<MAX-1;i++)
        list[i].next = i+1;
    list[MAX-1].next = NIL;
}

//4.1.
bool getNode(node list[], int &avail, int &pos)
{
    if(avail != NIL)
    {
        pos = avail;
        avail = list[avail].next;
        return true;
    }
    else
    {
        cout<< "No sufficient memory\n";
        return false;
    }
}

//4.2.
void insertData(node list[], int pos, double dataValue)
{
    list[pos].data = dataValue;
    list[pos].next = NIL;
}

//4.3.
int insertionSlot(const node list[], int head, int pos)
{
    bool found {false};//See the description of why we need this under the while statement.
    int prevPosition = NIL;// This is a starting assumption that the insertion is at the head. It will be changed while head != NIL(list has at least one node) and if the data to be inserted is greater than the data at which the head points to. See below:

    while(head != NIL && !found)//Although "head" at first holds the entry point to the data linked list (in which case "head != NIL" checks if data linked list has at least one node), apart from that it tracks the next node to be considered for comparison(in which case "head != NIL" checks if data linked list has reached the end). Since it came by copy from the caller function, the change here does not affect the original value. Therefore we use the boolen variable named found to keep the check on that. If this loop becomes false in the first round, it means it is inserted at the entry to the list("true" head). Therefore, "prevPosition" returns NIL. If it goes on until the end being true, it means the insertion is at the end(after the last element currently in the data linked list).Therefore, "prevPosition" returns the index of the node whose next element points to NIL. If the position of the node to be inserted is between two nodes, "found" tells us when we should stop the loop(when we find the first greater number than the data in the node to be inserted) to avoid late termination.
    {
        if(list[head].data < list[pos].data)// The varaible "pos" shows the index of the data which is neither in the available nor in the data linked list. 
        {
            prevPosition = head;//prevPosition holds the value of the index of the currently evaluated node. This is important since the data in the next node might be greater than the data of the node to be inserted. When such case occurs the previous index will be returned telling the function which inserts the node(see 4.4) to know next to which node it inserts the new node.
            head = list[head].next;
        }
        else
        {
            found = true;//shows that the previous node after which the new node is to be inserted is found before reaching the end of the list.
        }
        
    }
    
    return prevPosition;
}

//4.4.
void insertNode(node list[], int head, int slot, int pos)
{
    if(slot == NIL)//Two reasons for slot == NIL. One is that the insertion is at the head and two is that the node is the first in data linked list.
    {
        list[pos].next = head;
        head = pos;
    }
    else
    {
        list[pos].next = list[slot].next;
        list[slot].next = pos;
    }
    
}

int main()
{
    //2. Create an array of node type. An array should have a size. Create a constant integer named MAX to hold the size of the array to be created. See line 5 above. Then see below:
    node nodeArray[MAX];

    //3. Create the linked list on the array physical memory structure.
        //3.1. Remember that when we choose an array memory structure for our linkedlist we, as programmers, are responsible to manage not only the data(insertion, deletion...), but also the available(free) memory where we insert the data,how we take care of released space etc. Therefore, on the same array structure we create one linkedlist that we use to manage the free space on the memory(array) and another linkedlist to manage the data.
        //3.2. We create one varaible of int type for an entry point to the data linkedlist and another variable of int type for an entry to the available linkedlist. See below:
        
    int head, avail;
    //3.3. We can create this linked list using its own function (modular programming), so that all we need to do is call that function from main() when we want to create the linkedlists.
    createList(nodeArray, head, avail);//See line 15

    //4. Next we want to insert a new node to the data linked list. Each node will have a data and it will be inserted to the data linked list in an ascending order. The array memory structure is already used up by the available linked list. Therefore, inserting a new node to the data linked list means:
        //4.1. We have to secure a node from the available linked list. After giving up one node space, the available linked list entry should point to the next node. It should return the secured node to the caller. However if there isn't any available node, it should return false.
        //4.2. Insert the new data(data and next) in the secured node from the available linked list. Note that the node is secured from the available linked list, but it is not yet inserted to the data linked list.
        //4.3. Find out which will be the insertion slot of the new node in the data linked list by looping from the head all the way to the first element that exceeds the data to be input. Special consideration will be given if the slot is the first to be inserted in the data linked list(head = NIL) or if it is to be inserted at the head.
        //4.4. Insert the new node in the data linked list based on the following:
            //4.4.1. Insertion at the head if the data linked list is empty or if the new node has the smallest data.
            //4.4.2. Insertion between two nodes.
            //4.4.3. Insertion at the tail.
    //4.1.
    int pos;
    bool nodeSecured = false;
    nodeSecured = getNode(nodeArray, avail, pos);//see line 27.
    //4.2.
    double dataValue;
    insertData(nodeArray, pos, dataValue);//see line 43.
    //4.3.
    int slot;
    slot = insertionSlot(nodeArray, head, pos);// see line 50.
    //4.4.
    insertNode(nodeArray, head, slot, pos);//see line 63.


    
}
