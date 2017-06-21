/**
*
*	author: pawan patel
*
**/

#include <bits/stdc++.h>
using namespace std;

class LazyTree
{	class node
	{	
	public:
		long long val;
		long long update;
		bool ispending;

		node(){val = update = ispending = 0;}
	};
	long long Size;
	vector<node> tree;
	void update(long long n, long long L,long long R,long long &p,long long &q,long long v,long long u);
	long long retrieve(long long n,long long L,long long R,long long &p,long long &q);
public:
	LazyTree(){}
	LazyTree(long long N);
	long long size(){return Size;}
	void print();
	void update(long long &p,long long &q,long long v);
	long long retrieve(long long &p,long long &q);
};


LazyTree::LazyTree(long long N)
{	Size = N;
	N = pow(2,ceil(log2(N))+1);
	//cout<<"size = "<<size<<endl;
	tree = vector<node>(N);
}

void LazyTree::print()
{	// USED FOR DEBUGGING;
	cout<<endl;
	for(int i=1;i<tree.size();++i)
		cout<<"node = "<<i<<", v="<<tree[i].val<<", u="<<tree[i].update<<", p="<<(tree[i].ispending?1:0)<<endl;
	cout<<endl;
}

void LazyTree::update(long long &p,long long &q,long long v)
{	update(1,1,Size,p,q,v,0);	
}
void LazyTree::update(long long n, long long L,long long R,long long &p,long long &q,long long v,long long u)
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
		long long mid = (L+R)/2;
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

long long LazyTree::retrieve(long long n,long long L,long long R,long long &p,long long &q){
	//cout<<n<<L<<R<<".";
	if(R<p || q<L)return 0;
	if(L>=p && R<=q)return tree[n].val;
	long long mid = (L+R)/2;
	return   retrieve(n*2,L,mid,p,q)
	+ retrieve(n*2+1,mid+1,R,p,q)
	+ tree[n].update*(min(q,R)-max(L,p)+1);
}
long long LazyTree::retrieve(long long &p,long long &q)
{	return retrieve(1,1,Size,p,q);	}

