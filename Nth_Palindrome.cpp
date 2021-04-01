/**
Problem Statement: To determine the kth palindrome number where k>=1. Consider 0 as the first palindrome
number. So the first 15 palindrome numbers are 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22, 33, 44, 55.

Input format: An Integer k, 1<=k<=1e9
Output: Print the kth palindrome number.

Eg:
Input: 2    Output: 1

Input:61    Output: 515
=============================================================================================================

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

References:
http://oeis.org/A002113
http://oeis.org/A002113/list
https://stackoverflow.com/questions/15019817/need-algorithm-to-find-the-nth-palindromic-number
http://mathworld.wolfram.com/PalindromicNumber.html
https://www.rhyscitlema.com/algorithms/generating-palindromic-numbers/

**/

#include<bits/stdc++.h>
#define ll long long int
using namespace std;
 
// This function considers 0 as the first palindrome number. Nth_palindrome(1) = 0, Nth_palindrome(2) = 1, 
// Nth_palindrome(3) = 2,.. So, the first 12 palindrome numbers are : 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 22.
// Note: If given that 1 is the first palindrome number then we need to call Nth_palindrome(k+1) for the 
// kth palindrome number.
ll Nth_palindrome(ll n){
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
int main(){
    ll n;
    cin>>n;
    cout<<Nth_palindrome(n)<<"\n";
    return 0;
}
