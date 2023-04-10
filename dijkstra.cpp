#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <fstream>
using namespace std;
typedef struct side
{
    char first;//��һ�����
    char second;//�ڶ������
    int length;//�߳�
}side;

int main(){
    int n;
    char src;
    /*cout<<"��������ͼ�ıߵ���Ŀ��"<<endl;
    cin>>n;
    cout<<"����Դ��㣺";
    cin>>src;*/
    ifstream file;
    file.open("dijkstra.txt");//�˴�ʹ���ļ���ʽ���룬Ҳ����ɾ�����ļ���ش���ʹ���ֶ�����
    file>>n>>src;
    vector <side> graph;
    map<char,int> dist;//D(x)
    map<char,char> neighbor;//p(x)
    set<char> node;//����װ���н��
    string ans;
    ans.append(1,src);
    cout<<"��������ͼ:(��ʽΪ(�� ���� ��),��(u 1 v))"<<endl;
    for(int i=0;i<n;i++){//��ʼ��
        side s;
        char fst,snd;
        int l;
        //cin>>fst>>l>>snd;
        file>>fst>>l>>snd;
        s.first=fst;
        s.length=l;
        s.second=snd;
        graph.push_back(s);//��¼��
        node.insert(fst);//��¼���н��
        node.insert(snd);
        if(fst==src){//��ʼ��D(x),�ҵ������������ھ�
            dist.insert(make_pair(snd,l));
            neighbor.insert(make_pair(snd,fst));
        }else if(snd==src){
            dist.insert(make_pair(fst,l));
            neighbor.insert(make_pair(fst,snd));
        }
    }
    file.close();
    node.erase(src);
    cout<<"����"<<"\t"<<"N'"<<"\t";
    for(auto i=node.begin();i!=node.end();i++){
        cout<<"D("<<*i<<"),p("<<*i<<")\t";//�����ͷ
        if(dist.find(*i)==dist.end()){//���벻���ھӵĽ��
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
            if(dist.find(*i)!=dist.end()){//dist����о���
                minDist=min(minDist,dist[*i]);//������С����
                if(dist[*i]!=INT32_MAX){
                    cout<<dist[*i]<<','<<neighbor[*i]<<"\t\t";
                }else {
                    cout<<neighbor[*i]<<"  \t\t";
                }
            }else {//dist��û�н���Ӧ�ľ���
                cout<<"  \t\t";
            }
        }
        cout<<endl;
        char temp;
        for(auto i=dist.begin();i!=dist.end();i++){//�ҳ�������С��
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
                if(temp==(*j).first&&dist.find((*j).second)!=dist.end()){//dist��һ����ɾȥ�ĵ���ھӻ���dist��
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

