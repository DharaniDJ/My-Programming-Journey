// Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively.
// Below is one possible representation of A = “great”:
//  great
//    /    \
//   gr    eat
//  / \    /  \
// g   r  e   at
//            / \
//           a   t
// To scramble the string, we may choose any non-leaf node and swap its two children.

// For example, if we choose the node “gr” and swap its two children, it produces a scrambled string “rgeat”.

//     rgeat
//    /    \
//   rg    eat
//  / \    /  \
// r   g  e   at
//            / \
//           a   t
// We say that “rgeat” is a scrambled string of “great”.

// Similarly, if we continue to swap the children of nodes “eat” and “at”, it produces a scrambled string “rgtae”.

//     rgtae
//    /    \
//   rg    tae
//  / \    /  \
// r   g  ta  e
//        / \
//       t   a
// We say that “rgtae” is a scrambled string of “great”.


// Recursion
bool solve(string a, string b){

    if(a==b) return true;
    if(a.length()<=1) return false;
    int n = a.length();
    bool fl = false;
    for(int i=1;i<=n-1;i++){
    // when swapping happens
        if(solve(a.substr(0,i),b.substr(n-i,i)) && solve(a.substr(i,n-i),b.substr(0,n-i))){
            flag = true;
            break;
        }

        // when swapping not happens
        if(solve(a.substr(0,i),b.substr(0,i)) && solve(a.substr(i,n-i),b.substr(i,n-i))){
            flag = true;
            break;
        }
    }

    return flag;
}

// Memoized

unordered_map<string,int> mp

// key -> str : a+" "+b

bool solve(string a, string b){

    if(a==b) return true;
    if(a.length()<=1) return false;

    string key = a;
    key.push_back(" ");
    key.append(b);

    if(mp.find(key)!=mp.end()){
        return mp[key];
    }

    int n = a.length();
    bool fl = false;
    for(int i=1;i<=n-1;i++){
    // when swapping happens
        if(solve(a.substr(0,i),b.substr(n-i,i)) && solve(a.substr(i,n-i),b.substr(0,n-i))){
            flag = true;
            break;
        }

        // when swapping not happens
        if(solve(a.substr(0,i),b.substr(0,i)) && solve(a.substr(i,n-i),b.substr(i,n-i))){
            flag = true;
            break;
        }
    }

    return mp[key]=flag;
}