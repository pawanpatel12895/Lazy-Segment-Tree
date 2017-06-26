/**
*
*	author: pawan patel
*
**/

#include <bits/stdc++.h>
using namespace std;
#define llong long long
#define vect vector<llong>
class LazyTree
{	class node
	{	
	public:
		llong val;
		llong update;
		bool ispending;

		node(){val = update = ispending = 0;}
	};
	llong Size;
	vector<node> tree;
	void update(llong n, llong L,llong R,llong &p,llong &q,llong v,llong u);
	llong retrieve(llong n,llong L,llong R,llong &p,llong &q);
public:
	LazyTree(){}
	LazyTree(llong N);
	LazyTree(llong N,llong m);
	LazyTree(vect &initArr);
	llong size(){return Size;}
	void print();
	void update(llong p,llong q,llong v);
	void update(llong p,llong v);
	llong retrieve(llong p,llong q);
};
///private
void LazyTree::update(llong n, llong L,llong R,llong &p,llong &q,llong v,llong u)
{	
	if(R<p || q<L){//outOfRange
		tree[n].val += u*(R-L+1);
		tree[n].update +=u;
		if(u)tree[n].ispending = true;
	}
	else if(L>=p && R<=q){//totallyInRange
		tree[n].val+=(v+u)*(R-L+1);
		tree[n].update += v+u;
		if(v+u)tree[n].ispending = true;
	}
	else  { //overlaping range
		llong mid = (L+R)/2;
		tree[n].val += (v)*(min(R,q) - max(L,p)+1);
		tree[n].val += u*(R-L+1);
		update(n*2  ,L  ,mid,p,q,v,u+tree[n].update);
		update(n*2+1,mid+1,R  ,p,q,v,u+tree[n].update);
		tree[n].update = 0;
		tree[n].ispending = false;
	}
	if(L==R){
		tree[n].update = 0;
		tree[n].ispending = false; 
	}
}
//private
llong LazyTree::retrieve(llong n,llong L,llong R,llong &p,llong &q){
	//cout<<n<<L<<R<<".";
	if(R<p || q<L)return 0;
	if(L>=p && R<=q)return tree[n].val;
	llong mid = (L+R)/2;
	return   retrieve(n*2,L,mid,p,q)
	+ retrieve(n*2+1,mid+1,R,p,q)
	+ tree[n].update*(min(q,R)-max(L,p)+1);
}

//public
LazyTree::LazyTree(llong N)
{	Size = N;
	N = pow(2,ceil(log2(N))+1);
	//cout<<"size = "<<size<<endl;
	tree = vector<node>(N);
}
//public
LazyTree::LazyTree(vect &initArr)
{	LazyTree(initArr.size());
	int i, j;
	for(i=Size/2,j=0;j<initArr.size();++i)
		tree[i].val = initArr[j];
	i=Size/2 - 1;
	while(i>=1)
	{	tree[i].val = tree[i*2].val + tree[i*2+1].val;
		i--;
	}
}
LazyTree::LazyTree(llong N,llong m)
{	Size = N;
	N = pow(2,ceil(log2(N))+1);
	//cout<<"size = "<<size<<endl;
	tree = vector<node>(N,m);
	int i=Size/2 - 1;
	while(i>=1)
	{	tree[i].val = tree[i*2].val + tree[i*2+1].val;
		i--;
	}
}

//public
void LazyTree::print()
{	// USED FOR DEBUGGING;
	cout<<"\\*\ndebugging\nv is value at the node\nu is update pending for all decendants\np is to show if an update is pending\n"<<endl;
	for(int i=1;i<tree.size();++i)
		cout<<"node = "<<i<<", v="<<tree[i].val<<", u="<<tree[i].update<<", p="<<(tree[i].ispending?1:0)<<endl;
	cout<<"*\\\n"<<endl;
}

//public
void LazyTree::update(llong p,llong q,llong v)
{	update(1,1,Size,p,q,v,0);	
}
void LazyTree::update(llong p,llong v)
{	update(1,1,Size,p,p,v,0);	
}
//public
llong LazyTree::retrieve(llong p,llong q)
{	return retrieve(1,1,Size,p,q);	}
