#include<bits/stdc++.h>
using namespace std;
class Hash
{   private:
    int** arr;
    int size;
    public:
    Hash(int size)
    {
        this->size=size;
        arr=new int*[size];
        for(int i=0;i<size;i++)
        {
            arr[i]=new int[2];
        }
        for(int i=0;i<size;i++)
        {
            for(int j=0;j<2;j++)
            {
                arr[i][j]=-1;
            }
        }
    }
   void insert(int key)
    {
       int c=key%10;
        if(arr[c][0]==-1)
        {
            arr[c][0] = key;
        } 
        else if (arr[c][0]!=-1 && arr[c][0]%10==c)
        {
            if(arr[c][1]==-1)
            {
                int index = c+1;
                while(true)
                {
                    if(arr[index][0]==-1)
                    {
                        arr[index][0] = key;
                        arr[c][1] = index;
                        break;
                    } 
                    else 
                    {
                        if(index == 9)
                        {
                            index =0;
                        } else 
                        {
                             index++;
                        }
                    }
                }
            } else 
            {
                int index=c;
                int prev =c;
                while(true){
                    if(arr[index][1]!=-1)
                    {
                        index = arr[index][1];
                        prev = index;
                    } else 
                    {
                        while(arr[index][0]!= -1)
                        {
                            if(index == 9)
                            {
                                index =0;
                            } else 
                            {
                                index++;
                            }
                        }
                        arr[index][0] = key;
                        arr[prev][1] = index;
                        break;
                    }
                }
            }
        } 
        else if(arr[c][0]!=-1 && arr[c][0]%10!=c) 
        {
            int index = c+1;
            while(true)
            {
                if(arr[index][0]==-1)
                {
                        arr[index][0] = key;
                        break;
                } else 
                {
                    if(index == 9)
                    {
                        index =0;
                    } else 
                    {
                        index++;
                    }
                }
            }
        }
            
            

            
        
    }
  
   
   
    void display()
    {
        for(int i=0;i<size;i++)
        {    
                cout<<arr[i][0]<<" "<<arr[i][1]<<endl;
            
        }
    }
    
};
int main()
{
    Hash aj(10);
    int size;
    cout<<"Enter the size of the Hash Table"<<endl;
    cin>>size;
    int flag=1;
    while(flag)
    {
        cout<<"1 insert"<<endl;
       
        cout<<"2 Display"<<endl;
        
        cout<<"3 Exit"<<endl;
        int co;
        cin>>co;
        cout<<""<<endl;
        if(co==1)
        {
            int k;
            cout<<"Enter the key to be insereted "<<endl;
            cin>>k;
            aj.insert(k);

        }
       
        else if(co==2)
        {
            aj.display();
        }
       
        else if(co==3)
        {
            flag=0;
        }
    }

}