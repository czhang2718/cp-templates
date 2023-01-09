vector<int> pi(string s){
    int n=s.size();
    vector<int> p(n);
    for(int i=1; i<n; i++){
        int g=p[i-1];
        while(g && s[i]!=s[g]) g=p[g-1];
        p[i]=g+(s[i]==s[g]);
    }
    return p;
}

vector<int> match(string s, string t){
    vector<int> p=pi(t+'-'+s), matches;
    for(int i=p.size()-s.size(); i<p.size(); i++){
        if(p[i]==t.size()) matches.push_back(i-2*t.size());
    }
    return matches;
}