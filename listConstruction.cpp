/* Name: Zerihun Tilahun Eshete
   ID: TD 3767 */
#include<iostream>
using namespace std;
#include "2020_10_13_modifiedArrayImplementation.cpp"

const int MAX = 100;
enum{ADD_FLOAT = 1, REMOVE_FLOAT, SEARCH, UPDATE, DISPLAY, COUNT, CLEAR, COPY, EXIT};

int main()
{
    BaseArray<float> base;
    initializeBaseArray(base, MAX);
    LinkedList<float>list;
    createList(list, &base, true);

    int choice;
    do
    {
        choice = menu();
        switch(choice)
        {
            case ADD_FLOAT:
                float newData;
                int size;
                bool inserted = false;
                cout<<"How many numbers would you like to insert? ";
                cin>>size;
                for(int i=0;i<size;i++)
                {
                    cout<<"Input the number you would like to insert: ";
                    cin>>newData;
                    inserted = insert(list, newData);
                    if(inserted == false)
                        resizeBaseArray(array,MAX*2);
                }
        }
    } while (/* condition */);
    

    float newData;
    cout<< "Insert new data ";
    cin>>newData;
    insert(list, newData);

    cout<< "Insert new data ";
    cin>>newData;
    insert(list, newData);

    cout<< "Insert new data ";
    cin>>newData;
    insert(list, newData);

    // float deleteData;
    // cout<< "Insert data to delete";
    // cin>>deleteData;
    // remove(list, deleteData);

    cout<< "Insert new data ";
    cin>>newData;
    insert(list, newData);

    cout<< "Insert new data ";
    cin>>newData;
    insert(list, newData);

    float deleteData;
    cout<< "Insert data to delete";
    cin>>deleteData;
    remove(list, deleteData);

    cout<<list.head<<endl;
    displayList(list);
    

}