#include<vector>
#include<stack>   
using namespace std;  
  
class Solution {
public:
    //   二维数组查找，更好的办法是从左下或者右上开始
    bool Find(int target, vector<vector<int> > array) {
        if (array.empty())
            return false;

        for (int i = 0; i < array.size(); i ++)
        {
            for (int j = 0; j < array[i].size(); j ++)
            {
                if (array[i][j] == target){
                    return true;
                }
            }
        }

        return false;
    }

    //  字符串替换，重点在于
    // 1从前往后还是从后往前，决定了字符的移动次数
    // 2在原字符串修改还是新的，原字符串考虑长度不够问题
	void replaceSpace(char *str,int length) {
        if (length <= 0 || str == NULL)
            return;

        int count = 0;
        for (int i = 0l; i < length; i ++)
        {
            if (str[i] == ' ')
            {
                count++;
            }
        }
        int oldlen = length;
        int newlen = length + count * 2;
        while (oldlen >= 0)
        {
            if (str[oldlen] == ' ')
            {
                str[newlen --] = '0';
                str[newlen --] = '2';
                str[newlen --] = '%';
            }
            else
            {
                str[newlen--] = str[oldlen];
            }

            oldlen--;
        }
    }

    // 链表倒着输出，这里的递归函数真的秀啊
    struct ListNode
    {
        int val;
        struct ListNode *next;
        ListNode(int x) :
            val(x), next(NULL) {
        }
    };
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> re;
        if(head != NULL)
        {
            re.insert(re.begin(), head->val);
            if (head->next != NULL)
            {
                vector<int> tmpvec = printListFromTailToHead(head->next);
                if (tmpvec.size() > 0)
                {
                    re.insert(re.begin(), tmpvec.begin(), tmpvec.end());
                }
            }
        }

        return re;
    }

    // 已知树的前序和中序，求树。
    // 前序知道根，利用根在中序找到左右子树。
    struct TreeNode 
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if (pre.size() == 0 || vin.size() == 0)
            return NULL;

        return construct(pre, 0, pre.size() - 1, vin, 0, vin.size() - 1);
    }
private:
    TreeNode* construct(vector<int> pre,int ps, int pe, vector<int> vin, int vs, int ve) {
        if (ps > pe || vs > ve)
            return NULL;

        TreeNode *root = new TreeNode(pre[ps]);
        for (int i = vs;i <= ve;i ++)
        {
            if (vin[i] == pre[ps])
            {
                root->left = construct(pre, ps+1, ps+i-vs, vin, vs, i-1);
                root->right = construct(pre, ps+1+i-vs, pe, vin, i+1, ve);
                break;
            }
        }

        return root;
    }


};

class Solution2
{
public:

    // 利用两个队列实现栈：一个栈保存数据，一个栈用于把数据倒过来
    // 思考两个栈实现队列
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if(stack2.empty())
        {
            while(!stack1.empty())
            {
                int a = stack1.top();
                stack2.push(a);
                stack1.pop();
            }
        }
        int a = stack2.top();
        stack2.pop();

        return a;
    }

private:
    stack<int> stack1;
    stack<int> stack2;

    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0)
            return 0;

        int begin = 0;
        int end = rotateArray.size() - 1;
        while (begin < end)
        {
            int mid = begin + (end - begin) / 2;

            if (rotateArray[mid] > rotateArray[begin])
                begin = mid + 1;
            else if (rotateArray[mid] < rotateArray[end])
                end = mid;
            else
                end = end - 1;
        }

        return rotateArray[begin];
    }
};
