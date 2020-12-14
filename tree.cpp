#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

struct weight
{
    //保存字符以及对应次数
    char data; //字符
    int key;   //出现的次数(权值)
};
typedef struct tree
{
    //存放树结点
    char data;                  //字符
    int weight;                 //权值
    int parent, Lchild, Rchild; //左右孩子双亲
    string code;                //字符对应的编码
} tree, *Hafuman;
bool comp(const weight &a, const weight &b)
{
    //自定义sort函数的排序规则
    return a.key < b.key;
}
int getMessage(char *messages)
{
    /*用户输入想编码的信息*/
    cout << "请输入你想编码信息:" << endl;
    cin >> messages;
    return 1;
}
int DealMessage(char *messages, int &nodenumber, vector<weight> &_weight)
{
    //对指定信息进行处理找到字符种类以及每种字符的权值
    //先对信息进行扫描找出字符的种类，再根据字符的种类数得出结点个数，在内存自由分配区分配相应的空间存放结点
    int len;
    len = strlen(messages);
    int cnt[256] = {};
    int k = 0;
    for (int i = 0; i < len; i++)
        cnt[(int)messages[i]]++; //统计每个字符出现次数
    struct weight weight = {0, 0};
    _weight.push_back(weight);
    for (int i = 0; i < 256; i++)
    {
        //输出字符出现次数
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
    //根据输入的信息生成赫夫曼树，参数列表:【赫夫曼树结点,存放字符种类即权的向量容器,字符种类】

    sort(_weight.begin(), _weight.end(), comp); //将vector向量容器进行排序由小到大排列，注意从第二个元素开始
    if (n <= 1)
        return 0;                                   //判断结点的个数，如果小于等于1则不进行下面的操作
    hafuman = new tree[(2 * n - 1) * sizeof(tree)]; //使用结点数组保存结点信息
    for (int i = 0; i < n; i++)
    { //对前n个元素初始化存入叶子节点
        hafuman[i].data = (_weight.at(i + 1)).data;
        hafuman[i].weight = (_weight.at(i + 1)).key;
        hafuman[i].Lchild = -1;
        hafuman[i].parent = 0;
        hafuman[i].Rchild = -1;
        hafuman[i].code = "";
    }
    for (int i = n; i < 2 * n - 1; i++)
    { //对除了叶子结点之外的结点进行初始化
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
        //从第n+1个结点开始存点
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
    cd[n - 1] = '\0'; //编码结束字符
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
            hafuman[i].code.push_back(cd[start]); //将编码存回字符结点此时是逆序在下一步将字符串逆序

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
    //将用户输入的信息进行编码并以字符串对象引用带出
    //参数列表【用户输入的信息,编码后的引用对象,赫夫曼树,字符种类】
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
    char *messages = new char[1000];             //存放得到的信息初始化为1000
    int nodenumber = 0;                          //字符种类初始化为0
    string has_encode = "";                      //存放编码后的信息
    string has_decode = "";                      //存放解码后的信息
    vector<weight> _weight;                      //存放字符及其对应的权值
    Hafuman hafuman;                             //赫夫曼结点
    getMessage(messages);                        //用户输入信息
    DealMessage(messages, nodenumber, _weight);  //处理用户输入的信息将处理过的信息存放到vector容器中
    createHafuman(hafuman, _weight, nodenumber); //根据处理过的信息生成赫夫曼树
    encode(messages, has_encode, hafuman, nodenumber);
    decode(has_encode, hafuman, nodenumber, has_decode);
    cout << "编码的信息:" << has_encode << endl;
    cout << "解码的信息:" << has_decode << endl;
    system("pause");
    return 0;
}