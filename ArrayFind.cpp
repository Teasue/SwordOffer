#include<vector>
#include<stack>
#include<queue>     
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

    // 反转链表
    // Pre前一个，next是后一个，反过来
    ListNode* ReverseList(ListNode* pHead) {
        if (pHead == NULL)
            return NULL;

        ListNode *pre = NULL;
        ListNode *next = NULL;
        while(pHead != NULL)
        {
            next = pHead->next;
            pHead->next = pre;
            pre = pHead;
            pHead = next;
        }

        return pre;
    }

    // 两个递增列表合并，保证递增
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1 == NULL)
            return pHead2;

        if(pHead2 == NULL)
            return pHead1;
        
        ListNode* res = NULL;
        if(pHead1->val <= pHead2->val)
        {
            res = pHead1;
            res->next = Merge(pHead1->next, pHead2);
        }
        else
        {
            res = pHead2;
            res->next = Merge(pHead2->next, pHead1);
        }

        return res;
    }

    struct TreeNode {
	    int val;
	    struct TreeNode *left;
	    struct TreeNode *right;
	    TreeNode(int x) :
			val(x), left(NULL), right(NULL) {}
    };
    // 判断B是不是A的子结构
    bool isSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot2 == NULL)
            return true;
        if(pRoot1 == NULL)
            return false;
        if(pRoot2->val == pRoot1->val)
        {
            return isSubtree(pRoot1->left, pRoot2->left) 
            && isSubtree(pRoot1->right, pRoot2->right);
        }
        else
        {
            return false;
        }
    }
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot1 == NULL || pRoot2 == NULL)
            return false;

        return isSubtree(pRoot1, pRoot2) || HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    } 

    // 镜像二叉树
    void Mirror(TreeNode *pRoot) {
        if(pRoot == NULL)
            return;

        TreeNode *tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;

        Mirror(pRoot->left);
        Mirror(pRoot->right);
    }

    //输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字
    vector<int> printMatrix(vector<vector<int> > matrix) {
        vector<int> re;
        int row = matrix.size();
        int col = matrix[0].size();

         if (row == 0 || col == 0)
            return re;

        int left = 0, top = 0, right = col - 1, bottom = row - 1;
        while(left <= right && top <= bottom)
        {
            for (int i = left; i <= right; i++)
                re.push_back(matrix[top][i]);

            for (int j = top + 1; j <= bottom; j++)
                re.push_back(matrix[j][right]);

            if (top != bottom)
            {
                for (int m = right - 1; m >= left; m--)
                    re.push_back(matrix[bottom][m]);
            }

            if (left != right)
            {
                for (int n = bottom - 1; n > top; n--)
                    re.push_back(matrix[n][left]);
            }

            left++, top++, right--, bottom--;
        }
        return re;
    }
};


class Solution3 {
public:
    // 实现栈，能够得到栈中最小元素的min函数，O（1）时间复杂度
    stack<int> s1;
    stack<int> s2;
    void push(int value) {
        s1.push(value);

        if (s2.empty() || s2.top() > value)
            s2.push(value);
    }
    void pop() {
        int re = s1.top();
        s1.pop();

        if(s2.top() == re)
            s2.pop();
    }
    int top() {
        return s1.top();
    }
    int min() {
        return s2.top();
    }

    // 判断popV是不是pushV的弹出序列
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if (pushV.size() == 0)
            return false;

        vector<int> stack;
        for (int i = 0, j = 0; i < pushV.size();)
        {
            stack.push_back(pushV[i++]);
            while(j < popV.size() && stack.back() == popV[j])
            {
                stack.pop_back();
                j++;
            }
        }

        return stack.empty();
    }

    struct TreeNode {
	    int val;
	    struct TreeNode *left;
	    struct TreeNode *right;
	    TreeNode(int x) :
			val(x), left(NULL), right(NULL) {}
    };

    // 从上往下打印出二叉树的每个节点，同层节点从左至右打印。
    // 层次遍历，借助队列
    vector<int> PrintFromTopToBottom(TreeNode* root) {
        vector<int> re;
        if(root == NULL)
            return re;

        queue<TreeNode *> q;
        q.push(root);
        while(!q.empty())
        {
            re.push_back(q.front()->val);
            if(q.front()->left != NULL)
                q.push(q.front()->left);

            if(q.front()->right != NULL)
                q.push(q.front()->right);

            q.pop();
        }

        return re;
    }

    //输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
    //如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
    //BST的后序序列的合法序列是，对于一个序列S，最后一个元素是x （也就是根），
    //如果去掉最后一个元素的序列为T，那么T满足：T可以分成两段，前一段（左子树）小于x，
    //后一段（右子树）大于x，且这两段（子树）都是合法的后序序列。
    bool VerifySquenceOfBST(vector<int> sequence) {
        if (sequence.size() == 0)
            return false;

        return isLastOrder(sequence, 0, sequence.size() -1);
    }
    bool isLastOrder(vector<int>& sequece, int b, int e)
    {
        if (b == e)
            return true;
    
        int mid = b;
        while(sequece[mid++] < sequece[e] && mid < e);

        int tmp = mid;
        while (sequece[tmp++] > sequece[e] && tmp < e);

        if(tmp < e)
            return false;
 
        if(mid == b || mid == e)
        {
            return isLastOrder(sequece, b, e-1);
        }
        else
        {
            return (isLastOrder(sequece, b, mid-1) && isLastOrder(sequece, mid, e-1));
        }
    }
};