#include <bits/stdc++.h>
using namespace std;

class DSU{
    public:
    vector<int> rank, sz, par;
    int ct;

    DSU(int n) : rank(n,1), sz(n,1), par(n), ct(n) {
        iota(par.begin(), par.end(), 0);
    }

    int find(int v){
        if(v==par[v]) return v;   
        // else return find(par[v]);  -> no path cum
        else return par[v]=find(par[v]); 
    }

    int unite(int a, int b){
        int p_a= find(a);
        int p_b= find(b);
        if(p_a==p_b){ 
            return p_a;
        }
        else{
            ct--;
            //----zero optimization----
            par[p_b]=p_a;
            return p_a;

            //----rank optimization----
            if(rank[p_b]>rank[p_a]){
                par[p_a]=p_b;
                return p_b;
            }
            else{
                par[p_b]=p_a;
                rank[p_a]+= (rank[p_a]==rank[p_b]);
                return p_a;
            }

            //----size optimization----
            if(sz[p_b]>sz[p_a]){
                par[p_a]=p_b;
                sz[p_b]+= sz[p_a];
                return p_b;
            }
            else{
                par[p_b]=p_a;
                sz[p_a]+= sz[p_b];
                return p_a;
            }
        }
    }
};


