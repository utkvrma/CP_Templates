static class TrieNode{
// class TrieNode{
    public:
    TrieNode* children[26];
    char data;
    bool isEnd;
    int weight;
    TrieNode (char ch, int weight){
        this->data= ch;
        this->isEnd= false;
        this->weight= weight;
        for(int x=0; x<26; x++) children[x]= nullptr;
    }
};