// You are given N floor and K eggs. You have to minimize the number of times you
// have to drop the eggs to find the critical floor where critical floor means the
// floor beyond which eggs start to break.

// Assumptions of the problem:
// If egg breaks at ith floor then it also breaks at all greater floors.
// If egg does not break at ith floor then it does not break at all lower floors.
// Unbroken egg can be used again.

// Note: You have to find minimum trials required to find the critical floor not the critical floor.

// Recursion
int solve(int n, int k){

    if(n==0 || n==1) return n;
    if(k==1) return n;

    int mn = INT_MIN;
    for(int i=1;i<=n;i++){
        // Min # of Attempt i.e worst case
        int temp = 1+max(solve(i-1,k-1),solve(n-i,k))
        mn = min(mn,temp);
    }
    return mn;
}

// Memoization
int dp[N+1][k+1];
memset(dp,sizeof(dp),-1);

int solve(int n, int k){

    if(n==0 || n==1) return n;
    if(k==1) return n;

    if(dp[n][k]!=-1) return dp[n][k];

    int mn = INT_MIN;
    for(int i=1;i<=n;i++){
        // Min # of Attempt i.e worst case
        int low,high;
        if(dp[i-1][k-1]!=-1) low = dp[i-1][k-1];
        else low = solve(i-1,k-1);

        if(dp[n-i][k]!=-1) high = dp[n-i][k];
        else high = solve(i-1,k-1);

        int temp = 1+max(low,high);
        mn = min(mn,temp);
    }
    return dp[n][k]=mn;
}