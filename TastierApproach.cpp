#include<iostream>
#include<string>
using namespace std;

struct node{
int weight;
int associated_index;
};
struct heap_node{
    int low;
    int high;
    int weight;
    int associated_index;
     heap_node()
    {

    }
    heap_node(int a,int b,int c,int d)
    {
        low=a;
        high=b;
        weight=c;
        associated_index=d;

    }
};

class heap{
private:
    heap_node*arr;
    int Size,max_size;
public:
    heap();
    heap(int SIZE);
    int parent(int i);
    void insert_heap(heap_node node);
    void max_heapify(int i);
    void  pop();
    heap_node top();
};
void createSegmentTree(node*tree,int*arr,int low,int high,int si);
node max_query(node*tree,int qs,int qe,int low,int high,int si);
node max_query(node*tree,int qs,int qe,int low,int high,int si);
void updateSegmentTree(node*tree,int*arr,int i,int new_value,int low,int high,int si);
int compare(string&prefix,string&word);
int start_binary_search(string words[],int n,string&prefix);
int end_binary_search(string words[],int n,string&prefix);



int main()
{
    int SUG=3;
    heap max_heap(SUG+1);
    string words[]={"","app","apple","apple is good for health","application","baby","ball","bobby","butter","butter cost","call","car","car parking","card","carriage","carrot","cart"};
    int value[]={-1,15,20,2,14,16,20,3,7,3,12,30,20,10,5,10,3};
    for(int i=0;i<=16;i++)
    {
        cout<<words[i]<<"-->"<<value[i]<<" ";
    }
    cout<<endl<<endl;
    //create segment tree
    int k=1,n=17;
    while(k<n)
    {
        k=k*2;
    }
    k=k*2;
    node *tree=new node[k-1];
    createSegmentTree(tree,value,0,n-1,0);
    string prefix;
    cout<<"enter a prefix"<<endl;
    getline(cin,prefix);

    int start_index=start_binary_search(words,n,prefix);
    int end_index=end_binary_search(words,n,prefix);

    if(start_index==-1)
    {
        cout<<"No Word found with given prefix"<<endl;
        return 0;
    }

    //code for getting top K suggestions
    int l=start_index,r=end_index;

    node res1=max_query(tree,l,r,0,n-1,0);

    heap_node h1(l,r,res1.weight,res1.associated_index);
    max_heap.insert_heap(h1);
    int count=1;

    while(count<=(r-l+1)&&count<=3)
    {
        heap_node res=max_heap.top();
        max_heap.pop();
        cout<<words[res.associated_index]<<endl;
         node n1,n2;
        if(res.low>res.associated_index-1)
        {
            node n2=max_query(tree,res.associated_index+1,res.high,0,n-1,0);
            max_heap.insert_heap(heap_node(res.associated_index+1,res.high,n2.weight,n2.associated_index));
        }
        else if(res.high<res.associated_index)
        {
            node n1=max_query(tree,res.low,res.associated_index-1,0,n-1,0);
            max_heap.insert_heap(heap_node(res.low,res.associated_index-1,n1.weight,n1.associated_index));
        }
        else
        {
            node n1=max_query(tree,res.low,res.associated_index-1,0,n-1,0);
            max_heap.insert_heap(heap_node(res.low,res.associated_index-1,n1.weight,n1.associated_index));
            node n2=max_query(tree,res.associated_index+1,res.high,0,n-1,0);
            max_heap.insert_heap(heap_node(res.associated_index+1,res.high,n2.weight,n2.associated_index));
        }
        count++;
    }
    return 0;

}
heap::heap()
{
    max_size=16;
    arr=new heap_node[max_size];
}
heap:: heap(int s)
{
    max_size=s;
    arr=new heap_node[max_size];
    Size=0;
}
int heap::parent(int i)
{
    return(i-1)/2;
}
void heap::insert_heap(heap_node node)
{
    arr[Size]=node;
    Size++;
    int i=Size-1;
    while(i!=0&&arr[parent(i)].weight<arr[i].weight)
    {
        heap_node temp=arr[parent(i)];
        arr[parent(i)]=arr[i];
        arr[i]=temp;
        i=parent(i);
    }
}
void heap:: max_heapify(int i)
{
    int highest=i;
    int l=2*i+1,r=2*i+2;
    if(l<Size&&arr[highest].weight<arr[l].weight)
    {
        highest=l;
    }
    if(r<Size&&arr[highest].weight<arr[r].weight)
    {
        highest=r;
    }
    if(highest!=i)
    {
        heap_node temp=arr[i];
        arr[i]=arr[highest];
        arr[highest]=temp;
        max_heapify(highest);
    }
}
void heap:: pop()
{
    if(Size==0)
    {
        cout<<"no element to pop as heap is empty"<<endl;
        exit(1);
    }
    arr[0]=arr[Size-1];
    Size--;
    max_heapify(0);

}
heap_node heap:: top()
{
    if(Size==0)
    {
        cout<<"no element to return as heap is empty"<<endl;
        exit(1);

    }
    return arr[0];
}
void createSegmentTree(node*tree,int*arr,int low,int high,int si)
{
    if(low==high)
    {
       tree[si].weight=arr[low];
       tree[si].associated_index=low;
       return;
    }
    int mid=(low+high)/2;
    createSegmentTree(tree,arr,low,mid,2*si+1);
    createSegmentTree(tree,arr,mid+1,high,2*si+2);
    if(tree[2*si+1].weight>=tree[2*si+2].weight)
    {
        tree[si].weight=tree[2*si+1].weight;
        tree[si].associated_index=tree[2*si+1].associated_index;
    }
    else{
         tree[si].weight=tree[2*si+2].weight;
        tree[si].associated_index=tree[2*si+2].associated_index;
    }

}
node max_query(node*tree,int qs,int qe,int low,int high,int si)
{
    if(qs>high||qe<low)
    {
        node temp;
        temp.weight=-1;
        temp.associated_index=-1;
        return temp;
    }
    else if(low>=qs&&high<=qe)
    {
        return tree[si];
    }
    else
    {
        int mid=(low+high)/2;
        node p=max_query(tree,qs,qe,low,mid,2*si+1);
        node q=max_query(tree,qs,qe,mid+1,high,2*si+2);
        if(p.weight>=q.weight)
        {
            return p;
        }
        else
        {
            return q;
        }
    }

}
void updateSegmentTree(node*tree,int*arr,int i,int new_value,int low,int high,int si)
{
    if(i<low||i>high)
    {
        cout<<"Invalid Input";
        exit(1);
    }
    if(low==high)
    {
        arr[i]=new_value;
        tree[si].weight=arr[i];
        tree[si].associated_index=i;
        return;
    }
    int mid=(low+high)/2;
    if(i>=low&&i<=mid)
    {
        updateSegmentTree(tree,arr,i,new_value,low,mid,2*si+1);
    }
    else
    {
        updateSegmentTree(tree,arr,i,new_value,mid+1,high,2*si+2);
    }
     if(tree[2*si+1].weight>=tree[2*si+2].weight)
    {
        tree[si].weight=tree[2*si+1].weight;
        tree[si].associated_index=tree[2*si+1].associated_index;
    }
    else{
         tree[si].weight=tree[2*si+2].weight;
        tree[si].associated_index=tree[2*si+2].associated_index;
    }

}
int compare(string&prefix,string&word)
{
    unsigned int i=0;
    if(word.length()<prefix.length())
    {
        i=0;
        while(i<word.length()&&prefix[i]==word[i])
        {
            i++;
        }
        if(i==word.length())
        return 1;
        if(prefix[i]<word[i])
            return -1;
        return 1;
    }
    i=0;
    while(i<prefix.length()&&prefix[i]==word[i])
    {
        i++;
    }
    if(i==prefix.length())
    return 0;
    if(prefix[i]<word[i])
        return -1;
    return 1;
}
int start_binary_search(string words[],int n,string&prefix)
{
    int l=0,r=n-1,mid,ans=-1;
    while(l<=r)
    {
        mid=(l+r)/2;
        int comp=compare(prefix,words[mid]);

        if(comp==0)
        {
            ans=mid;
            r=mid-1;
        }
        else if(comp==-1)
        {
            r=mid-1;
        }
        else
        {
            l=mid+1;
        }
    }
    return ans;
}

int end_binary_search(string words[],int n,string&prefix)
{
    int l=0,r=n-1,mid,ans=-1;
    while(l<=r)
    {
        mid=(l+r)/2;
        int comp=compare(prefix,words[mid]);
        if(comp==0)
        {
            ans=mid;
            l=mid+1;
        }
        else if(comp==-1)
        {
            r=mid-1;
        }
        else
        {
            l=mid+1;
        }
    }
    return ans;
}

