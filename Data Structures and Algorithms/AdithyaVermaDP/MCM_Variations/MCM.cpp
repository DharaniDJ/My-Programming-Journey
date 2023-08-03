// arr[] : {40,20,30,10,30}

// Ai - arr[i-1]*arr[i] , starts from 1 and ends at n-1

// A1 - 40*20
// A2 - 20*30
// A3 - 30*10
// A4 - 10*30

// Recursion
// solve(arr,i,j) = (arr[i-1]*arr[i]),.........(arr[j-1]*arr[j]);
// k can loop from i to j-1, and compute solve(arr,i,k) and solve(arr,k+1,j)
// k can loop from i+1 to j, and compute solve(arr,i,k-1) and solve(arr,k,j)
int solve(int arr[], int i, int j){
    if(i>=j) return 0;

    int ans = INT_MAX;
    for(int k=i;k<j;k++){
        int temp = solve(arr,i,k)+solve(k+1,j)+arr[i-1]*arr[k]*arr[j];
        ans = min(ans,temp);
    }
    return ans;
}

// Bottom-up DP (Memoization)
vector<vector<int>> dp(n,vector<int>(n,-1));

int solve(int arr[], int i, int j){
    if(i>=j) return 0;

    if(dp[i][j]!=-1) return dp[i][j];

    int ans = INT_MAX;
    for(int k=i;k<j;k++){
        int temp = solve(arr,i,k)+solve(k+1,j)+arr[i-1]*arr[k]*arr[j];
        ans = min(ans,temp);
    }
    return dp[i][j]=ans;
}