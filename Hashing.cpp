// These algorithums are written by Akshat Saxena
#include <iostream>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <numeric>
#include <iterator>
#include <bitset> 
#include <cstring>
#define ll long long
using namespace std;
#define mod 1000000007
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);
//HASHING
/* 1) Hashing is expert data structure when we use it in operations 
like Search,Insert,Delete all in O(1).
 2) It is not a great idea to use hashing in to find upper ,lower bounds,Prefix searching
 or Printing in sorted order
 3) To do operations mentioned in 2nd point we use AVL or Red Black Trees
 4) Associative array is noting but hash tables
 */

// DIRECT ADDRESSING TABLE
/* It is used when we have values in a range and when keys are small
Its Disadvantages are real no,string as a key as index is only in integers
used to store ascii values #ex */

//CHAINING
/* key%m where m is prime and cosest to n=no of keys
Data structure to store the chains are as follows
1.Linked list  sear/ins/del in O(n)
2.Vectors -- same -- but cache friendly
3.BST {AVL tree, Red black tree} in O(logn)
*/
// OPEN ADRESSING WITH LINEAR PROBBING
/* To avoid clustering we use quadratic or Double hashing
Mathameticfact load=n/m if load<0.5 and m is prime then only quadratic
probbing promise to fill the vacnet space or the space will be left
as it is. */

// DOUBLE HASHING
// hash(key,i)=(h1key+ih2key)%m hash function 
// where i is the number of ith collision
// h2 function should not return zero else it will probe to the same
//position
//  unorderded set uses hash table so ins/serch/del in O(1)
//  unorderded map uses hash table so ins/serch/del in O(1)
// To pass array in set set<ll>st(arr,arr+n)
struct MyHash
{
    int BUCKET;
    list<int> *table;
    MyHash(int b)
    {
        BUCKET = b;
        table = new list<int>[BUCKET];
    }
    void insert(int k)
    {
        int i = k % BUCKET;
        table[i].push_back(k);
    }
    bool search(int k)
    {
        int i = k % BUCKET;
        for (auto x : table[i])
           if (x == k)
              return true;
        return false;      
    }
    void remove(int k)
    {
        int i = k % BUCKET;
        table[i].remove(k);
    }
};
int pairWithSumX(int arr[],int n, int X)
{
    unordered_set<int> us;
    for(int i = 0; i < n; i++)
    {
        if(us.find(X - arr[i]) != us.end())
          return 1;
          
        us.insert(arr[i]);
    }
    return 0;
    
}
// Subarray with zero sum
// The idea is to calculate the prefix sum and iterate to check wheter the prefix sum value dosnt change
// after iterating till a perticular value idc the prefix sum dosnt change the the subarray with zero sum exist
int ZeroSumSubarray(int arr[], int n)
{
    unordered_set<int> us;
    int prefix_sum = 0;
    us.insert(0);
    for(int i = 0; i < n; i++)
    {
        prefix_sum += arr[i];
        if(us.find(prefix_sum) != us.end())
          return 1;
        us.insert(prefix_sum);
    }
    return 0;
    
}
//Subarray with Given sum
// We will compute prefix sum and keep it in the hash table then
// find if prefixsum-given sum is present in the array or not
bool isSum(int arr[], int n, int sum)
{
    unordered_set<int> s;
    int pre_sum = 0;
    for(int i = 0; i < n; i++)
    {   
        if(pre_sum==sum)
            return true;
        pre_sum += arr[i];
        if(s.find(pre_sum-sum) != s.end())
          return true;
        s.insert(pre_sum);
    }
    return false;
}
int largestSubarrayWithSumX(int a[], int n, int sum)
{
    int prefix_sum = 0;
    unordered_map<int,int>mp;
    int res=0;
    for(int i=0;i<n;i++){
        prefix_sum+=a[i];
        if(prefix_sum==sum){
          res=i+1;
        }
        if(mp.find(prefix_sum)==mp.end()){
            mp[prefix_sum]=i;
        }
        if(mp.find(prefix_sum-sum)!=mp.end()){
            res=max(res,i-mp[sum-prefix_sum]);
        }
    }
    return res;
}
//  Longest Subarray with equal number of 0s and 1s 
// make all 0 to -1 and find longestsubarray with sum=0

//   Longest Subarray with equal number of 0s and 1s 
//  Take the difference of the array and find the longest subarray
// with given sum as 0

//Longest Consecutive Subsequence
// insert all the elements in the hash table
// search from x-1 if its not present start the serach else go to the next
// eleemnt as this elemnt is previously considered
// Naive in nlogn
int findLongest(int arr[], int n)
{
    sort(arr,arr+n);
    int res=1,curr=1;
    for(int i=1;i<n;i++){
        if(arr[i]==arr[i-1]+1)
            curr++;
        else{
            res=max(res,curr);
            curr=1;
        }
    }
    res=max(res,curr);
    return res;
}

// efficient in O(n)
int findLongest(int arr[], int n)
{
    unordered_set<int> s;
    int res = 0;
 
    for (int i = 0; i < n; i++)
        s.insert(arr[i]);
 
    for (int i = 0; i < n; i++) {
        if (s.find(arr[i] - 1) == s.end()) {
            // begining
            int curr = 1;
            while (s.find(curr+arr[i]) != s.end())
                curr++;
                
            res = max(res, curr);
        }
    }
    return res;
}


//Count Distinct Elements In Every Window
void printDistinct(int arr[], int n, int k)
{
    map<int, int> m; 
   
    for (int i = 0; i < k; i++) { 
        m[arr[i]] += 1; 
    } 
   
    cout << m.size() << " "; 
   
    for (int i = k; i < n; i++) { 
        
        m[arr[i - k]] -= 1;
        
        if (m[arr[i - k]] == 0) { 
            m.erase(arr[i-k]); 
        }   
        m[arr[i]] += 1; 
   
        cout << m.size() << " "; 
    } 
    
}
int main(){
MyHash mh(7);
	    mh.insert(10);
	    mh.insert(20);
	    mh.insert(15);
	    mh.insert(7);
	    cout << mh.search(10) << endl;
	    mh.remove(15);
	    cout << mh.search(15);
       int arr[] = {8, 3, -7, -4, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    int sum = -8;
    cout<<endl;
    cout << largestSubarrayWithSumX(arr, n, sum)<<endl;




    return 0;
}