struct CHT{
  deque<pair<ld, ld>> dq;

  ld intersect(pair<ld, ld> a, pair<ld, ld> b){
    return (a.s-b.s)/(b.f-a.f);
  }

  bool check(ld m, ld b){ // account for parallel lines
    if(sz(dq)==0) return false;
    if(sz(dq)==1 && m==dq.back().f) return b>dq.back().s;
    else if(sz(dq)==1) return false;
    if(m!=dq.back().f) return intersect(dq.back(), dq[sz(dq)-2])>=intersect(dq[sz(dq)-2], {m, b});
    return b>dq.back().s;
  }

  void insert(ld m, ld b){ // **non-decreasing slopes
    while(check(m, b)) dq.pop_back();
    dq.push_back({m, b});
  }

  ld get_max(ld x){ // **increasing x
    while(sz(dq)>1 && intersect(dq[0], dq[1])<=x) dq.pop_front();
    ld m=dq.front().f;
    ld b=dq.front().s;
    return m*x+b;
  }
};