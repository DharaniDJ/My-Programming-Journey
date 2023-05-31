// Evaluate Expression To True-Boolean Parenthesization Recursion
// Given a boolean expression with following symbols.
// Symbols
//     'T' --- true 
//     'F' --- false 
// And following operators filled between symbols
// Operators
//     &   ---boolean AND
//     |   --- boolean OR
//     ^   --- boolean XOR 
// Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.
// Example:
// Input: symbol[]    = {T, F, T}
//        operator[]  = {^, &}
// Output: 2
// The given expression is "T ^ F & T", it evaluates true
// in two ways "((T ^ F) & T)" and "(T ^ (F & T))"

// PROBLEM STATEMENT LINK : https://www.geeksforgeeks.org/boolean-parenthesization-problem-dp-37/

// 1. Find i and j (i=0 andd j=s.length()-1)
// 2. Base Condition
// 3. K loop
// 4. get ans from the temporary answer

// Recursion - solve(s,0,n-1,true)
int solve(string &s, int i, int j, bool isTrue){
    if(i>j) return false;
    if(i==j){
        if(isTrue){
            return s[i]=='T';
        }eles{
            return s[i]=='F';
        }
    }
    int ans = 0;
    for(int k=i+1;k<=j-1;k+=2){
        int lt = solve(s,i,k-1,true);
        int lf = solve(s,i,k-1,false);
        int rt = solve(s,k+1,j,true);
        int rf = solve(s,k+1,j,false);

        if(s[k]=='&'){
            if(isTrue){
                ans += (lt*rt);
            }else{
                ans += (lf*rt + lt*rf + lf*rf);
            }
        }else if(s[k]=='|'){
            if(isTrue){
                ans += (lt*rt + lf*rt + lt*rf);
            }else{
                ans += (lf*rf);
            }
        }else if(s[k]=='^'){
            if(isTrue){
                ans += (lf*rt + lt*rf);
            }else{
                ans += (lt*rt + lf*rf);
            }
        }
    }
    return ans;
}

// Memoization
int dp[1001][1001][2];
memset(dp,-1,sizeof(dp));
// you can also use unordered_map<string,int> mp and can store (i,j,isTrue) as string pattern

int solve(string &s, int i, int j, bool isTrue){
    if(i>j) return false;
    if(i==j){
        if(isTrue){
            return s[i]=='T';
        }eles{
            return s[i]=='F';
        }
    }
    int b = isTrue ? 1 : 0;
    if(dp[i][j][b]!=-1) return dp[i][j][b];

    // string temp = to_string(i);
    // temp.push_back(" ");
    // temp.push_back(to_string(j));
    // temp.push_back(" ");
    // temp.push_back(to_string(b));
    // if(mp.find(temp)!=mp.end()) return mp[temp];

    int ans = 0;
    for(int k=i+1;k<=j-1;k+=2){
        int lt = solve(s,i,k-1,true);
        int lf = solve(s,i,k-1,false);
        int rt = solve(s,k+1,j,true);
        int rf = solve(s,k+1,j,false);

        if(s[k]=='&'){
            if(isTrue){
                ans += (lt*rt);
            }else{
                ans += (lf*rt + lt*rf + lf*rf);
            }
        }else if(s[k]=='|'){
            if(isTrue){
                ans += (lt*rt + lf*rt + lt*rf);
            }else{
                ans += (lf*rf);
            }
        }else if(s[k]=='^'){
            if(isTrue){
                ans += (lf*rt + lt*rf);
            }else{
                ans += (lt*rt + lf*rf);
            }
        }
    }
    return dp[i][j][b]=ans;
    // return mp[temp]=ans;
}