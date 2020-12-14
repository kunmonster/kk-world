#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

struct weight
{
    //�����ַ��Լ���Ӧ����
    char data; //�ַ�
    int key;   //���ֵĴ���(Ȩֵ)
};
typedef struct tree
{
    //��������
    char data;                  //�ַ�
    int weight;                 //Ȩֵ
    int parent, Lchild, Rchild; //���Һ���˫��
    string code;                //�ַ���Ӧ�ı���
} tree, *Hafuman;
bool comp(const weight &a, const weight &b)
{
    //�Զ���sort�������������
    return a.key < b.key;
}
int getMessage(char *messages)
{
    /*�û�������������Ϣ*/
    cout << "���������������Ϣ:" << endl;
    cin >> messages;
    return 1;
}
int DealMessage(char *messages, int &nodenumber, vector<weight> &_weight)
{
    //��ָ����Ϣ���д����ҵ��ַ������Լ�ÿ���ַ���Ȩֵ
    //�ȶ���Ϣ����ɨ���ҳ��ַ������࣬�ٸ����ַ����������ó������������ڴ����ɷ�����������Ӧ�Ŀռ��Ž��
    int len;
    len = strlen(messages);
    int cnt[256] = {};
    int k = 0;
    for (int i = 0; i < len; i++)
        cnt[(int)messages[i]]++; //ͳ��ÿ���ַ����ִ���
    struct weight weight = {0, 0};
    _weight.push_back(weight);
    for (int i = 0; i < 256; i++)
    {
        //����ַ����ִ���
        if (cnt[i] != 0)
        {

            weight.data = (char)i;
            weight.key = cnt[i];
            _weight.push_back(weight);
            // cout << (char)i << ':' << cnt[i] << endl;
            nodenumber++;
        }
    }
    return 0;
}
int createHafuman(Hafuman &hafuman, vector<weight> _weight, int n)
{
    //�����������Ϣ���ɺշ������������б�:���շ��������,����ַ����༴Ȩ����������,�ַ����ࡿ

    sort(_weight.begin(), _weight.end(), comp); //��vector������������������С�������У�ע��ӵڶ���Ԫ�ؿ�ʼ
    if (n <= 1)
        return 0;                                   //�жϽ��ĸ��������С�ڵ���1�򲻽�������Ĳ���
    hafuman = new tree[(2 * n - 1) * sizeof(tree)]; //ʹ�ý�����鱣������Ϣ
    for (int i = 0; i < n; i++)
    { //��ǰn��Ԫ�س�ʼ������Ҷ�ӽڵ�
        hafuman[i].data = (_weight.at(i + 1)).data;
        hafuman[i].weight = (_weight.at(i + 1)).key;
        hafuman[i].Lchild = -1;
        hafuman[i].parent = 0;
        hafuman[i].Rchild = -1;
        hafuman[i].code = "";
    }
    for (int i = n; i < 2 * n - 1; i++)
    { //�Գ���Ҷ�ӽ��֮��Ľ����г�ʼ��
        hafuman[i].data = '0';
        hafuman[i].Lchild = 0;
        hafuman[i].parent = 0;
        hafuman[i].Rchild = 0;
        hafuman[i].weight = 0;
        hafuman[i].code = "";
    }

    int j = n;
    for (int i = 0; i < (2 * n - 1); i += 2)
    {
        //�ӵ�n+1����㿪ʼ���
        if ((hafuman[i].parent == 0) && (hafuman[i + 1].parent == 0))
        {
            hafuman[i].parent = j;
            hafuman[i + 1].parent = j;
            hafuman[j].Lchild = i;
            hafuman[j].Rchild = i + 1;
            hafuman[j].weight = hafuman[i].weight + hafuman[i + 1].weight;
            ++j;
        }
    }
    char *cd = new char[n * sizeof(char)];
    cd[n - 1] = '\0'; //��������ַ�
    for (int i = 0; i < n; i++)
    {
        int start = n - 1;
        for (int c = i, f = hafuman[i].parent; f != 0; c = f, f = hafuman[f].parent)
        {
            if (hafuman[f].Lchild == c)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
            hafuman[i].code.push_back(cd[start]); //���������ַ�����ʱ����������һ�����ַ�������

        }
        string str(hafuman[i].code.rbegin(),hafuman[i].code.rend());
        hafuman[i].code = str;
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << hafuman[i].data << ":" << hafuman[i].code << endl;
    // }
    return 1;
}
void encode(char *messages, string &has_translated, Hafuman hafuman, int n)
{
    //���û��������Ϣ���б��벢���ַ����������ô���
    //�����б��û��������Ϣ,���������ö���,�շ�����,�ַ����ࡿ
    int length = strlen(messages);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (messages[i] == hafuman[j].data)
            {
                has_translated = has_translated + hafuman[j].code;
                break;
            }
            else
            {
                continue;
            }
        }
    }
}
void decode(string information, Hafuman hafuman, int n, string &has_decode)
{
    int flag = 2 * n - 2;
    int i = 0;
    const char *k = information.c_str();
    while (i < information.length())
    {
        if (k[i] == '0')
        {
            if (flag != -1)
            {

                flag = hafuman[flag].Lchild;
                if (hafuman[flag].Lchild == -1)
                {
                    if (hafuman[flag].data != '0')
                    {
                        has_decode.push_back(hafuman[flag].data);
                        i++;
                        flag = 2 * n - 2;
                        continue;
                    }
                }
                else{
                    i++;
                    continue;
                }
            }
            else
            {
                flag = 2 * n - 2;
                i++;
                continue;
            }
        }
        else
        {
            if (flag != -1)
            {

                flag = hafuman[flag].Rchild;
                if (hafuman[flag].Rchild == -1)
                {
                    if (hafuman[flag].data != '0')
                    {
                        has_decode.push_back(hafuman[flag].data);
                        flag = 2 * n - 2;
                        i++;
                        continue;
                    }
                }
                else{
                    i++;
                    continue;
                }
            }
            else
            {
                flag = 2 * n - 2;
                i++;
                continue;
            }
        }
    }
}

int main()
{
    char *messages = new char[1000];             //��ŵõ�����Ϣ��ʼ��Ϊ1000
    int nodenumber = 0;                          //�ַ������ʼ��Ϊ0
    string has_encode = "";                      //��ű�������Ϣ
    string has_decode = "";                      //��Ž�������Ϣ
    vector<weight> _weight;                      //����ַ������Ӧ��Ȩֵ
    Hafuman hafuman;                             //�շ������
    getMessage(messages);                        //�û�������Ϣ
    DealMessage(messages, nodenumber, _weight);  //�����û��������Ϣ�����������Ϣ��ŵ�vector������
    createHafuman(hafuman, _weight, nodenumber); //���ݴ��������Ϣ���ɺշ�����
    encode(messages, has_encode, hafuman, nodenumber);
    decode(has_encode, hafuman, nodenumber, has_decode);
    cout << "�������Ϣ:" << has_encode << endl;
    cout << "�������Ϣ:" << has_decode << endl;
    system("pause");
    return 0;
}