#include <bits/stdc++.h>
using namespace std;
#include "trieClass.cpp"

TrieNode* insertChar(TrieNode *head, char ch, bool soloChar=false){
    int index= ch-'a';
    if(head->children[index]==NULL){
        TrieNode* newNode= new TrieNode(ch, -1);
        head->children[index]= newNode;
        newNode->isEnd= soloChar;
    }
    
    return head->children[index];
}

void insertString(TrieNode *head, string s, int weight=0){
    int n= s.size();
    TrieNode* current= head;
    for(int x=0; x<n; x++){
        current= insertChar(current, s[x]);
    }
    current->isEnd= true;
    current->weight= weight;
}

TrieNode* findChar(TrieNode *head, char ch ){
    return head->children[ch-'a'];
}

bool findString(TrieNode *head, string s){
    int n= s.size();
    TrieNode* current= head;
    for(int x=0; x<n; x++){
        current= findChar(current, s[x]);
        if(current== NULL) return false;
    }

    return current->isEnd;
}

TrieNode* findPrefix(TrieNode *head, string s){
    int n= s.size();
    TrieNode* current= head;
    for(int x=0; x<n; x++){
        current= findChar(current, s[x]);
        if(current== NULL) return NULL;
    }
    return current;
}

void fetchWords( vector<pair<string,int>>& words, TrieNode* head, string& curr){
    if(head->isEnd) words.push_back({curr, head->weight});

    for(int x=0; x<26; x++){
        auto ptr= head->children[x];
        if(ptr==nullptr) continue;

        curr+= ('a'+x);
        fetchWords(words, ptr, curr);
        curr.pop_back();
    }
}

int main() {
    TrieNode* root = new TrieNode('-',-1);

    vector<pair<string,int>> words = {
        {"apple", 70}, {"app", 100}, {"apply", 35}, {"apex", 15}, {"bat", -1}, {"ball", -2}, {"batman", 0}, {"bark", -100}
    };

    for (const auto& [word, wt] : words) {
        insertString(root, word, wt);
    }

    string prefix;
    cout << "Enter prefix to search: \n";
    cin >> prefix;

    vector<pair<string,int>> matches;
    TrieNode* startingPoint= findPrefix(root, prefix);
    if(startingPoint == nullptr){
        cout << "No matches found.\n";
    } else{
        fetchWords(matches, startingPoint, prefix);

        if (matches.empty()) {
            cout << "No matches found.\n";
        } else {
            cout << "Words with prefix:\n";
            sort(matches.begin(), matches.end(), [](pair<string, int>&a, pair<string, int>&b){
                return a.second>b.second;
            });
            for (const auto& [w,_] : matches) {
                cout << w << '\n';
            }
        }
    }

    return 0;
}
