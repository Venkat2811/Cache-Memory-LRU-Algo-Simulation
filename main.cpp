#include <iostream>
#include<fstream>
using namespace std;

struct CacheLine
{
    int data,blockNo;
    char processor;
    CacheLine *nxt;
};

class Cache
{
    int total,ccount,hits,misses;
    CacheLine *head;

public:

    Cache()
    {
        hits=misses=ccount=0;
        total=5;
        head=NULL;
    }

    void insert(int a, int b , char proc)//in the beginning
    {

        CacheLine *temp=new CacheLine;
        temp->data=a;
        temp->blockNo=b;
        temp->processor=proc;
        temp->nxt=NULL;

        if(ccount==0)
            head=temp;
        else
        {
            CacheLine *walker=head;
            temp->nxt=walker;
            head=temp;

        }

       ccount++;

    }

    void rearrange(CacheLine *target)
    {
       if(target!=head)
       {
           CacheLine *pre=head;

        while(pre->nxt!=target)
            pre=pre->nxt;

        pre->nxt=target->nxt;
        target->nxt=head;
        head=target;
       }
    }

void leastRecentlyUsed( char proc) //LRU
{
    int flag=0;
    CacheLine *walker=head,*target;

    while(walker!=NULL)
    {
        if(walker->processor==proc)
        {
            target=walker;
            flag=1;
        }
      walker=walker->nxt;
    }

    if(flag==0)
    {
        cout<<"\n No same processor content.. No other go.. Replacing LRU cache line....";

        walker=head;
        while(walker->nxt->nxt!=NULL)
          walker=walker->nxt;

          CacheLine *dltptr=walker->nxt;
          walker->nxt=NULL;
          delete dltptr;
    }
     else if(flag==1)
    {
        cout<<"\n There is a Cache line with same processor....";

        walker=head;
        if(target!=head)
        {

        while(walker->nxt!=target)
              walker=walker->nxt;

        walker->nxt=target->nxt;
        delete target;
        }
        else
        {
         head=target->nxt;
        delete target;
        }
    }

    ccount--;
}
    void search(int a, int b , char proc)
    {
        CacheLine *walker=head;
        int flag=0;
        while(walker!=NULL)
        {
            if((walker->processor==proc)&&(walker->blockNo==b)&&(walker->data==a))
            {
                flag=1;
                break;
            }
            else
                walker=walker->nxt;
        }

        if(flag==1)
        {
            cout<<"\n CACHE HIT.... ";
              rearrange(walker);
             hits++;

        }
        else
            {
                if(ccount<total)
                {
                     cout<<"\n CACHE MISS.. There is an empty cache line to be filled...";
                     insert(a,b,proc);

                }

                else
                    {

                cout<<"\n CACHE MISS..There is no empty cacheline to be filled... going for replacement...";
                leastRecentlyUsed(proc);
                insert(a,b,proc);
                }
              misses++;
        }
    }
    void display()
    {
        CacheLine *walker=head;

        while(walker!=NULL)
        {
            cout<<"\n **"<<walker->blockNo<<"     "<<walker->data<<"     "<<walker->processor;
            //cout<<"     "<<walker->nxt;
            walker=walker->nxt;
        }

        cout<<"\nCACHE HITS      :"<<hits;
        cout<<"\nCACHE MISSES    :"<<misses<<endl;

    }



};

int main()
{
    int i,data,block,s;
    char proc,c='y';
    Cache o;

    cout<<"\n ******CACHE SIMULATION******"<<endl<<endl;
    cout<<"\n Input for processing is fed by user through console..."<<endl;
   // cout<<"\n Input for processing is fed through a text file called 'CacheInput.txt'.."<<endl<<endl;
    cout<<"\n Format is....  Main_Memory_Block_No   Cache_Data  Processor_Name"<<endl<<endl;
    cout<<"\n *****PRESS 1 TO CONTINUE*****"<<endl<<endl;
    cin>>i;
/*
    ifstream FeedFile("CacheInput.txt");

    while(FeedFile >> block >> data >> proc)
    {
         o.search(data,block,proc);
         o.display();
    }
    */

 do            //FOR MANUAL FEED
    {
        cout<<"\n Enter 1 for processing 2 to quit..";
        cin>>s;
        switch(s)
        {
            case 1:cin>>block>>data>>proc;
                   o.search(data,block,proc);
                   o.display();
                    break;
            case 2:
                    c='n';
                    break;

        }
    }while(c!='n');



}
