# lazy propogating segment Tree.

Read About Lazy Trees:<br>
http://www.geeksforgeeks.org/lazy-propagation-in-segment-tree/

### 

Build 0: <br>
--> update and retrieval of range sum.<br>
--> all nodes are initialized with zero.<br>
--> initialization with given values <br>
--> only integer values are accepted<br>

***

Range Query -- O(log N)<br>
Range Update O(log N)<br>

*** 

***Constructors:***
1. LazyTree()
2. LazyTree(long long)
3. LazyTree(long long, long long)
4. LazyTree(vector<long long>)
<br>

***Functions available:***
1. long long size()
2. void update(long long, long long)
3. void update(long long, long long, long long)
4. long long retrieve(long long, long long)

***usage & discription: ***

1. LazyTree() : creates an empty Tree. with no nodes at all. useless.<br>
```
LazyTree L();
```
2. LazyTree(long long size) : creates tree with Size = size, with default value = 0, for every node.<br>
```
LazyTree L(4);
```
3. LazyTree(long long size, long long m) : creates tree with Size = size, with default value = m, for every node.<br>
```
LazyTree L(4,2);
```
4. LazyTree(vector<long long> ) : creates a tree from the array.<br> 
```
vector<long long> vect(4,2); //array values can be different
LazyTree L(vect);
```

1. long long size() : returns initialized size. useless.
2. void update(long long pos, long long val) : element at position = pos, increments with value = val;
```
L.update(4,7); 
// equivalent to L.update(4,4,7);
```
3. void update(long long L, long long R, long long val) : range update function. increments the values = val, in the range [L,R].
```
L.update(4,5,7);
```
4. long long retrieve(long long L, long long R) : query the sum in range [L,R]
```
L.retrieve(4,5);	
```
***

(\\____/) <br>
(='.'=) <br>
o(")_(")<br>