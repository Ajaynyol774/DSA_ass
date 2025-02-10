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
   
    void inserting(int key,int &cnt)
    {  

          cnt++;
    int index=key%size;
    if(arr[index][0]==-1){
        arr[index][0]=key;
    }
    else if (cnt != size && index == arr[index][0] %size)
    {
        while (arr[index][1] != -1)
        {
            index = arr[index][1];
        }
        int chain_index = index;
        while (arr[index][0] != -1)
        {
            index = (index + 1) % 10;
        }
        arr[chain_index][1] = index;
        if (arr[index][0] == -1)
        {
            arr[index][0] = key;
        }
    }
    else{
        int new_index=index;
        int old_element=arr[index][0];
        arr[index][0]=key;
        int new_chain_index=arr[index][1];
        arr[index][1]=-1;
        while(arr[index][0]!=-1){
            index=(index+1)%size;
        }
        if(arr[index][0]==-1){
            arr[index][0]=old_element;
            arr[index][1]=new_chain_index;
        }
        for(int i=0; i<size; i++){
            if(arr[i][1]==new_index){
                arr[i][1]=index;
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
    
    int size;
    cout<<"Enter the size of the Hash Table"<<endl;
    cin>>size;
    Hash H(size);
    int cnt=0;
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
            int count;
            int k;
            cout<<"Enter the key to be insereted "<<endl;
            cin>>k;
            H.inserting(k,cnt);
            count++;
            // if(count==size){
            //     H.display();
            //     break;
            // }

        }
       
        else if(co==2)
        {
            H.display();
        }
       
        else if(co==3)
        {
            flag=0;
        }
    }

}