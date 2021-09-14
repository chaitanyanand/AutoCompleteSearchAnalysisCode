#include<iostream>
#include<string>
using namespace std;
int compare(string&prefix,string&word)
{
    int i=0;
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
int main()
{
    int SUG=3;
    int n=17;
    string words[]={"","app","apple","apple is good for health","application","baby","ball","bobby","butter","butter cost","call","car","car parking","card","carriage","carrot","cart"};
    int value[]={-1,15,20,2,14,16,20,3,7,3,12,30,20,10,5,10,3};
    for(int i=0;i<=16;i++)
    {
        cout<<words[i]<<"-->"<<value[i]<<" ";
    }
    cout<<endl;
    string prefix;
    cout<<"enter a prefix"<<endl;
    getline(cin,prefix);
    //starting and ending indices of prefix phrase
    int start_index=start_binary_search(words,n,prefix);
    int end_index=end_binary_search(words,n,prefix);
    if(start_index==-1)
    {
        cout<<"No Word found with given prefix"<<endl;
        return 0;
    }
    int count=0,l=start_index,r=end_index;
    int weight[r-l+1];
    int size=(r-l+1);
    for(int i=l;i<=r;i++)
    {
        weight[i-l]=value[i];
    }
    int index=0;
    while(count<SUG)
    {
        for(int i=0;i<size;i++)
        {
            if(weight[i]>weight[index])
            {
                index=i;
            }
        }
        if(weight[index]==-1)
            break;
        cout<<words[index+l]<<endl;
        weight[index]=-1;
        count++;
    }
    return 0;
}
