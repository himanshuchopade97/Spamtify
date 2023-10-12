//music playlist manager
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <Windows.h>
#include "MMSystem.h"

using namespace std;

class node
{
    public:
        node *left;
        int data;
        node *right;
}
class song
{

}
class playlist : public song
{
    node *head,*listptr;
    public:
        playlist()
        {
            head=listptr=NULL;
        }   
        
        

}
