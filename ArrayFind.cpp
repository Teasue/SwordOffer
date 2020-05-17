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

    // 12345旋转数组34512，求最小值 二分法
    int minNumberInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0)
            return 0;

        int begin = 0;
        int end = rotateArray.size() - 1;
        while (begin < end)
        {
            if (rotateArray[begin] < rotateArray[end])
                return rotateArray[begin];

            int mid = begin + (end - begin) / 2;

            if (rotateArray[mid] > rotateArray[begin])
                begin = mid + 1;
            else if (rotateArray[mid] < rotateArray[end])
                end = mid;
            else
                begin ++;
        }

        return rotateArray[begin];
    }

    // 求斐波那契数列
    int Fibonacci(int n) {
        if (n == 0)
            return 0;

        if (n <= 2)
            return 1;

        return Fibonacci(n - 1) + Fibonacci(n - 2);
    }

    // 这个动态规划太秀了
    int Fibonacci(int n) {
        int f = 0, g = 1;
        while(n--) {
            g += f;
            f = g - f;
        }
        return f;
    }

    // 第n次跳法就是以1开头(fn-1)还是以2开头（fn-2）
    int jumpFloor(int number) {
        if(number < 0)
            return 0;
        
        if(number == 1 || number == 2)
            return number;

        return jumpFloor(number - 1) + jumpFloor(number - 2);
    }

    // 可以一次跳n格，第n次变为fn-1+fn-2+......+f2+f1
    int jumpFloorII(int number) {
        if(number == 1)
            return 1;
        
        return 2 * jumpFloorII(number - 1);
    }

    int rectCover(int number) {
        if(number < 0)
            return 0;
        
        if(number == 1 || number == 2)
            return number;

        return rectCover(number - 1) + rectCover(number - 2);
    }

    // 求一个整数的二进制中1的个数
    // 将每一位和1求与
    // 不能将n右移。因为负数最高位全部补位1
    int  NumberOf1(int n) {
        int count = 0;
        int flag = 1;
        while(flag != 0)
        {
            if ((n & flag) != 0)
                count++;

            flag = flag << 1;
        }

        return count;
    }

    // 如果一个整数不为0，那么这个整数至少有一位是1。如果我们把这个整数减1，那么原来处在整数最右边的1就会变为0，原来在1后面的所有的0都会变成1(如果最右边的1后面还有0的话)。其余所有位将不会受到影响。
    int NumberOf1(int n) {
        int count = 0;
        while(n!= 0){
            count++;
            n = n & (n - 1);
         }
        return count;
    }

    // 一个数的n次方
    double Power(double base, int exponent) {
        double tmp = 1;
        int n = exponent > 0 ? exponent : -exponent;
        while (n != 0)
        {
            if ((n & 1) != 0)
                tmp *= base;
                
            base *= base;
            n = n >> 1;
        }

        return exponent > 0 ? tmp : (1/tmp);
    }

    // 将一个数组中奇数排在偶数前面
    void reOrderArray(vector<int> &array) {
        if (array.empty())
            return;

        int count = 0;
        vector<int>::iterator itor;
        for (itor = array.begin(); itor != array.end(); itor++)
        {
            if (*itor % 2 == 1)
            {
                int tmp = *itor;
                array.erase(itor);
                array.insert(array.begin() + count, tmp);
                count++;
            }
        }
    }
    struct ListNode {
	    int val;
	    struct ListNode *next;
	    ListNode(int x) :
			val(x), next(NULL) { }
    };

    // 求链表的倒数第几个节点
    // 两个指针追赶。相差为k
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(pListHead == NULL || k==0)
            return NULL;
            
        int n = 0;
        ListNode *p = pListHead;
        while(pListHead != NULL)
        {
            if (n >= k)
                p = p->next;

            n++;
            pListHead = pListHead->next;
        }
        return n < k ? NULL : p;
    }
};
