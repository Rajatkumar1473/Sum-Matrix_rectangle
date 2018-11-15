#include <bits/stdc++.h> 
using namespace std; 
  
/* Declaring Structure for storing 
   three values in each segment tree node */
struct Node { 
    int pairs; 
    int open; // unused 
    int closed; // unused 
  
    Node() 
    { 
        pairs = open = closed = 0; 
    } 
}; 
  
// A utility function to get the middle index from corner indexes. 
int getMid(int s, int e) { return s + (e - s) / 2; } 
  
// Returns Parent Node after merging its left and right child 
Node merge(Node leftChild, Node rightChild) 
{ 
    Node parentNode; 
    int minMatched = min(leftChild.open, rightChild.closed); 
    parentNode.pairs = leftChild.pairs + rightChild.pairs + minMatched; 
    parentNode.open = leftChild.open + rightChild.open - minMatched; 
    parentNode.closed = leftChild.closed + rightChild.closed - minMatched; 
    return parentNode; 
} 
  
// A recursive function that constructs Segment Tree  
// for string[ss..se]. si is index of current node in 
// segment tree st 
void constructSTUtil(char str[], int ss, int se, Node* st, 
                                                 int si) 
{ 
    // If there is one element in string, store it in 
    // current node of segment tree and return 
    if (ss == se) { 
  
        // since it contains one element, pairs  
        // will be zero 
        st[si].pairs = 0; 
  
        // check whether that one element is opening  
        // bracket or not 
        st[si].open = (str[ss] == '(' ? 1 : 0); 
  
        // check whether that one element is closing 
        // bracket or not 
        st[si].closed = (str[ss] == ')' ? 1 : 0); 
  
        return; 
    } 
  
    // If there are more than one elements, then recur 
    // for left and right subtrees and store the relation 
    // of values in this node 
    int mid = getMid(ss, se); 
    constructSTUtil(str, ss, mid, st, si * 2 + 1); 
    constructSTUtil(str, mid + 1, se, st, si * 2 + 2); 
  
    // Merge left and right child into the Parent Node 
    st[si] = merge(st[si * 2 + 1], st[si * 2 + 2]); 
} 
  
/* Function to construct segment tree from given 
   string. This function allocates memory for segment  
   tree and calls constructSTUtil() to fill the  
   allocated memory */
Node* constructST(char str[], int n) 
{ 
    // Allocate memory for segment tree 
  
    // Height of segment tree 
    int x = (int)(ceil(log2(n))); 
  
    // Maximum size of segment tree 
    int max_size = 2 * (int)pow(2, x) - 1; 
  
    // Declaring array of structure Allocate memory 
    Node* st = new Node[max_size]; 
  
    // Fill the allocated memory st 
    constructSTUtil(str, 0, n - 1, st, 0); 
  
    // Return the constructed segment tree 
    return st; 
} 
  
/* A Recursive function to get the desired  
   Maximum Sum Sub-Array, 
The following are parameters of the function- 
   
st     --> Pointer to segment tree  
si --> Index of the segment tree Node  
ss & se  --> Starting and ending indexes of the  
             segment represented by 
                 current Node, i.e., tree[index] 
qs & qe  --> Starting and ending indexes of query range */
Node queryUtil(Node* st, int ss, int se, int qs, 
               int qe, int si) 
{ 
    // No overlap 
    if (ss > qe || se < qs) { 
  
        // returns a Node for out of bounds condition 
        Node nullNode; 
        return nullNode; 
    } 
  
    // Complete overlap 
    if (ss >= qs && se <= qe) { 
        return st[si]; 
    } 
  
    // Partial Overlap Merge results of Left 
    // and Right subtrees 
    int mid = getMid(ss, se); 
    Node left = queryUtil(st, ss, mid, qs, qe, si * 2 + 1); 
    Node right = queryUtil(st, mid + 1, se, qs, qe, si * 2 + 2); 
  
    // merge left and right subtree query results 
    Node res = merge(left, right); 
    return res; 
} 
  
/* Returns the maximum length correct bracket  
   subsequencebetween start and end 
   It mainly uses queryUtil(). */
int query(Node* st, int qs, int qe, int n) 
{ 
    Node res = queryUtil(st, 0, n - 1, qs, qe, 0); 
  
    // since we are storing numbers pairs 
    // and have to return maximum length, hence 
    // multiply no of pairs by 2 
    return 2 * res.pairs; 
} 
  
// Driver Code 
int main() 
{ 
    char str[] = "())(())(())("; 
    int n = strlen(str); 
  
    // Build segment tree from given string 
    Node* st = constructST(str, n); 
  
    int startIndex = 0, endIndex = 11; 
    cout << "Maximum Length Correct Bracket"
           " Subsequence between "
         << startIndex << " and " << endIndex << " = "
         << query(st, startIndex, endIndex, n) << endl; 
  
    startIndex = 1, endIndex = 2; 
    cout << "Maximum Length Correct Bracket"
           " Subsequence between "
         << startIndex << " and " << endIndex << " = "
         << query(st, startIndex, endIndex, n) << endl; 
  
    return 0; 
} 

