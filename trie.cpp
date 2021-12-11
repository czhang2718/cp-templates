// 11/11/2021
// trie implementation with array
// N = MAX total # chars among all strings
const int N=400000;
int nex[N][26];
int cnt[N];
int cur;

void insert(string s){
  int d=0;
  for(int i=0; i<s.size(); i++){
    if(nex[d][s[i]-'a']) d=nex[d][s[i]-'a'];
    else{
      nex[d][s[i]-'a']=++cur;
      d=cur;
    }
  }
  cnt[d]++;
}

void search(int i){
  int x=0;
  while(i<n && nex[x][t[i]-'a']){
    x=nex[x][t[i]-'a'];
    // visit x = node on path
    i++;
  } // break when no longer any string matches (at leaf)
}