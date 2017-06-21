class LazyTree
{	class node
	{public:
		llong val;
		llong update;
		bool ispending;
	
		node(){val = update = ispending = 0;}
	};
		llong Size;
	vector<node> tree;
	void update(llong n, llong L,llong R,llong &p,llong &q,llong v,llong u)
	{	
		if(R<p || q<L)//outOfRange
		{	
			tree[n].val += u*(R-L+1);
			tree[n].update +=u;
			if(u)tree[n].ispending = true;
		}
		else if(L>=p && R<=q)//totallyInRange
		{	tree[n].val+=(v+u)*(R-L+1);
			tree[n].update += v+u;
			if(v+u)tree[n].ispending = true;
		}
		else // overlaping range
		{	llong mid = (L+R)/2;
			tree[n].val += (v)*(min(R,q) - max(L,p)+1);
			tree[n].val += u*(R-L+1);
			update(n*2  ,L  ,mid,p,q,v,u+tree[n].update);
			update(n*2+1,mid+1,R  ,p,q,v,u+tree[n].update);
			tree[n].update = 0;
			tree[n].ispending = false;
		}
		if(L==R)
		{	tree[n].update = 0;
			tree[n].ispending = false; 
		}
	}
	llong retrieve(llong n,llong L,llong R,llong &p,llong &q)
	{	//cout<<n<<L<<R<<".";
		if(R<p || q<L)return 0;
		if(L>=p && R<=q)return tree[n].val;
		llong mid = (L+R)/2;
		return   retrieve(n*2,L,mid,p,q)
				+retrieve(n*2+1,mid+1,R,p,q)
				+tree[n].update*(min(q,R)-max(L,p)+1);
	}
public:
	LazyTree(){}
	LazyTree(llong N)
	{	Size = N;
		N = pow(2,ceil(log2(N))+1);
		//cout<<"size = "<<size<<endl;
		tree = vector<node>(N);
	}
	llong size(){return Size;}
	void update(llong &p,llong &q,llong v)
	{	//cout<<v<<endl;;
		update(1,1,Size,p,q,v,0);
	}
	llong retrieve(llong &p,llong &q)
	{
		return retrieve(1,1,Size,p,q);
	}
	void print()
	{	cout<<endl;
		for(int i=1;i<tree.size();++i)
		{
			cout<<"node = "<<i<<", v="<<tree[i].val<<", u="<<tree[i].update<<", p="<<(tree[i].ispending?1:0)<<endl;
		}
		cout<<endl;
	}
};