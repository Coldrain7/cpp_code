#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
using namespace std;
typedef struct side
{
    char first;//第一个结点
    char second;//第二个结点
    int length;//边长
}side;

int main(){
    int n;
    char src;
    /*cout<<"输入拓扑图的边的数目："<<endl;
    cin>>n;
    cout<<"输入源结点：";
    cin>>src;*/
    ifstream file;
    file.open("dijkstra.txt");//此处使用文件形式输入，也可以删掉与文件相关代码使用手动输入
    file>>n>>src;
    vector <side> graph;
    map<char,int> dist;//D(x)
    map<char,char> neighbor;//p(x)
    set<char> node;//用于装所有结点
    string ans;
    ans.append(1,src);
    cout<<"输入拓扑图:(格式为(点 长度 点),如(u 1 v))"<<endl;
    for(int i=0;i<n;i++){//初始化
        side s;
        char fst,snd;
        int l;
        //cin>>fst>>l>>snd;
        file>>fst>>l>>snd;
        s.first=fst;
        s.length=l;
        s.second=snd;
        graph.push_back(s);//记录边
        node.insert(fst);//记录所有结点
        node.insert(snd);
        if(fst==src){//初始化D(x),找到并存入所有邻居
            dist.insert(make_pair(snd,l));
            neighbor.insert(make_pair(snd,fst));
        }else if(snd==src){
            dist.insert(make_pair(fst,l));
            neighbor.insert(make_pair(fst,snd));
        }
    }
    file.close();
    node.erase(src);
    cout<<"步骤"<<"\t"<<"N'"<<"\t";
    for(auto i=node.begin();i!=node.end();i++){
        cout<<"D("<<*i<<"),p("<<*i<<")\t";//输出表头
        if(dist.find(*i)==dist.end()){//加入不是邻居的结点
            dist.insert(make_pair(*i,INT32_MAX));
            neighbor.insert(make_pair(*i,'?'));
        }
    }
    cout<<endl;
    int count=0;
    while(ans.size()!=node.size()+1){
        cout<<count<<"\t"<<ans<<"\t";
        count++;
        int minDist=INT32_MAX;
        for(auto i=node.begin();i!=node.end();i++){
            if(dist.find(*i)!=dist.end()){//dist里存有距离
                minDist=min(minDist,dist[*i]);//计算最小距离
                if(dist[*i]!=INT32_MAX){
                    cout<<dist[*i]<<','<<neighbor[*i]<<"\t\t";
                }else {
                    cout<<neighbor[*i]<<"  \t\t";
                }
            }else {//dist里没有结点对应的距离
                cout<<"  \t\t";
            }
        }
        cout<<endl;
        char temp;
        for(auto i=dist.begin();i!=dist.end();i++){//找出距离最小点
            if(minDist==i->second){
                temp=i->first;
                ans+=temp;
                dist.erase(i->first);
                neighbor.erase(i->first);
                break;
            }
        }
        for(auto i=dist.begin();i!=dist.end();i++){
            for(auto j=graph.begin();j!=graph.end();j++){
                if(temp==(*j).first&&dist.find((*j).second)!=dist.end()){//dist上一步被删去的点的邻居还在dist中
                    int distance=minDist+(*j).length;//D(w)+c(w,v)
                    dist[(*j).second]=min(dist[(*j).second],distance);
                    neighbor[(*j).second]=temp;
                }else if(temp==(*j).second&&dist.find((*j).first)!=dist.end()){
                    int distance=minDist+(*j).length;//D(w)+c(w,v)
                    dist[(*j).first]=min(dist[(*j).first],distance);
                    neighbor[(*j).second]=temp;
                }
            }
        }
    }
    cout<<count<<"\t"<<ans;
    return 0;
}

