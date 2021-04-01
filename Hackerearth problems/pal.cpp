/********
https://www.hackerearth.com/problem/algorithm/kth-palindrome-45f48699/
 
A palindromic number is a number that remains the same when its digits are reversed. Your task is to get the kth palindrome number greater than or equal to X.
 
Input format:
First line: Integer T denoting the number of test cases
Each of the following T lines:
First line: Two space-separated integers X and K
 
Output format:
Print T lines, each line contains the answer for the ith case.
 
Constraints: 1<=X,K<=10^9
SAMPLE INPUT :
4
10 23
1 12
5 26
12 11
SAMPLE OUTPUT :
232
33
212
121
Explanation :
The first 32 palindrome numbers are:
1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99, 101, 111, 121, 131, 141, 151, 161, 171, 181, 191, 202, 212, 222, 232.
 
*****/
 
#include<bits/stdc++.h>
#define ll long long int
using namespace std;
 
void print(vector<ll>v){
    for(ll i=0; i<v.size(); i++){
        cout<<v[i]<<" ";
    }
    cout<<endl;
}
 
// Function "Nth_pal_util" considers 0 as the 1st , 1 as the 2nd,... palindrome number. So first 20 palindrome numbers are
// 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99, 101,..
// But according to question we require nth palindrome number that is equal to  Nth_pal_util(n+1);
ll Nth_pal_util(ll n){
    string nt=to_string(n);
    string temp="";
    string temp2="";
    string ans="";
    ll res;
    
    ll g = log10(n);
    ll k = 2 * pow(10,g);
    ll m = 1.1 * pow(10,g);
    ll h = n/pow(10, g);
    
    if(n>=m && n<k){    //nth palindrome number has even digits
        temp="";
        temp2="";
        for(int i=1; i<nt.length(); i++){
            temp+=nt[i];
            temp2+=nt[nt.length()-i];
        }
        ans+=temp+temp2;
        res=stoll(ans);
        return res;
        
    }
    else{   //nth palindrome number has odd digits
        if(h!=1){
            int y =(nt[0]-'0')-1;
            temp+=to_string(y);
            for(int i=1; i<nt.length(); i++){
                temp+=nt[i];
            }
            ans+=temp;
            for(int i=temp.length()-2; i>=0; i--){
                ans+=temp[i];
            }
            res=stoll(ans);
            return res;
        }
        temp+=to_string(9);
        for(int i=2; i<nt.length(); i++){
            temp+=nt[i];
        }
        ans+=temp;
        for(int i=temp.length()-2; i>=0; i--){
            ans+=temp[i];
        }
        res=stoll(ans);
        return res;
    }
}
// This function has very high time complexity as it uses linear search,so gives TLE.
// ll solve(ll x, ll k){
//     if(x==1){
//         return Nth_pal_util(k+1);
//     }
//     ll i=1;
//     while(Nth_pal_util(i+1)<x){
//         i++;
//     }
//     return Nth_pal_util((i+1)+k-1);
// }
 
// This function has slightly optimized linear search but still gives TLE.
//ll solve(ll x, ll k){
//     if(x==1){
//         return Nth_pal_util(k+1);
//     }
//      ll b = log10(x);
//      vector<ll>v={9,18,108,198,1098,1998,10998,19998,109998,199998,1099998,1999998,10999998,19999998,109999998,199999998,1099999998,1999999998};
//      vector<ll>dif={9,9,90,90,900,900,9000,9000,90000,90000,900000,900000,9000000,9000000,90000000,90000000,900000000,900000000};
//         ll i=1;
//         if(b>=1)i = v[b-1];
//         while(nthpalutil(i+1)<x){
//             i++;
//         }
//         return Nth_pal_util((i+1)+k-1);
// }
 
//This function is highly optimized or most efficient as it uses binary search and so passed all the test cases.
ll solve(ll x, ll k){
    if(x==1){
        return Nth_pal_util(k+1);
    }
    
    vector<ll>v={9,18,108,198,1098,1998,10998,19998,109998,199998,1099998,1999998,10999998,19999998,109999998,199999998,1099999998,1999999998};
    vector<ll>dif={9,9,90,90,900,900,9000,9000,90000,90000,900000,900000,9000000,9000000,90000000,90000000,900000000,900000000};
    ll dx = log10(x);
    
    if(dx<=1){
        vector<ll>temp={1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99};
        ll low=0, high=temp.size()-1, z=-1;
        while(low<=high){
            ll mid = low+(high-low)/2;
            if(temp[mid]==x){
                z=mid;
                break;
            }
            else if(temp[mid]<x){
                low=mid+1;
            }
            else{
                z=mid;
                high=mid-1;
            }
        }
        return Nth_pal_util(((z+1)+k-1)+1);
    }
    // vector<ll>w(dif[dx]);
        // for(ll i=0; i<dif[dx]; i++){
        //     w[i]=Nth_pal_util(v[dx-1]+i+1+ 1);
        // }
        // print(w);
    ll low1=0, high1=dif[dx]-1; // w.size()=dif[dx]
    ll z1=-1;
    while(low1<=high1){
        ll mid1 = low1+(high1-low1)/2;
        if( Nth_pal_util(v[dx-1]+mid1+1+1) == x ){ // w[mid1] = Nth_pal_util(v[dx-1]+mid1+1+1)
            z1=mid1;
            break;
        }
        else if( Nth_pal_util(v[dx-1]+mid1+1+1) < x ){
            low1=mid1+1;
        }
        else{ //Nth_pal_util(v[dx-1]+mid1+1+1) > x
            z1=mid1;
            high1=mid1-1;
        }
    }
    return Nth_pal_util((v[dx-1]+1+z1+k-1)+1);
}
 
int main(){
    ll t;
    cin>>t;
    ll x,k;
    while(t--){
        cin>>x>>k;
        cout<<solve(x,k)<<endl;
    }
    return 0;
}
 
/**
 
Code Explanation / Hints :
Hint-1 :
The position of a palindrome within the sequence can be determined almost without calculation: 
If the palindrome has an even number of digits, prepend a 1 to the front half of the palindrome's digits. 
If the number of digits is odd, prepend the value of front digit + 1 to the digits from position 2 ... central digit.
Examples: 98766789 = a(19876), 515 = a(61), 8206028 = a(9206), 9230329 = a(10230).
 
Hint-2:
The (nonzero) palindromes with even number of digits start at p(11) = 11, p(110) = 1001, p(1100) = 100'001,.... 
They are constructed by taking the index n - 10^L, where L=floor(log10(n)), 
and append the reversal of this number: p(1101) = 101|101, p(1102) = 102|201, ..., p(1999) = 999|999, etc. 
This case must be considered for indices n >= 1.1*10^L but n < 2*10^L.
When n >= 2*10^L, we get the palindromes with odd number of digits, which start with p(2) = 1, p(20) = 101, p(200) = 10001 etc., and 
can be constructed the same way, using again n - 10^L with L=floor(log10(n)), and appending the reversal of that number, 
now without its last digit: p(21) = 11|1, p(22) = 12|1, ..., p(99) = 89|8, ....
When n < 1.1*10^L, subtract 1 from L to be in the correct setting with n >= 2*10^L for the case of an odd number of digits.
 
Hint-3:
The numbers of palindromic numbers less than 10, 10^2, 10^3, ... are 9, 18, 108, 198, 1098, 1998, 10998, ... (OEIS A050250). 
 
References:
http://oeis.org/A002113
https://stackoverflow.com/questions/15019817/need-algorithm-to-find-the-nth-palindromic-number
http://mathworld.wolfram.com/PalindromicNumber.html
http://oeis.org/A050250
https://www.rhyscitlema.com/algorithms/generating-palindromic-numbers/
 
**/
