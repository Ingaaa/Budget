#include <iostream>
#include<fstream>
#include "stdio.h"
#include "stdlib.h"
using namespace std;

fstream fin ("budget.in.txt", ios::in);
fstream fout ("budget.out.txt", ios::out);
struct node
{
    int position;
    long int amount;
    node *next;
};

struct node_num
{
    int num;
    node_num *next;
};
struct node_pos
{
    int position;
    long int amount;
    long int total_amount;
    node_num *parent_first;
    node_num *parent_last;
    int ministries[17];
    node *first;
    node *last;
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
    void add_element (int amou, int pos)
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
            cout<<N->position<<" "<<N->amount<<endl;
            N=N->next;
        }
    }

};

void find_ministry (int a, int b, struct node_pos**arr)
{
   for(int i=a; i<b+1; i++)
    {
        if (arr[i]->position!=0)
        {
            int sum=0;
            for (int j=1; j<17; j++)
            {
                sum=sum+arr[i]->ministries[j];
            }
            if (sum>0)
            {
                node *L=new node;
                L=arr[i]->first;

                while (L!=NULL)
                {
                    for (int k=1; k<17; k++)
                    {
                        if(arr[i]->ministries[k]!=0)
                        {
                            arr[L->position]->ministries[k]=k;
                            cout<<"void"<<endl;
                            cout<<arr[i]->position<<" ";
                            cout<<L->position<<endl;
                        }
                    }
                    L=L->next;
                }

            }
        }
    }

}
int main()
{

  node_pos **arr=new node_pos*[100000];

  for (int i =0; i<100001; i++)
  {
      arr[i]=new node_pos;
      arr[i]->amount=0;
      arr[i]->position=0;
      arr[i]->first=NULL;
      arr[i]->last=NULL;
      arr[i]->parent_first=NULL;
      arr[i]->parent_last=NULL;
      for (int j=0; j<17; j++)
      {
          arr[i]->ministries[j]=0;
      }
  }

  int coun=0, amou=0, pos=0, paren_pos=0, child_pos=0, biggest_pos=0, mistake=0, ministry=0;
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
      arr[pos]->ministries[pos]=pos;
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
        if (arr[paren_pos]->first == NULL) arr[paren_pos]->first = T;
        else arr[paren_pos]->last->next = T;
        arr[paren_pos]->last = T;
        T->amount=amou;
        T->position=child_pos;
        T->next=NULL;

        //Ja vēl neeksistē bērna pozīcija, tad to izveido
        if (arr[child_pos]->position==0 && child_pos>coun)
        {
        arr[child_pos] = new node_pos;
        arr[child_pos]->amount=amou;
        arr[child_pos]->position=child_pos;

        //Bērna vecāku saraktam pievieno vecāku
        node_num *N= new node_num;
        N->num=paren_pos;
        N->next=NULL;
        if (arr[child_pos]->parent_first==NULL)
        {
            arr[child_pos]->parent_first=N;
            arr[child_pos]->parent_last=N;
        }
        else
        {
            arr[child_pos]->parent_last->next=N;
            arr[child_pos]->parent_last=N;
        }

        }

        else if (child_pos>coun && arr[child_pos]->position!=0)
        {
            //Ja bērna pozīcija jau eksistē, tad tikai vecāku sarakstam pievieno vecāku
            node_num *N=new node_num;
            N->num=paren_pos;
            N->next=NULL;
            arr[child_pos]->amount=amou;
            if (arr[child_pos]->parent_first==NULL)
            {
            arr[child_pos]->parent_first=N;
            arr[child_pos]->parent_last=N;
            }
            else
            {
            arr[child_pos]->parent_last->next=N;
            arr[child_pos]->parent_last=N;
            }
            }
        else
        {

        }

        fin>>paren_pos>>child_pos>>amou;
    }



    //error2
    for(int i=1; i<biggest_pos+1; i++)
    {
        if (arr[i]->position!=0)
        {
            int sum=0;
            for (int j=1; j<17; j++)
            {
                sum=sum+arr[i]->ministries[j];
            }
            if (sum>0)
            {
                node *L=new node;
                L=arr[i]->first;

                while (L!=NULL)
                {
                    for (int k=1; k<17; k++)
                    {
                        if(arr[i]->ministries[k]!=0)
                        {
                            arr[L->position]->ministries[k]=k;
                            cout<<arr[i]->position<<" ";
                            cout<<L->position<<endl;
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
            Error2_saraksts.add_element(arr[i]->position, arr[i]->amount);
            }
        }
    }

    for (int i=0; i<biggest_pos+1; i++)
    {
        if (arr[i]->position!=0)
        {
           cout<<"Poz: "<<arr[i]->position<<" "<<arr[i]->amount<<endl;
           for(int j=0; j<17; j++)
           {
               cout<<arr[i]->ministries[j]<<" ";
           }
           cout<<endl;
           node_num*K=new node_num;
           K=arr[i]->parent_first;
           while(K!=NULL)
           {
               cout<<K->num<<" ";
               K=K->next;
           }
           cout<<endl;
           node *O=new node;
           O=arr[i]->first;
           while(O!=NULL)
           {
               cout<<O->position<<" ";
               O=O->next;
           }
           cout<<endl;
        }

    }
    //error3
    int error3arr[17]={0};
    for (int i=1; i<biggest_pos+1; i++)
    {
        node *B=new node;
        B = arr[i]->first;
        while(B!=NULL)
        {
            if((arr[i]->position)>(B->position))
            {
               cout<< arr[i]->position<<" "<<B->position<<endl;
               //int cou=0;
                for (int j=1; j<17; j++)
                {
                    if (arr[i]->ministries[j]==arr[B->position]->ministries[j] && arr[i]->ministries[j]!=0)
                    {
                        //cou++
                        error3=true;
                        error3arr[j]=j;
                    }

                }
            }
            B=B->next;
        }
    }
//error4
node*A=new node;
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
            long int arr_total=0;
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
//                if (mistake>4000000000)
//                {
//                    mistake=4000000001;
//                }
                arr[i]->total_amount=mistake;
                error4=true;
                Error4_saraksts.add_element(arr[i]->total_amount, i);
                node_num *Z=new node_num;
                Z=arr[i]->parent_first;
                while(Z!=NULL)
                {
                    arr[Z->num]->total_amount=arr[Z->num]->total_amount+mistake;
                    Z=Z->next;
                }

            }
        }
}



if (error1 ==true)
{
    node *P = new node;
    P = Error1_saraksts.first;
    fout<<"Error_1"<<endl;
    while (P!=NULL)
    {
        fout<<P->position<<" "<<P->amount<<endl;
        P=P->next;
    }
}

if (error2 ==true && error1==false)
{
    node *P = new node;
    P = Error2_saraksts.first;
    fout<<"Error_2"<<endl;
    while (P!=NULL)
    {
        fout<<P->position<<" "<<P->amount<<endl;
        P=P->next;
    }
}

if (error2 ==false && error1==false && error3==true)
{
    fout<<"Error_3"<<endl;
    for (int i=1; i<17; i++)
    {
        if(error3arr[i]!=0)
        {
          fout<<" "<<error3arr[i];
        }
    }

}

if (error2 ==false && error1==false && error3==false && error4==true)
{
    node *P = new node;
    P = Error4_saraksts.first;
    fout<<"Error_4"<<endl;
    while (P!=NULL)
    {
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
            if(arr[i]->ministries[j]!=0) c++;
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

