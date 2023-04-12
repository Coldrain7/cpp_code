#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
struct word
{
    string spell;
    vector<string> wordClass;
    vector<string> meaning;
};
bool cmp(word a,word b)
    {
        return a.spell>b.spell;
    }
class helper
{
private:
    vector<word> words;
    vector<word> testWords;
public:
    helper()
    {
        ifstream ifs;
        ifs.open("words.txt",ios::in);
        while(!ifs.eof())
        {
            string data;
            getline(ifs,data);
            istringstream line(data);
            word w;
            line>>w.spell;
            if(w.spell=="")break;
            string tmp;
            while(line>>tmp)
            {
                w.wordClass.push_back(tmp);
                if(line>>tmp)
                {
                    w.meaning.push_back(tmp);
                }else break;
            }
            words.push_back(w);
        }
        ifs.close();
        ifs.open("testWords.txt",ios::in);
        while(!ifs.eof())
        {
            string data;
            getline(ifs,data);
            istringstream line(data);
            word w;
            line>>w.spell;
            if(w.spell=="")break;
            string tmp;
            while(line>>tmp)
            {
                w.wordClass.push_back(tmp);
                if(line>>tmp)
                {
                    w.meaning.push_back(tmp);
                }else break;
            }
            testWords.push_back(w);
        }
    }
    int searchWord(string word)//???????
    {
        int left=0,right=words.size()-1;
        int mid=-1;
        while(left+1!=right)
        {
            mid=(left+right)/2;
            if(words[mid].spell==word)
            {
                return mid;
            }else if(words[mid].spell<word)
            {
                right=mid;
            }else
            {
                left=mid;
            }
        }
        if(words[left].spell==word)
        {
            return left;
        }
        if(words[right].spell==word)
        {
            return right;
        }
        return -1;
    }
    /*void sortWords(int begin,int end,vector<word> vec)
    {
        int left=begin;
        int right=end;
        int key_i = left;
        if (begin >= end)//??????????
		return;
	    while (left < right){
		//???????
		while (left < right&&vec[right].spell>= vec[key_i].spell)//???key_i ??��???
			right--;
		while (left < right&&vec[left].spell <= vec[key_i].spell)//???key_i ??????
			left++;
		swapWord(vec[left], vec[right]);
	}
	swapWord(vec[key_i], vec[left]);
	sortWords( begin, left - 1,vec);//???
	sortWords( right + 1, end,vec);
    }*/
   
    void addWord()//???????
    {
        word w;
        int n;
        string wc;
        string mn;
        cout<<"����Ҫ��ӵĵ���"<<endl;
        cin>>w.spell;
        //sortWords(0,testWords.size()-1,testWords);
        sort(words.begin(),words.end(),cmp);
        int p=searchWord(w.spell);
        if(p<testWords.size()&&p>=0)
        {
            cout<<"���󣺵����Ѵ���"<<endl;
            return;
        }else
        {
            cout<<"�����������"<<endl;
            cin>>n;
            cout<<"һ��������Ժʹ���"<<endl;
            for(int i=0;i<n;i++)
            {
                cin>>wc>>mn;
                w.wordClass.push_back(wc);
                w.meaning.push_back(mn);
            }
            testWords.push_back(w);
            cout<<"��ӳɹ�"<<endl;
        }
        
    }
    void updateWord()//??????
    {

        string w;
        cout<<"����Ҫ�޸ĵĵ���"<<endl;
        cin>>w;
        //sortWords(0,words.size()-1,words);
        sort(words.begin(),words.end(),cmp);
        int pos=searchWord(w);
        if(pos==-1)
        {
            cout<<"���󣺵��ʲ�����"<<endl;
            return;
        }
        vector<word>::iterator it=words.begin()+pos;
        cout<<"����Ҫ�޸ĵĴ������"<<endl;
        vector<string>::iterator i=(*it).wordClass.begin();
        vector<string>::iterator j=(*it).meaning.begin();
        int count=1;
        while(i!=(*it).wordClass.end())
        {
            cout<<count<<":\t"<<*i<<"\t"<<*j<<endl;
            i++;
            j++;
            count++;
        }
        int p=0;
        cin>>p;
        while(p<=0||p>count)
        {
            cout<<"�������ֳ�����Χ"<<endl;
            cin>>p;
        }
        cout<<"һ��������Ժʹ���"<<endl;
        p--;
        string tmp;
        cin>>tmp;
        *((*it).wordClass.begin()+p)=tmp;
        cin>>tmp;
        *((*it).meaning.begin()+p)=tmp;
        cout<<"�޸ĳɹ�"<<endl;
    }
    void deleteWord()//???????
    {
        cout<<"����Ҫɾ���ĵ���"<<endl;
        string w;
        int pos;
        cin>>w;
        //sortWords(0,words.size()-1,words);
        sort(words.begin(),words.end(),cmp);
        pos=searchWord(w);
        if(pos==-1)
        {
            cout<<"���󣺵��ʲ�����"<<endl;
            return;
        }
        words.erase(words.begin()+pos);
        cout<<"ɾ���ɹ�"<<endl;
    }
    void wordTest()
    {
        char c;
        for(int i=0;i<testWords.size();i++)
        {
            cout<<"��q:�˳� a:��ʾ���� c:���� k:������ʱ�"<<endl;
            cout<<testWords[i].spell<<endl;
            cin>>c;
            while (c!='q'&&c!='a'&&c!='c'&&c!='k')
            {
                cout<<"���������������:"<<endl;
                cin>>c;
            }
            if(c=='a')
            {
                for(int j=0;j<testWords[i].wordClass.size();j++)
                {
                    cout<<testWords[i].wordClass[j]<<' '<<testWords[i].meaning[j]<<endl;
                }
                cout<<"���������..."<<endl;
                cin>>c;
            }else if(c=='q')
            {
                cout<<"���˳�"<<endl;
                break;
            }else if(c=='k')
            {
                word w;
                w.spell=testWords[i].spell;
                for(int j=0;j<testWords[i].wordClass.size();j++)
                {
                    w.wordClass.push_back(testWords[i].wordClass[j]);
                    w.meaning.push_back(testWords[i].meaning[j]);
                }
                words.push_back(w);
                testWords.erase(testWords.begin()+i);
                i--;
            }
        }
    }
    ~helper()
    {
        ofstream ofs;
        ofs.open("words.txt",ios::out);
        ofs.flush();
        while(!words.empty())
        {
            word w=words.back();
            ofs<<w.spell;
            while(!w.wordClass.empty())
            {
                ofs<<' '<<w.wordClass.back()<<' '<<w.meaning.back();
                w.wordClass.pop_back();
                w.meaning.pop_back();
            }
            words.pop_back();
            ofs<<endl;
        }
        ofs.close();
        ofs.open("testWords.txt",ios::out);
        ofs.flush();
        while(!testWords.empty())
        {
            word w=testWords.back();
            ofs<<w.spell;
            while(!w.wordClass.empty())
            {
                ofs<<' '<<w.wordClass.back()<<' '<<w.meaning.back();
                w.wordClass.pop_back();
                w.meaning.pop_back();
            }
            testWords.pop_back();
            ofs<<endl;
        }
        ofs.close();
        cout<<"����ɹ�"<<endl;
    }
};
int main()
{
    helper* h=new helper();
    cout<<"ѡ�����"<<endl;
    cout<<"1:��ӵ��� 2:�޸ĵ��� 3:ɾ������ 4:���ʲ���"<<endl;
    int opration;
    cin>>opration;
    while(opration>0&&opration<=4)
    {
        switch (opration)
        {
        case 1:
            h->addWord();
            break;
        case 2:
            h->updateWord();
            break;
        case 3:
            h->deleteWord();
            break;
        case 4:
            h->wordTest();
            break;
        default:
            break;
        }
        cout<<"1:��ӵ��� 2:�޸ĵ��� 3:ɾ������ 4:���ʲ���"<<endl;
        cin>>opration;
    }
    delete h;
    return 0;
}