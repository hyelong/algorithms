void compute_lps(string pattern, int lps[]){
    int m = pattern.size();
    int i = 1;
    int j = 0;
    while(i<m){
        if(pattern[j]==pattern[i]){
            j++;
            lps[i]=j;
            i++;
        }
        else{
            if(j>0){
                j = lps[j-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
    
}
int strStr(string haystack, string needle) {
    int m = needle.size();
    int n = haystack.size();
    if(m==0 && n==0) return 0;
    if(n==0) return -1;
    if(m==0) return 0;
    if(n < m) return -1;
    int lps[m]={0};
    compute_lps(needle, lps);
    int i=0;
    int j=0;
    while(i<n){
        if(haystack[i]==needle[j]){
            j++;
            i++;
            if(j==m) return i-m;
        }
        else{
            if(j>0)
                j = lps[j-1];
            else i++;
        }
    }
    return -1;
}