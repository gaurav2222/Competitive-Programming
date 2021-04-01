/********
Problem Link: https://www.hackerearth.com/problem/algorithm/kth-palindrome-45f48699/
 
A palindromic number is a number that remains the same when its digits are reversed. Your task is to get the Kth palindrome number greater than or equal to X.
 
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
1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55, 66, 77, 88, 99, 101, 111, 121, 131, 141, 151, 161, 
171, 181, 191, 202, 212, 222, 232.

===========================================================================================================
Solution Code Explanation, Hints, References used :

Hint-1 :
The position of a palindrome within the sequence can be determined almost without calculation: 
If the palindrome has an even number of digits, prepend a 1 to the front half of the palindrome's digits. 
If the number of digits is odd, prepend the value of (front digit + 1) to the digits from 
position 2 to the central digit.
Examples: 98766789 = Nth_pal(19876), 515 = Nth_pal(61), 8206028 = Nth_pal(9206), 9230329 = Nth_pal(10230).
Here Nth_pal(i) denotes the ith palindrome number, where i >= 1
So, Nth_pal(1)=0, Nth_pal(2)=1, Nth_pal(3)=2,....
 
Hint-2:
The (nonzero) palindromes with even number of digits start at Nth_pal(11) = 11, Nth_pal(110) = 1001, 
Nth_pal(1100) = 100001, .... 
They are constructed by taking the index (n - 10^L), where L=floor(log10(n)), 
and append the reversal of this number: Nth_pal(1101) = 101|101, Nth_pal(1102) = 102|201, ..., 
Nth_pal(1999) = 999|999, etc. 
This case must be considered for indices n >= 1.1*10^L but n < 2*10^L.

Hine-3:
When n >= 2*10^L, we get the palindromes with odd number of digits, which begins with 
Nth_pal(2)=1, Nth_pal(20)= 101, Nth_pal(200) = 10001 etc., and can be constructed the same way, using again 
n - 10^L where L=floor(log10(n)), and appending the reversal of that number, now without its last digit: 
Nth_pal(21) = 11|1, Nth_pal(22) = 12|1, ..., Nth_pal(99) = 89|8, ....
When n < 1.1*10^L, subtract 1 from L to be in the correct setting with n >= 2*10^L for the case 
of an odd number of digits.
 
Hint-4:
The numbers of palindromic numbers less than 10, 10^2, 10^3, ... are 9, 18, 108, 198, 1098, 1998, 
10998, ... (OEIS A050250). 
 
References:
http://oeis.org/A002113
http://oeis.org/A002113/list
https://stackoverflow.com/questions/15019817/need-algorithm-to-find-the-nth-palindromic-number
http://mathworld.wolfram.com/PalindromicNumber.html
http://oeis.org/A050250
https://www.rhyscitlema.com/algorithms/generating-palindromic-numbers/

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
 
// This function considers 0 as the first palindrome number. Nth_palindrome(1) = 0, Nth_palindrome(2) = 1, 
// Nth_palindrome(3) = 2,.. So, the first 12 palindrome numbers are : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22.
// But according to question, 1 is the first palindrome number,
// So we need to call Nth_palindrome(n+1) for the nth palindrome number.
ll Nth_palindrome(ll n){ // Constraint: 1<=n<=1e9
	if(n==1)return 0;
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
        }
        else{
            temp+=to_string(9);
            for(int i=2; i<nt.length(); i++){
                temp+=nt[i];
            }
            ans+=temp;
            for(int i=temp.length()-2; i>=0; i--){
               ans+=temp[i];
            }
            res=stoll(ans);
        }
		      return res;
    }
}

// // Method-1: This function has very high time complexity as it uses linear search,so gives TLE.
// ll solve(ll x, ll k){
//     if(x==1){
//         return Nth_palindrome(k+1);
//     }
//     ll i=1;
//     while(Nth_palindrome(i+1)<x){
//         i++;
//     }
//     return Nth_palindrome((i+1)+k-1);
// }
 
// // Method-2: This function has slightly optimized linear search but still gives TLE.
// ll solve(ll x, ll k){
//     if(x==1){
//         return Nth_palindrome(k+1);
//     }
//      ll b = log10(x);
//      vector<ll>v={9,18,108,198,1098,1998,10998,19998,109998,199998,1099998,1999998,10999998,19999998,109999998,199999998,1099999998,1999999998};
//      vector<ll>dif={9,9,90,90,900,900,9000,9000,90000,90000,900000,900000,9000000,9000000,90000000,90000000,900000000,900000000};
//         ll i=1;
//         if(b>=1)i = v[b-1];
//         while(Nth_palindrome(i+1)<x){
//             i++;
//         }
//         return Nth_palindrome((i+1)+k-1);
// }
 
// Method-3: This function is highly optimized or most efficient since it uses binary search 
// and so passed all the test cases.
ll solve(ll x, ll k){
    if(x==1){
        return Nth_palindrome(k+1);//Simply return the kth palindrome number, So called Nth_pal_util(k+1)
    }
    
    vector<ll>v={9,18,108,198,1098,1998,10998,19998,109998,199998,1099998,1999998,10999998,19999998,109999998,199999998,1099999998,1999999998};
	//Vector v: v[i] represents Number of nonzero palindromes less than 10^(i), where i is 1-based index

    vector<ll>diff={9,9,90,90,900,900,9000,9000,90000,90000,900000,900000,9000000,9000000,90000000,90000000,900000000,900000000};
	// Vector diff: diff[i] represents the number of palindromes of length i, where i is 1-index-based.

    ll dx = log10(x);// dx = No. of digits in x - 1;
    
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
        return Nth_palindrome(((z+1)+k-1)+1);//Return the Nth palindrome number where N = (z+1 + k-1)
    }

    // vector<ll>w(diff[dx]);//This vector gives the array of palindrome numbers of length dx+1
	// for(ll i=0; i<diff[dx]; i++){
	//     w[i]=Nth_palindrome(v[dx-1]+i+1+ 1);
	// }
	// print(w);

    ll low1=0, high1=diff[dx]-1; // w.size()=diff[dx]
    ll z1=-1;
    while(low1<=high1){
        ll mid1 = low1+(high1-low1)/2;
		      ll value = Nth_palindrome(v[dx-1]+mid1+1+1);
        if(value == x){ // w[mid1] = value
            z1=mid1;
            break;
        }
        else if(value < x){
            low1=mid1+1;
        }
        else{ // value > x
            z1=mid1;
            high1=mid1-1;
        }
    }
    return Nth_palindrome((v[dx-1]+1+z1+k-1)+1);//Return the Nth Palindrome Number where N= v[dx-1]+1+z1+k-1
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
