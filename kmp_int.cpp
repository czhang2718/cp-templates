vector<int> pi(vector<int> s){
    int n=s.size();
    vector<int> p(n);
    for(int i=1; i<n; i++){
        int g=p[i-1];
        while(g && s[i]!=s[g]) g=p[g-1];
        p[i]=g+(s[i]==s[g]);
    }
    return p;
}

vector<int> match(vector<int> s, vector<int> t){
    vector<int> st=t, matches;
    st.push_back(-1);
    for(int x:s) st.push_back(x);
    vector<int> p=pi(st);
    for(int i=st.size()-s.size(); i<p.size(); i++){
        if(p[i]==t.size()) matches.push_back(i-2*t.size());
    }
    return matches;
}