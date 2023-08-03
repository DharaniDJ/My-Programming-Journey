// Given a string, a partitioning of the string is a palindrome
// partitioning if every substring of the partition is a palindrome.
// Example:
//   “aba|b|bbabb|a|b|aba” is a palindrome partitioning of “ababbbabbababa”.

bool isPalindrome(string s, int i, int j){
    while(i<j){
        if(s[i]!=s[j]) return false;
        i++;
        j--;
    }
    return true;
}

// Recursion
// solve(s,0,n-1);
// k can loop from i to j-1, and compute solve(s,i,k) and solve(s,k+1,j)
// k can loop from i+1 to j, and compute solve(s,i,k-1) and solve(s,k,j)
int solve(string s, int i, int j){
    if(i>=j) return 0;
    if(isPalindrome(s,i,j)){
        return 0;
    }

    int ans = INT_MAX;
    for(int k=i;k<=j-1;k++){
        int temp = solve(s,i,k)+solve(s,k+1,j)+1;
        ans = min(ans,temp);
    }
    return ans;
}

// Bottom-up DP (Memoization)
vector<vector<int>> dp(n,vector<int>(n,-1));

int solve(string s, int i, int j){
    if(i>=j) return 0;

    if(isPalindrome(s,i,j)){
        return 0;
    }

    if(dp[i][j]!=-1) return dp[i][j];

    int ans = INT_MAX;
    for(int k=i;k<=j-1;k++){
        int temp = solve(s,i,k)+solve(s,k+1,j)+1;
        ans = min(ans,temp);
    }
    return dp[i][j]=ans;
}

// Bottom-up DP (Memoization Optimized)
vector<vector<int>> dp(n,vector<int>(n,-1));

int solve(string s, int i, int j){
    if(i>=j) return 0;

    if(isPalindrome(s,i,j)){
        return 0;
    }

    if(dp[i][j]!=-1) return dp[i][j];

    int ans = INT_MAX;
    int left, right;
    for(int k=i;k<=j-1;k++){
        left = dp[i][k]!=-1 ? dp[i][k] : solve(s,i,k);
        dp[i][k] = left;
        right = dp[k+1][j]!=-1 ? dp[k+1][j] : solve(s,k+1,j);
        dp[k+1][j] = right;
        int temp = left+right+1;
        ans = min(ans,temp);
    }
    return dp[i][j]=ans;
}