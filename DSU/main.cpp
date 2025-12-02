#include <iostream>
#include <vector>
using namespace std;
class DSU{
    public:
    int n;
    vector<int> parent;
    vector<int> size;
    //old way of initialization of the constructor
    DSU(int n){
        this->n = n;
        parent.resize(n);
        size.resize(n);
        for(int i=0;i<n;i++){
            size[i]=1;
            parent[i]=i;
        }
    }
    //modern constructor initialization
    // DSU(int n) : size(n), parent(n,0){
    //     for(int i=0;i<n;i++){
    //         parent[i]=i;
    //     }
    // }
    int get(int node){
        if(parent[node]==node) return node;
        return parent[node] = get(parent[node]);
    }
    void merge(int node1,int node2){
        int parentNode1 = get(node1);
        int parentNode2 = get(node2);
        if(parentNode1==parentNode2) return;
        if(size[parentNode1]>=size[parentNode2]){
            size[parentNode1]+=size[parentNode2];
            parent[parentNode2] = parentNode1;
        }
        else{
            size[parentNode2]+=size[parentNode1];
            parent[parentNode1] = parentNode2;
        }
        return;
    }
};

//this is the solution for the minimum spanning tree
int solution(int n,int m,vector<vector<int>> &edges){
    DSU* dsu = new DSU(n); // also can be initialized as DSU dsu(n)
    for(auto &it:edges) reverse(it.begin(),it.end());
    sort(edges.begin(),edges.end());
    int cost=0,count=0;
    for(int i=0;i<m;i++){
        int wt = edges[i][0] , node1 = edges[i][1], node2 = edges[i][2];
        if(dsu->get(node1)!=dsu->get(node2)){
            dsu->merge(node1,node2);
            cost+=wt;
            count++;
            if(count==n-1) return cost;
        }
    }
    return cost;
}

int main(){
    vector<vector<int>> edges = {{0, 1, 5}, {1, 2, 3}, {0, 2, 1}};
    int m = edges.size(),n=3;
    int cost = solution(n,m,edges);
    cout << cost << endl;
    return 0;
}
