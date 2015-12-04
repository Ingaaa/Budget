#include <iostream>
#include<fstream>
#include "stdio.h"
#include "stdlib.h"
using namespace std;

fstream fin ("budget.in.txt", ios::in);
fstream fout ("budget.out.txt", ios::out);
struct node
{
    unsigned int position;
    unsigned int amount;
    node *next;
};

struct node_num
{
    short int num;
    node_num *next;
};
struct node_pos
{
    unsigned short int position;
    long long int amount;
    unsigned int total_amount;
    node_num *parent_first;
    unsigned char ministries[17];
    node *first;
};

class saraksts
{
    public:
    node *first;
    node *last;
public:
     saraksts()
    {
        first=NULL;
        last=NULL;
    };
    void add_element (unsigned int amou, unsigned int pos)
    {
        node * P=new node;
        P->position=pos;
        P->amount=amou;
        P->next=NULL;
        if (first == NULL) first = P;
        else last->next = P;
        last = P;
    };
     void print()
    {
        node * N=new node;
        N=first;
        while (N!=NULL)
        {

            N=N->next;
        }
    }
    void sort_izeja ()
    {
        if((first!=NULL) && (first->next!=NULL))
        {
            node *p=first;
            node *pasreiz=first;
            node *ieprieks=NULL;
            node *temp=NULL;
            bool a=false;
            short int skaits=0;

            while (p!=NULL)
            {
                skaits++;
                p=p->next;
            }
            for (int i=0; i<skaits; i++)
            {
                while (pasreiz->next !=NULL)
                {
                    temp=pasreiz->next;
                    if ((pasreiz->position) > (temp->position))
                    {
                        a=true;
                        pasreiz->next=temp->next;
                        temp->next=pasreiz;
                        if (ieprieks !=NULL) ieprieks->next=temp;
                        ieprieks=temp;
                        if (first==pasreiz) first=temp;
                        if(pasreiz->next==NULL) last=pasreiz;

                    }
                    else
                    {
                        ieprieks=pasreiz;
                        pasreiz=pasreiz->next;
                    }
                }

                if (a==false) break;
                else
                {
                    ieprieks=NULL;
                    pasreiz=first;
                    a=false;
                }
            }
        }
    }
    void sort_izeja_dilstosi ()
    {
        if((first!=NULL) && (first->next!=NULL))
        {
            node *p=first;
            node *pasreiz=first;
            node *ieprieks=NULL;
            node *temp=NULL;
            bool a=false;
            int skaits=0;

            while (p!=NULL)
            {
                skaits++;
                p=p->next;
            }
            for (int i=0; i<skaits; i++)
            {
                while (pasreiz->next !=NULL)
                {
                    temp=pasreiz->next;
                    if ((pasreiz->position) < (temp->position))
                    {
                        a=true;
                        pasreiz->next=temp->next;
                        temp->next=pasreiz;
                        if (ieprieks !=NULL) ieprieks->next=temp;
                        ieprieks=temp;
                        if (first==pasreiz) first=temp;
                        if(pasreiz->next==NULL) last=pasreiz;

                    }
                    else
                    {
                        ieprieks=pasreiz;
                        pasreiz=pasreiz->next;
                    }
                }

                if (a==false) break;
                else
                {
                    ieprieks=NULL;
                    pasreiz=first;
                    a=false;
                }
            }
        }
    }

};

void find_ministry (unsigned int a, unsigned int b, struct node_pos* arr[])
{
    node *L=new node;
    bool has_ministr=false;
   for(int i=a; i<b+1; i++)
    {
        if (arr[i]->position!=0)
        {
            has_ministr=false;
            for (int j=1; j<17; j++)
            {
                if(arr[i]->ministries[j]=='t')
                    has_ministr=true;
            }
            if (has_ministr==true)
            {
                L=arr[i]->first;

                while (L!=NULL)
                {
                    for (int k=1; k<17; k++)
                    {
                        if(arr[i]->ministries[k]!='f')
                        {
                            arr[L->position]->ministries[k]='t';

                        }
                    }
                    L=L->next;
                }

            }
        }
    }

}

node_pos* arr[50000];
int main()
{



  for (int i =0; i<50001; i++)
  {
      arr[i]=new node_pos;
      arr[i]->amount=0;
      arr[i]->position=0;
      arr[i]->first=NULL;
      arr[i]->parent_first=NULL;
      for (int j=0; j<17; j++)
      {
          arr[i]->ministries[j]='f';
      }
  }

  unsigned int coun=0, pos=0, paren_pos=0, child_pos=0, biggest_pos=0, ministry=0;
  long long int amou;
  bool error2=false, error1 = false, error3=false, error4=false;
  saraksts Error2_saraksts;
  saraksts Error1_saraksts;
  saraksts Error3_saraksts;
  saraksts Error4_saraksts;
  fin>>coun;
  for (int i=1; i<coun+1; i++)
  {

      fin>>pos>>amou;
      if(pos>biggest_pos)biggest_pos=pos;
      arr[pos]=new node_pos;
      arr[pos]->position=pos;
      arr[pos]->amount=amou;
      arr[pos]->total_amount=0;
      arr[pos]->ministries[pos]='t';
  }

fin>>paren_pos>>child_pos>>amou;
error1=false;
bool error21 = false;
while(fin)
    {
        //error1
        if (child_pos<=coun)
        {
            error1=true;
            Error1_saraksts.add_element(amou, child_pos);
        }

        //atrod lielāko pozīciju
        if(paren_pos>biggest_pos)biggest_pos=paren_pos;
        if(child_pos>biggest_pos)biggest_pos=child_pos;

        //skatās vai eksistē vecāka pozīcija, ja neeksistē, tad izveido
        if (arr[paren_pos]->position==0)
        {
            arr[paren_pos] = new node_pos;
            arr[paren_pos]->position=paren_pos;
        }

        //vecāka pozīcijai bērnu sarakstam pievieno bērnu
        node *T=new node;
        if (arr[paren_pos]->first == NULL)
        {
            arr[paren_pos]->first = T;
            T->next=NULL;
        }
        else
        {
            T->next=arr[paren_pos]->first;
            arr[paren_pos]->first = T;
        }
        T->amount=amou;
        T->position=child_pos;

        //Ja vēl neeksistē bērna pozīcija, tad to izveido
        if (arr[child_pos]->position==0 && child_pos>coun)
        {
        arr[child_pos] = new node_pos;
        arr[child_pos]->amount=amou;
        arr[child_pos]->position=child_pos;

        //Bērna vecāku saraktam pievieno vecāku
        node_num *N= new node_num;
        N->num=paren_pos;
        if (arr[child_pos]->parent_first==NULL)
        {
            arr[child_pos]->parent_first=N;
            N->next=NULL;
        }
        else
        {
            N->next= arr[child_pos]->parent_first;
            arr[child_pos]->parent_first=N;
        }

        }

        else if (child_pos>coun && arr[child_pos]->position!=0)
        {
            //Ja bērna pozīcija jau eksistē, tad tikai vecāku sarakstam pievieno vecāku
            node_num *N=new node_num;
            N->num=paren_pos;
            arr[child_pos]->amount=amou;
            if (arr[child_pos]->parent_first==NULL)
            {
                arr[child_pos]->parent_first=N;
                N->next=NULL;
            }
            else
            {
                N->next= arr[child_pos]->parent_first;
                arr[child_pos]->parent_first=N;
            }
        }
        else
        {

        }

        fin>>paren_pos>>child_pos>>amou;
    }
//ja ir atrasts error1, tad izdrukā un beidz programmu
if (error1 ==true)
{
    node *P = new node;
    Error1_saraksts.sort_izeja();
    P = Error1_saraksts.first;
    fout<<"Error_1";
    while (P!=NULL)
    {
        if (P->next!=NULL)
        {
            if (P->position== P->next->position)P=P->next;
        }
        fout<<" "<<P->position;
        P=P->next;
    }
    return 0;
}


    //error2
    node *L=new node;
    bool has_ministr=false;

    for(int i=1; i<biggest_pos+1; i++)
    {
        if (arr[i]->position!=0)
        {
            has_ministr=false;
            for (int j=1; j<17; j++)
            {
                if (arr[i]->ministries[j]=='t')
                    has_ministr=true;
            }
            if (has_ministr==true)
            {

                L=arr[i]->first;

                while (L!=NULL)
                {
                    for (int k=1; k<17; k++)
                    {
                        if(arr[i]->ministries[k]=='t')
                        {
                            arr[L->position]->ministries[k]='t';
                        }
                    }
                    if (L->position<arr[i]->position)
                    {
                        find_ministry(L->position, i, arr);
                    }
                    L=L->next;
                }

            }
            else
            {
            error2=true;
            Error2_saraksts.add_element(arr[i]->amount, arr[i]->position);
            }
        }
    }
  //ja ir atrasts error2, tad izdrukā un programma beidz darbu
    if (error2 ==true && error1==false)
{
    Error2_saraksts.sort_izeja();

    node *P = new node;
    P = Error2_saraksts.first;
        fout<<"Error_2";
    while (P!=NULL)
    {
        if (P->next!=NULL)
        {
            if (P->position== P->next->position)P=P->next;
        }
        fout<<" "<<P->position;
        P=P->next;
    }
    return 0;
}

//error3

//error4
long long int mistake=0;
long long int arr_total=0;
node*A=new node;
node_num *Z=new node_num;
    for (int i=biggest_pos; i>0; i--)
    {
        mistake=0;
        if(arr[i]->first!=NULL)
        {

            if(arr[i]->total_amount!=0)
            {
            mistake =arr[i]->total_amount;
            }

            A=arr[i]->first;
            arr_total=0;
            while(A!=NULL)
            {

                arr_total=arr_total+A->amount;
                A=A->next;
            }

            if (arr_total!=arr[i]->amount || mistake!=0)
            {
                if((arr_total-arr[i]->amount)!=0)
                {

                if ((arr_total-arr[i]->amount)<0)
                {
                  mistake =mistake+ (arr_total-arr[i]->amount)*(-1);
                }
                else
                {
                    mistake =mistake+ arr_total-arr[i]->amount;
                }
            }

                if (mistake>=4000000000)
            {

                error4=true;
                Error4_saraksts.add_element(i, 4000000001);

                Z=arr[i]->parent_first;

                while(Z!=NULL)
                {
                    arr[Z->num]->total_amount=4000000001;
                    Z=Z->next;
                }
            }
            else {
                arr[i]->total_amount=mistake;
                error4=true;
                Error4_saraksts.add_element(i, arr[i]->total_amount);

                Z=arr[i]->parent_first;

                while(Z!=NULL)
                {
                    arr[Z->num]->total_amount=arr[Z->num]->total_amount+mistake;
                    Z=Z->next;
                }
            }


            }
        }
}


cout<<error1<<" "<<error2<<" "<<error3<<" "<<error4<<endl;




if (error2 ==false && error1==false && error3==false && error4==true)
{
    Error4_saraksts.sort_izeja_dilstosi();
    node *P = new node;
    P = Error4_saraksts.first;
    fout<<"Error_4"<<endl;
    while (P!=NULL)
    {
        if (P->next->next!=NULL)
        {
            if(P->position==P->next->position)
            {

                //node*Temp=new node;
                //Temp=P;
               saraksts Error41_saraksts;
               Error41_saraksts.add_element(P->position,P->amount);
                while( P->position==P->next->position)
                {
                   Error41_saraksts.add_element(P->next->position,P->next->amount);
                   P=P->next;
                }
                P=P->next;
                Error41_saraksts.sort_izeja();
                node*Temp=new node;
                Temp=Error41_saraksts.first;
                while(Temp!=NULL)
                {
                    fout<<Temp->amount<<" "<<Temp->position<<endl;
                    Temp=Temp->next;
                }

            }
        }
        fout<<P->position<<" "<<P->amount<<endl;
        P=P->next;
    }
}
if (error2==false && error3==false && error1==false && error4==false)
{
    for (int i=1; i<biggest_pos+1; i++)
    {
        int c=0;
        for (int j=1; j<17; j++)
        {
            if(arr[i]->ministries[j]!='f') c++;
        }
        if (c>=2)
        {
            fout<<arr[i]->position<<" "<<arr[i]->amount;
            for (int j=1; j<17; j++)
            {
                if (arr[i]->ministries[j]!=0)
                fout<<" "<<j;
            }
            fout<<endl;

        }
    }
}


}

