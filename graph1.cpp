#include<bits/stdc++.h>
using namespace std;

//Adjancy matrix 
//undirected unweighted graph
int main(){
  int vertex,edges;
  cin>>vertex>>edges;
  // int G[vertex][vertex]={0};
  vector<vector<bool> >AdjMat(vertex,vector<bool>(vertex,0));
  int x,y;
  for(int i=0;i<<edges;i++){
    cin>>x>>y;
    AdjMat[x][y]=1;
    AdjMat[y][x]=1;
  }
  for(int i=0;i<vertex;i++){
    for(int j=0;j<vertex;j++){
      cout<<AdjMat[x][y]<<" ";
    }
    cout<<endl;
  }
}