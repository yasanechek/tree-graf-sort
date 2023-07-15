#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
using namespace std;
struct DEC
{
    struct DEC *next;
    struct DEC *prev;
    int data;
};
 
void createOne(int c);
void push_back(int c);
void push_front(int c);
void coutDEC();
void sortDec(void);
 
struct DEC *first; //указатель на начало Дека
struct DEC *last;  //указатель на конец Дека
 
int maxSize = 0; //маскимальный размер
int curSize = 0; //текущий размер
 
int main(void)
{
    int start_time = clock();
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int cur = -100; //текущий символ
 
    cout << "Введите размер Дека:" << endl;
    cin >> maxSize;
 
 
    bool flags = true;
    
    
    while(cur != '0')
    {
        if(curSize == maxSize)
        {
            cout<<endl;
            break;
        }
        
        cur=rand();
        cout<<cur<<endl;
 
        if(flags == true)
        {
            push_back(cur);
            flags = false;
        }
        else
        {
            push_front(cur);
            flags = true;
        }
        
    }
 
    cout << "Отсортированный Дек:" << endl;
    sortDec();
    coutDEC();
    int end_time = clock();
    cout<<endl;
    cout<<"SEARCH TIME IS "<<end_time-start_time<<endl;
    return 0;
}
 
void push_back(int c)
{
    curSize++;
 
    if(last) //если дек уже создан (есть его последний элемент)
    {
        struct DEC *n = (struct DEC*)malloc(sizeof(struct DEC));
        n->data = c;
        n->prev = last;
        n->next = NULL;
        last->next = n;
        last = n;
    }
    else
    {
        createOne(c); //создается первый элемент
    }
}
 
void push_front(int c)
{
    curSize++;
 
    if(first) //если дек уже создан (есть его последний элемент)
    {
        struct DEC *n = (struct DEC*)malloc(sizeof(struct DEC));
        n->data = c;
        n->prev = NULL;
        n->next = first;
        first->prev = n;
        first = n;
    }
    else
    {
        createOne(c); //создается первый элемент
    }
}
 
void createOne(int c)
{
    struct DEC *n = (struct DEC*)malloc(sizeof(struct DEC));
    n->data = c;
    n->next = NULL;
    n->prev = NULL;
    first = n;
    last = n;
}
 
void coutDEC()
{
    struct DEC *tempX = first;
    int f = 0;
    while(f < curSize)
    {
        cout << tempX->data << " \\ ";
        tempX = tempX->next;
        f++;
    }
 
 
    cout <<endl;
 
}
 
void sortDec(void)
{
        int i = 0, j;
        struct DEC *tempX = first;
        
        while(i < curSize)
        {
                if(tempX->data >= 0)
                {
                    j=0;
                    struct DEC *tempY = first;
 
                        while(j < curSize)
                        {
                                if(tempY->data >= 0 && tempX->data >= tempY->data)
                                {
                                        int x = tempX->data;
                                        tempX->data = tempY->data;
                                        tempY->data = x;
                                }
                                tempY = tempY->next;
                                j++;
                        }
                }
 
                tempX = tempX->next;
                i++;
        }
 
        cout <<endl;
}
