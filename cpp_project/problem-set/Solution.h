//
// Created by miko on 2021/12/13.
//

#ifndef PROBLEM_SET_SOLUTION_H
#define PROBLEM_SET_SOLUTION_H
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:

    /*
    * @lc app=leetcode.cn id=5 lang=cpp
    *
    * [5] 最长回文子串
    */
    string lc5_longestPalindrome(string s) {
        int left = 0;
        int right = 0;
        int maxLen = 0;
        for (size_t i = 0; i < s.size(); i++)
        {
            lc5_longestPalindromeExtend(s, i, i, s.size(), left, right, maxLen);
            lc5_longestPalindromeExtend(s, i, i + 1, s.size(), left, right, maxLen);
        }
        return s.substr(left, maxLen);
        
    }
    void lc5_longestPalindromeExtend(const string& s, int i, int j, int len, 
    int& l, int& r, int& maxLen) {
        while(i >= 0 && j < len && s[i] == s[j]) {
            if (j - i + 1 > maxLen) {
                l = i;
                r = j;
                maxLen = j - i + 1;
            }
            i--;
            j++;
        }
    }

    string lc5_longestPalindrome2(string s) {

        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        int l = 0, r = 0, maxLen = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            for(int j = i; j < s.size(); j++) {
                if(s[i] == s[j] && (j - i <= 1 || dp[i+1][j-1])) {
                    dp[i][j] = 1;
                }
                if (dp[i][j] && j - i + 1 > maxLen) {
                    l = i;
                    r = j;
                    maxLen = j - i +1;
                }
            }
        }
        return s.substr(l, maxLen);
    }
    //leetcode-6 Z 字形变换
    string lc6_convert_6(string s, int numRows) {
        if (numRows == 1) return s;

        vector<vector<char>> lines(numRows > s.size() ? s.size() : numRows, vector<char>());
        string ret;
        bool goingDown = false;
        int idx = 0;
        for (size_t i = 0; i < s.length(); i++)
        {
            lines[idx].push_back(s[i]);
            if (idx == numRows -1 || idx == 0) {
                goingDown = !goingDown;
            }
            idx += goingDown ? 1 : -1;
        }
        for (size_t i = 0; i < lines.size(); i++)
        {
            for (int j = 0; j < lines[i].size(); j++)
            {
                ret.push_back(lines[i][j]);
            }
        }
        return ret;
    }

    /*
    * @lc app=leetcode.cn id=9 lang=cpp
    *
    * [9] 回文数
    */
    bool lc9_isPalindrome(int x) {
        if (x < 0)
        {
            return false;
        }
        
        int len = 1;
        for (len = 1; x /len >= 10; len*=10);
        while (x > 0)
        {
            int left = x / len;
            int right = x % 10;
            if (left != right)
            {
                return false;
            }
            x = (x%len) / 10;
            len /= 100;
        }
        return true;
    }
    //12. 带最小值操作的栈
    //https://www.lintcode.com/zh-cn/problem/min-stack/
    class MinStack {
    public:
        MinStack() {
            // do intialization if necessary
        }

        /*
        * @param number: An integer
        * @return: nothing
        */
        void push(int number) {
            // write your code here
            st.push_back(number);
            if ((mins.size() > 0) && (number > mins.back()))
            {
                mins.push_back(mins.back());
            }
            else {
                mins.push_back(number);
            }
        }

        /*
        * @return: An integer
        */
        int pop() {
            // write your code here
            int ret = st.back();
            st.pop_back();
            mins.pop_back();
            return ret;
        }

        /*
        * @return: An integer
        */
        int min() {
            // write your code here
            return mins.back();

        }
        vector<int> st;
        vector<int> mins;
    };

    /*
    * @lc app=leetcode.cn id=13 lang=cpp
    *
    * [13] 罗马数字转整数
    */
    int lc13_romanToInt(string s) {
        int ret = 0;
        for (size_t i = 0; i < s.size();)
        {
            switch (s[i])
            {
            case 'I': 
                if (i +1 < s.size() && s[i + 1] == 'V') {
                    ret += 4;
                    i += 2;
                    break;
                }
                if (i +1 < s.size() && s[i + 1] == 'X') {
                    ret += 9;
                    i += 2;
                    break;
                }
                ret += 1;
                i++;
                break;
            case 'V':
                ret += 5;
                i++;
                break;
            case 'X':
                if (i +1 < s.size() && s[i + 1] == 'L') {
                    ret += 40;
                    i += 2;
                    break;
                }
                if (i +1 < s.size() && s[i + 1] == 'C') {
                    ret += 90;
                    i += 2;
                    break;
                }
                ret += 10;
                i++;
                break;
            case 'L':
                ret += 50;
                i++;
                break;
            case 'C':
                if (i +1 < s.size() && s[i + 1] == 'D') {
                    ret += 400;
                    i += 2;
                    break;
                }
                if (i +1 < s.size() && s[i + 1] == 'M') {
                    ret += 900;
                    i += 2;
                    break;
                }
                ret += 100;
                i++;
                break;
            case 'D':
                ret += 500;
                i++;
                break;
            case 'M':
                ret += 1000;
                i++;
                break;
            default:
                i++;
                break;
            }
            
        }
        return ret;

    }

    /*
    * @lc app=leetcode.cn id=14 lang=cpp
    *
    * [14] 最长公共前缀
    */
    string lc14_longestCommonPrefix(vector<string>& strs) {
        int shortest_len = 300;
        std::string shortest_str;
        for (auto& str: strs)
        {
            if (str.length() < shortest_len) {
                shortest_len = str.length();
                shortest_str = str;
            }
        }
        int longest_prefix = 0;
        bool from_start = true;
        for (size_t i = 0; i < shortest_len; i++)
        {
            bool str_is_same = true;
            for (auto& str: strs)
            {
                if (str[i] != shortest_str[i])
                {
                    str_is_same = false;
                    break;
                }
            }
            if (from_start && str_is_same)
            {
                longest_prefix++;
            } else {
                from_start = false;
            }
        }
        return shortest_str.substr(0, longest_prefix);
        
    }

    /*
    * @lc app=leetcode.cn id=20 lang=cpp
    *
    * [20] 有效的括号
    */
    bool ls20_isValid(string s) {
        if (s.size() % 2) {
            return false;
        }
        unordered_map<char, char> pairs = {
            {'}', '{'},
            {']', '['},
            {')', '('},
        };
        stack<char> ret;
        for (char c : s) {
            if (pairs.count(c)) {
                if(ret.empty() || ret.top() != pairs[c]) {
                    return false;
                } else {
                    ret.pop();
                }
            } else {
                ret.push(c);
            }
        }
        return ret.empty();
    }

    /*
    * @lc app=leetcode.cn id=22 lang=cpp
    *
    * [22] 括号生成
    */
    void lc22_bt(vector<string>& ret, string& cur, int open, int close, int n) {
        if (cur.size() == 2*n) {
            ret.push_back(cur);
        }
        if (open < n) {
            cur.push_back('(');
            lc22_bt(ret, cur, open + 1, close, n);
            cur.pop_back();
        }
        if (close < open) {
            cur.push_back(')');
            lc22_bt(ret, cur, open, close+1, n);
            cur.pop_back();
        }
    }
    vector<string> lc22_generateParenthesis(int n) {
        vector<string> ret;
        string current;
        lc22_bt(ret, current, 0, 0, n);
        return ret;
    }
    /*
    * @lc app=leetcode.cn id=27 lang=cpp
    *
    * [27] 移除元素
    */
    int lc27_removeElement(vector<int>& nums, int val) {
        int new_idx = 0;
        if (nums.empty())
        {
            return 0;
        }

        for (size_t i = 0; i < nums.size(); i++)
        {
           if (nums[i] != val) {
               nums[new_idx] = nums[i];
               new_idx++;
           }
        }
        return new_idx;
        
        
    }
    /*
    * @lc app=leetcode.cn id=32 lang=cpp
    *
    * [32] 最长有效括号
    */
    int lc32_longestValidParentheses(string s) {
        int maxLen = 0;
        stack<int> stk;
        stk.push(-1);
        for (int i = 0; i < s.size(); i++) {
            if(s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    stk.push(i); 
                } else {
                    maxLen = max(maxLen, i - stk.top());
                }
            }
        }
        return maxLen;
    }
    /*
    * @lc app=leetcode.cn id=33 lang=cpp
    *
    * [33] 搜索旋转排序数组
    */
    int lc33_search(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target) {
                return mid;
            }
            if (nums[mid] == nums[l] && nums[r] == nums[mid]) {
                l++;
                r--;
            } else if (nums[l] <= nums[mid]) {
                if (nums[mid] > target && nums[l] <= target) {
                    r = mid -1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (nums[mid] < target && nums[r] >= target) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return -1;
    }
    //offer 40
    vector<int> lc_offer_40_getLeastNumbers(vector<int>& arr, int k) {
        vector<int> res(k, 0);
        if (k == 0) {
            return res;
        }
        priority_queue<int, vector<int>, std::less<int>> big_heap;
        for(int i: arr) {
            if(big_heap.empty() || big_heap.size() < k || i < big_heap.top()) {
                big_heap.push(i);
            }

            if (big_heap.size() > k) {
                big_heap.pop();
            }
        }
        while (!big_heap.empty())
        {
            res.push_back(big_heap.top());
            big_heap.pop();
        }

        return res;

    }
    /*
    * @lc app=leetcode.cn id=42 lang=cpp
    * 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
    * [42] 接雨水
    */
    int lc42_trap(vector<int>& height) {
        if (height.size() < 2) {
            return 0;
        }
        int lMax = height[0], rMax = height[height.size() - 1];
        int l = 0, r = height.size() - 1;
        int sum = 0;

        while (l < r) {
            if (lMax < height[l]) {
                lMax = height[l];
            }
            if (rMax <  height[r]) {
                rMax = height[r];
            }
            if (height[l] < height[r]) {
                sum += lMax - height[l];
                ++l;
            } else {
                sum += rMax - height[r];
                --r;
            }
        }
        return sum;
    }
    /*
    * @lc app=leetcode.cn id=53 lang=cpp
    *
    * [53] 最大子数组和
    */
    int lc53_maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size(), 0);
        int ans = nums[0];
        int sum  = 0;
        for (int i = 1; i < nums.size(); i++) {
            if (sum + nums[i]  > 0) {
                sum = sum + nums[i];
            } else {
                sum = nums[i];
            }
            ans = max(ans, sum);
        }  
        return ans;
    }
    /*
    * @lc app=leetcode.cn id=58 lang=cpp
    *
    * [58] 最后一个单词的长度
    */
    int lc58_lengthOfLastWord(string s) {
        int len = 0;
        int last_len = 0;
        for (size_t i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ') {
                if (len > 0) {
                    last_len = len;
                }
                len = 0;
            } else {
                len++;
            }
        }
        if (len > 0) {
            last_len = len;
        }
        return last_len;
    }
    /*
    * @lc app=leetcode.cn id=66 lang=cpp
    *
    * [66] 加一
    */
    vector<int> lc66_plusOne(vector<int>& digits) {
        list<int> ret;
        int cur = 1;
        for (int i = digits.size() - 1; i >= 0; i--)
        {
            if (i == digits.size() - 1) {
                if(digits[i] == 9) {
                    ret.push_front(0);
                    cur = 1;
                } else {
                    ret.push_front(digits[i] + 1);
                    cur = 0;
                }
            } else {
                if(digits[i] == 9 && cur > 0) {
                    ret.push_front(0);
                    cur = 1;
                } else {
                    ret.push_front(digits[i] + cur);
                    cur = 0;
                }
            }
        }
        if (cur > 0) {
            ret.push_front(cur);
        }
        vector<int> res;
        std::for_each(ret.begin(), ret.end(), [&res](int x){ 
            res.push_back(x);
            });
        return res;
    

    }

    /*
    * @lc app=leetcode.cn id=67 lang=cpp
    *
    * [67] 二进制求和
    */
    string lc67_addBinary(string a, string b) {
        if (a.empty()) return b;
        if (b.empty()) return a;
        string ret;
        int alen = a.length() - 1;
        int blen = b.length() - 1;
        int add = 0;
        //  a   b   add
        //  0   0   0   0
        //  0   0   1   1
        //  0   1   0   1
        //  0   1   1   0
        //  1   0   0   1
        //  1   0   1   0
        //  1   1   0   0
        //  1   1   1   1
  
        while (alen >= 0 || blen >= 0 || add)
        {
            int x = alen >= 0 ? a[alen] - '0' : 0;
            int y = blen >= 0 ? b[blen] - '0' : 0;
            int sum = x + y + add;
            add = sum / 2;
            ret += to_string(sum % 2);
            --alen;
            --blen;
        }

        std::reverse(ret.begin(), ret.end());
        return ret;
    }
    /*
    * @lc app=leetcode.cn id=69 lang=cpp
    *
    * [69] x 的平方根 
    */
     //69 给定一个非负整数，求它的开方，向下取整。
    int lc69_mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        int l = 0, r = x, mid = l + (r - l) / 2, sqr = 0;
        while (l <= r) {
            mid = l + (r - l) / 2;
            sqr = x / mid;
            if (sqr == mid) {
                return mid;
            } else if (sqr < mid) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }

        }
        return 0;
    }
    /*
    * @lc app=leetcode.cn id=70 lang=cpp
    *
    * [70] 爬楼梯
    */
    int lc70_climbStairs(int n) {
        if (n <= 2) return n;
        int an = 0, a1 = 1, a2 =2;
        for (size_t i = 3; i <= n; i++)
        {
            an = a1 + a2;
            a1 = a2;
            a2 = an;
        }
        
        return an;
    }

    /*
    * @lc app=leetcode.cn id=83 lang=cpp
    *
    * [83] 删除排序链表中的重复元素
    */
    ListNode* lc83_deleteDuplicates(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }

        head->next = lc83_deleteDuplicates(head->next);

        if (head->val == head->next->val) head = head->next;
        return head;

    }

    /*
    * @lc app=leetcode.cn id=88 lang=cpp
    *
    * [88] 合并两个有序数组
    */
    void lc88_merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if (m == 0) {
            nums1 = nums2;
            return;
        }
        if (n == 0) {
            return;
        }
        int cur_idx = nums1.size() - 1;
        int i = m - 1;
        int j = n -1;
        while (i >= 0 || j >= 0)
        {
            if(j >= 0) {
                if (i >= 0 && nums1[i] <= nums2[j]) {
                    nums1[cur_idx--] = nums2[j--];
                } else if (i < 0) {
                    nums1[cur_idx--] = nums2[j--];
                } else {
                    nums1[cur_idx--] = nums1[i--];
                }
            } else {
                nums1[cur_idx--] = nums1[i--];
            }
        }
    }
    /*
    88. Lowest Common Ancestor of a Binary Tree
    https://www.lintcode.com/zh-cn/problem/lowest-common-ancestor-of-a-binary-tree/
    * @param root: The root of the binary search tree.
    * @param A: A TreeNode in a Binary.
    * @param B: A TreeNode in a Binary.
    * @return: Return the least common ancestor(LCA) of the two nodes.
    */
    TreeNode *lc88_dfs(TreeNode * root, TreeNode * A, TreeNode * B) {
        if ((root == NULL) || (root == A) || (root == B))
        {
            return root;
        }
        TreeNode *left = lc88_dfs(root->left, A, B);
        TreeNode *right = lc88_dfs(root->right, A, B);
        if ((left!=NULL)&&(right!=NULL))
        {
            return root;
        }
        else {
            return left==NULL ? right : left;
        }
    }
    TreeNode * lc88_lowestCommonAncestor(TreeNode * root, TreeNode * A, TreeNode * B) {
        // write your code here
        return lc88_dfs(root, A, B);
    }

    /*
    * @lc app=leetcode.cn id=94 lang=cpp
    *
    * [94] 二叉树的中序遍历
    */
    vector<int> lc94_inorderTraversal(TreeNode* root) {
        vector<int> ret;
        inorderTraversal(root, ret);
        return ret;

    }
    void inorderTraversal(TreeNode* root, vector<int>& ret) {
        if (root == nullptr) {
            return;
        }
        if (root->left) {
            inorderTraversal(root->left, ret);
        }
        ret.push_back(root->val);
        if (root->right) {
            inorderTraversal(root->right, ret);
        }
        
    }

    /*
    * @lc app=leetcode.cn id=101 lang=cpp
    *
    * [101] 对称二叉树
    */
    bool lc101_isMirror(TreeNode* p, TreeNode* q) {
        if (p && !q) {
            return false;
        } else if (!p && q) {
            return false;
        } else if (!p && !q) {
            return true;
        }
        if (p->val != q->val) {
            return false;
        } else {
            return lc101_isMirror(p->left, q->right) && lc101_isMirror(p->right, q->left);
        }
    }
    bool isSymmetric(TreeNode* root) {
        return lc101_isMirror(root, root);
    }

    /*
    * @lc app=leetcode.cn id=105 lang=cpp
    *
    * [105] 从前序与中序遍历序列构造二叉树
    */
    TreeNode* lc105_rebuildTree(vector<int>& preorder, int pl, int pr, 
    vector<int>& inorder, int il, int ir) {
        if (pl > pr || il > ir) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[pl]);
        // split inorder [il, i) i [i+1, ir)
        int i = il;
        while(i < ir && inorder[i] != preorder[pl]) {
            i++;
        }
        int interval = i - il;
        root->left = lc105_rebuildTree(preorder, pl + 1, pl + interval, inorder, il, i + interval - 1);
        root->right = lc105_rebuildTree(preorder, pl + interval + 1, pr, inorder, il + interval + 1, ir);
        return root;
    }
    TreeNode* lc105_buildTree(vector<int>& preorder, vector<int>& inorder) {
        return lc105_rebuildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }

    /*
    * @lc app=leetcode.cn id=106 lang=cpp
    *
    * [106] 从中序与后序遍历序列构造二叉树
    */
    TreeNode* lc106_rebuildTree(vector<int>& inorder, int il, int ir, 
    vector<int>& postorder, int pl, int pr) {
        if (pl > pr || il > ir) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(postorder[pr]);
        // split inorder [il, i) i [i+1, ir)
        int i = il;
        while(i < ir && inorder[i] != postorder[pr]) {
            i++;
        }
        int interval = i - il;
        root->left = lc106_rebuildTree(inorder, il, i + interval - 1, postorder, pl, pl + interval - 1);
        root->right = lc106_rebuildTree(inorder, il + interval + 1, ir, postorder, pl + interval, pr - 1);
        return root;
    }
    TreeNode* lc106_buildTree(vector<int>& inorder, vector<int>& postorder) {
        return lc106_rebuildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() -1);
    }
    //107. Binary Tree Level Order Traversal II
    //https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
    int lc107_TreeNodeAtLevel(TreeNode* pRoot, int level, vector<int>& levelContent)
    {
        if (!pRoot || level < 0)
        {
            return 0;
        }

        if (level == 0)
        {
            levelContent.push_back(pRoot->val);
            return 1;
        }
        return lc107_TreeNodeAtLevel(pRoot->left, level - 1, levelContent) + lc107_TreeNodeAtLevel(pRoot->right, level - 1, levelContent);
    }

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ret;
        for (int i; ; i++)
        {
            vector<int> levelContent;
            if (!lc107_TreeNodeAtLevel(root, i, levelContent))
            {
                break;
            }
            ret.push_back(levelContent);
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }
    /*
    * @lc app=leetcode.cn id=108 lang=cpp
    *
    * [108] 将有序数组转换为二叉搜索树
    */
    TreeNode* lc108_sortedArrayToBstDFS(vector<int>& nums, int l, int r) {
        if (r < l) {
            return nullptr;
        }
        int mid = l + (r- l) / 2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = lc108_sortedArrayToBstDFS(nums, l, mid - 1);
        root->right = lc108_sortedArrayToBstDFS(nums, mid + 1, r);
        return root;
    } 
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return lc108_sortedArrayToBstDFS(nums, 0, nums.size() -1);
    }

    /*
    * @lc app=leetcode.cn id=110 lang=cpp
    *
    * [110] 平衡二叉树
    */
    int lc110_levelBst(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int l = lc110_levelBst(root->left);
        int r = lc110_levelBst(root->right);
        return max(l, r) + 1;
    }
    bool lc110_isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        return abs(lc110_levelBst(root->left) - lc110_levelBst(root->right)) > 1 ?
            false : lc110_isBalanced(root->left) && lc110_isBalanced(root->right);
    }

    /*
    * @lc app=leetcode.cn id=111 lang=cpp
    *
    * [111] 二叉树的最小深度
    */
    int lc111_minDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        int l = lc111_minDepth(root->left);
        int r = lc111_minDepth(root->right);
        return (l&&r) ? 
        1 + std::min(l, r) :
        1 + l + r;
    }

    /*
    * @lc app=leetcode.cn id=112 lang=cpp
    *
    * [112] 路径总和
    */
    bool lc112_hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) return false;
        if (!root->left && !root->right) {
            return targetSum - root->val == 0;
        }
        return lc112_hasPathSum(root->left, targetSum - root->val) ||
        lc112_hasPathSum(root->right, targetSum - root->val);

    }

    /*
    * @lc app=leetcode.cn id=118 lang=cpp
    *
    * [118] 杨辉三角
    */
    void lc118_generateTriangleDfs(vector<vector<int>>& ret, int level, int numRows) {
        if (level > numRows) {
            return;
        }
        for (int i = 0; i < level; i++)
        {
            if(i == 0 || i == level - 1) {
                ret[level - 1].push_back(1);
            } else {
                ret[level - 1].push_back(ret[level - 2][i -1] + ret[level - 2][i]);
            }
        }
        lc118_generateTriangleDfs(ret, level+1, numRows);
    }
    vector<vector<int>> lc118_generate(int numRows) {
        vector<vector<int>> ret(numRows, vector<int>());
        lc118_generateTriangleDfs(ret, 1, numRows);
        return ret;
    }

    /*
    * @lc app=leetcode.cn id=121 lang=cpp
    *
    * [121] 买卖股票的最佳时机
    */
    int lc121_maxProfit(vector<int>& prices) {
        if (prices.size() <= 1) return 0;
        int minP = prices[0];
        int maxP = 0;
        for (size_t i = 0; i < prices.size(); i++)
        {
            maxP = max(maxP, prices[i] - minP);
            minP = min(minP, prices[i]);

        }
        return maxP;
    }
    //128. 最长连续序列
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set;
        for (const int& num : nums) {
            num_set.insert(num);
        }
        int longestStreak = 0;
        for (const int& num : num_set) {
            if (!num_set.count(num - 1)) {
                int currentNum = num;
                int currentStreak = 1;

                while (num_set.count(currentNum + 1)) {
                    currentNum += 1;
                    currentStreak += 1;
                }
                longestStreak = max(longestStreak, currentStreak);
            }
        }
        return longestStreak;
    }
    /**
    * @param num: A list of integers
    * @return: An integer
    124. 最长连续序列
    https://www.lintcode.com/zh-cn/problem/longest-consecutive-sequence/
    */
    int lc124_longestConsecutive(vector<int> &num) {
        // write your code here
        set<int> seqSet;
        vector<int> seqVect;
        for (auto i : num)
            seqSet.insert(i);
        for (auto i : seqSet)
        {
            seqVect.push_back(i);
        }
        int longest = 0;
        int pre = 1;
        for (int it =0; it < seqVect.size();it++)
        {
            if (it + 1 <= seqVect.size() - 1)
            {
                if (seqVect[it] +1 == seqVect[it + 1] )
                {
                    pre++;
                }
                else
                {
                    if (pre>longest)
                    {
                        longest = pre;
                    }
                    pre = 1;
                }
            }
            else
            {
                if (pre > longest)
                {
                    longest = pre;
                }
            }
        }
        return longest;
    }

    /*
    * @lc app=leetcode.cn id=125 lang=cpp
    *
    * [125] 验证回文串
    */
    bool lc125_isPalindrome(string s) {
        for (int i = 0; i< s.size(); i++) {
            s[i] = tolower(s[i]);
        }
        int r = s.size() - 1;
        int l = 0;
        while (l < r)
        {
            bool lok = false;
            if ((s[l] >= '0' && s[l] <= '9') || (s[l] >= 'a' && s[l] <= 'z')) {
                lok = true;
            } else {
                l++;
                continue;
            }
            bool rok = false;
            if ((s[l] >= '0' && s[l] <= '9') || (s[r] >= 'a' && s[r] <= 'z')) {
                rok = true;
            } else {
                r--;
                continue;
            }
            if (lok && rok) {
                if (s[l] != s[r]) return false;
                l++;
                r--;
                continue;
            }
        }
        return true;
    }
    /*
    * @lc app=leetcode.cn id=160 lang=cpp
    *
    * [160] 相交链表
    */
    ListNode* lc160_getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* l = headA, *r = headB;
        while (l != r) {
            l = l ? l->next : headB;
            r = r ? r->next : headA;
        }
        return l;
    }

    /*
    * @lc app=leetcode.cn id=168 lang=cpp
    *
    * [168] Excel表列名称
    */
    string lc168_convertToTitle(int columnNumber) {
        string ret;
        while (columnNumber >= 1) {
            ret.push_back(((columnNumber - 1) % 26) + 'A');
            columnNumber = (columnNumber - 1) / 26;
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
    
    /*
    * @lc app=leetcode.cn id=240 lang=cpp
    *
    * [240] 搜索二维矩阵 II
    */
    bool searchMatrixDfs(vector<vector<int>>& matrix, int target, int b, int r, int t, int l) {
        if (t >= 0 && l <= r) {
            if (matrix[t][l] == target) {
                return true;
            } else if (matrix[t][l] < target) {
                return searchMatrixDfs(matrix, target, b, r, t, ++l);
            } else {
                return searchMatrixDfs(matrix, target, b, r, --t, l);
            }
        }
        return false;
    }

    bool lc240_searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty() ) {
            return false;
        }
        int m = matrix.size() - 1, n = matrix.size() - 1;
        return searchMatrixDfs(matrix, target, m, n, m, 0);
    }
    /*
    * @lc app=leetcode.cn id=300 lang=cpp
    *
    * [300] 最长递增子序列
    */
    int lc300_lengthOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums.size();
        }
        int ans = 1;
        vector<int> dp(nums.size(), 1);

        for (int i = 1; i< nums.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }

    //344. Reverse String
    //https://leetcode.com/problems/reverse-string/description/
    string lc344_reverseString(string s) {
        int index = 0;
        int len = s.size();
        while (index < len / 2) {
            std::swap(s[index], s[len - 1 - index]);
            index++;
        }
        return s;
    }

    //412. Fizz Buzz
    //https://leetcode.com/problems/fizz-buzz/description/
    vector<string> lc412_fizzBuzz(int n) {
        vector<string> ret;
        for (int index = 1; index <= n; index++)
        {
            if ((index % 3 == 0) && (index % 5 == 0))
            {
                ret.push_back("FizzBuzz");
            }
            else if (index % 3 == 0)
            {
                ret.push_back("Fizz");
            }
            else if (index % 5 == 0)
            {
                ret.push_back("Buzz");
            }
            else
            {
                ret.push_back(std::to_string(index));
            }
        }
        return ret;
    }
    //461. Hamming Distance
    //https://leetcode.com/problems/hamming-distance/description/
    int lc461_hammingDistance(int x, int y) {
        int dist = 0;
        unsigned  val = x ^ y;

        // Count the number of bits set
        while (val != 0)
        {
            // A bit is set, so increment the count and clear the bit
            dist++;
            val &= val - 1;
        }

        // Return the number of differing bits
        return dist;
    }
    //463. Island Perimeter
    //https://leetcode.com/problems/island-perimeter/description/
    int lc463_islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int total = 0;
        for (auto& items : grid)
        {
            for (auto& item : items)
            {
                if (item == 1)
                {
                    total++;
                }
            }
        }
        total *= 4;
        int adjecent = 0;
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j])
                {
                    if ((i - 1 >= 0) && grid[i - 1][j])
                    {
                        adjecent++;
                    }
                    if ((j - 1 >= 0) && grid[i][j - 1])
                    {
                        adjecent++;
                    }
                }
            }
        }
        total -= (adjecent * 2);
        return total;
    }

    //476. Number Complement
    //https://leetcode.com/problems/number-complement/description/
    int lc476_findComplement(int num) {
        unsigned int mask = ~0;
        while (num & mask) mask <<= 1;
        return  ~num&~mask;

    }
    //496. Next Greater Element I
    //https://leetcode.com/problems/next-greater-element-i/description/
    vector<int> lc496_nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
        vector<int> result(findNums.size());

        int tmp = 0;
        for (int i = 0; i < findNums.size(); i++)
        {
            int cmp = findNums[i];

            for (int j = (tmp > i ? tmp : i); j < nums.size(); j++)
            {
                if (cmp < nums[j])
                {
                    cmp = nums[j];
                    tmp = j;
                    break;
                }

            }

            if (cmp != findNums[i])
                result[i] = cmp;
            else
                result[i] = -1;
        }
        return result;
    }

    //500. Keyboard Row
    //https://leetcode.com/problems/keyboard-row/description/
    vector<string> lc500_findWords(vector<string>& words) {
        vector<string> ret;
        vector<string> TabVect{ "QWERTYUIOPqwertyuiop","ASDFGHJKLasdfghjkl","ZXCVBNMzxcvbnm" };
        for (int index = 0; index < TabVect.size(); index++)
        {
            for (auto& items : words)
            {
                int count = 0;
                for (auto ch : items)
                {
                    if (TabVect[index].find(ch) != std::string::npos)
                    {
                        count++;
                    }
                }
                if (count == items.size())
                {
                    ret.push_back(items);
                }
            }
        }
        return ret;
    }

    //557. Reverse Words in a String III
    //https://leetcode.com/problems/reverse-words-in-a-string-iii/description/
    string lc557_reverseWords(string s) {
        size_t front = 0;
        for (int i = 0; i <= s.length(); ++i) {
            if (i == s.length() || s[i] == ' ') {
                reverse(&s[front], &s[i]);
                front = i + 1;
            }
        }

        return s;
    }
    
    //561. Array Partition I
    //https://leetcode.com/problems/array-partition-i/description/
    int lc561_arrayPairSum(vector<int>& nums) {
        int sum = 0;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i += 2)
            sum += nums[i];
        return sum;
    }

    //566. Reshape the Matrix
    //https://leetcode.com/problems/reshape-the-matrix/description/
    vector<vector<int>> lc566_matrixReshape(vector<vector<int>>& nums, int r, int c) {
        vector<vector<int>> res(r, vector<int>(c));
        if (!nums.empty())
        {
            if (r*c != nums.size() * nums[0].size())
                return nums;

            int rIndex = 0, cIndex = 0;
            for (auto& row : nums)
            {
                for (auto& item : row)
                {
                    res[rIndex][cIndex++] = item;
                    if (cIndex == c)
                    {
                        cIndex = 0;
                        rIndex++;
                    }
                }
            }
        }
        return res;
    }

    //575. Distribute Candies
    //https://leetcode.com/problems/distribute-candies/description/
    int lc575_distributeCandies(vector<int>& candies) {
        unordered_set<int> kinds;
        for (int kind : candies) {
            kinds.insert(kind);
        }
        return min(kinds.size(), candies.size() / 2);
    }
         
    //617. Merge Two Binary Trees
    //https://leetcode.com/problems/merge-two-binary-trees/description/
    /**
    * Definition for a binary tree node.
    */
    TreeNode* lc617_mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr)
            return t2;
        else if (t2 == nullptr)
            return t1;
        t1->val += t2->val;
        t1->left = lc617_mergeTrees(t1->left, t2->left);
        t1->right = lc617_mergeTrees(t1->right, t2->right);
        return t1;
    }
    
    //637. Average of Levels in Binary Tree
    //https://leetcode.com/problems/average-of-levels-in-binary-tree/description/
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ret;
        for (int i = 0;; i++)
        {
            double avg = 0;
            int num = 0;
            if (!lc637_TreeNodeAtLevel(root, i, avg, num))
            {
                break;
            }
            else {
                ret.push_back(avg/num);
            }
        }
        return ret;
    }
    int lc637_TreeNodeAtLevel(TreeNode* pRoot, int level, double& avg, int& num)
    {
        if (!pRoot || level < 0)
        {
            return 0;
        }

        if (level == 0)
        {
            num++;
            avg = (avg + pRoot->val);
            return 1;
        }
        return lc637_TreeNodeAtLevel(pRoot->left, level - 1, avg, num) + lc637_TreeNodeAtLevel(pRoot->right, level - 1, avg, num);
    }

    //657. Judge Route Circle
    //https://leetcode.com/submissions/detail/151706850/
    bool lc657_judgeCircle(string moves) {
        int left = 0, right = 0, up = 0, down = 0;
        for (auto i : moves)
        {
            switch (i) {
                case 'L':
                    left++;
                    break;
                    case 'R':
                        right++;
                        break;
                        case 'U':
                            up++;
                            break;
                            case 'D':
                                down++;
                                break;
                                default:
                                    break;
            }
        }
        return (left == right) && (up == down);
    }

    //669. Trim a Binary Search Tree
    //https://leetcode.com/problems/trim-a-binary-search-tree/description/
    struct TreeNode* lc669_trimBST(struct TreeNode* root, int L, int R) {
        bool notFound = 0;
        if (root == nullptr) {
            return root;
        }
        
        if (root->val < L) {
            return lc669_trimBST(root->right, L, R);
        }
        if (root->val > R) {
            return lc669_trimBST(root->left, L, R);
        }

        root->left = lc669_trimBST(root->left, L, R);
        root->right = lc669_trimBST(root->right, L, R);

        return root;
    }
    /*
    * @lc app=leetcode.cn id=673 lang=cpp
    *
    * [673] 最长递增子序列的个数
    */
    int lc673_findNumberOfLIS(vector<int>& nums) {
        if (nums.size() <= 1) {
            return nums.size();
        }
        int ans = 1;
        vector<int> dp(nums.size(), 1);
        vector<int> count(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] > nums[j])
                {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        count[i] = count[j];
                    } else if (dp[j] + 1 == dp[i]) {
                        count[i] += count[j];
                    }
                }
                ans = max(ans, dp[i]);
            }

        }
        int result = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (ans == dp[i]) result += count[i];
        }
        return result;
    }

    /*
    * @lc app=leetcode.cn id=674 lang=cpp
    *
    * [674] 最长连续递增序列
    */
    int lc674_findLengthOfLCIS(vector<int>& nums) {
        int maxLen = 1;
        vector<int> dp(nums.size(), 1);
        for (int i = 0; i < nums.size() - 1; i++)
        {
            if (nums[i+1] > nums[i]) dp[i+1] = max(dp[i+1], dp[i] +1);
            if(dp[i+1] > maxLen) {
                maxLen= dp[i+1];
            }
        }
        return maxLen;
        
    }
    //682. Baseball Game
    //https://leetcode.com/problems/baseball-game/description/
    int lc682_calPoints(vector<string>& ops) {
        stack<int> scoreValidStack;
        int score = 0;
        for (auto& it : ops) {
            if (it == "C")
            {
                score -= scoreValidStack.top();
                scoreValidStack.pop();
            }
            else if (it == "D")
            {
                score += 2 * scoreValidStack.top();
                scoreValidStack.push(2 * scoreValidStack.top());
            }
            else if (it == "+")
            {
                int first = scoreValidStack.top();
                scoreValidStack.pop();
                int second = scoreValidStack.top();
                scoreValidStack.pop();
                int addScore = first + second;
                scoreValidStack.push(second);
                scoreValidStack.push(first);
                scoreValidStack.push(addScore);
                score += addScore;
            }
            else {
                int getScore = stoi(it);
                score += getScore;
                scoreValidStack.push(getScore);
            }
        }

        return score;
    }

    //693. Binary Number with Alternating Bits
    //https://leetcode.com/problems/binary-number-with-alternating-bits/description/
    bool lc693_hasAlternatingBits(int n) {
        return !((n - (n >> 2))&(n - (n >> 2) - 1));
    }

    //728. Self Dividing Numbers
    //https://leetcode.com/problems/self-dividing-numbers/description/
    vector<int> lc728_selfDividingNumbers(int left, int right) {
        vector<int> selfDividingNumbersVec;
        for (int i = left; i <= right; i++)
        {
            int dec = i;
            int res = 0;
            bool selfDividing = false;
            while (res = (dec % 10))
            {
                if (i%res != 0)
                {
                    selfDividing = false;
                    break;
                }
                selfDividing = true;
                dec = dec / 10;
            }
            if (selfDividing && dec == 0)
                selfDividingNumbersVec.push_back(i);
        }
        return selfDividingNumbersVec;
    }
    //766. Toeplitz Matrix
    //https://leetcode.com/problems/toeplitz-matrix/description/
    bool lc766_isToeplitzMatrix(vector<vector<int>>& matrix) {
        if (!matrix.empty())
        {
            //if( matrix.size() != matrix[0].size())
            //    return false;

            for (int i = 0; i < matrix.size(); i++)
            {
                for (int j = 0; j < matrix[0].size(); j++)
                {
                    if (i + 1 < matrix.size() && j + 1 < matrix[0].size())
                    {
                        if (matrix[i + 1][j + 1] != matrix[i][j]) return false;
                    }
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    ////766. Toeplitz Matrix
    //https://leetcode.com/problems/toeplitz-matrix/discuss/113390/C++-1-liner
    bool lc766_isToeplitzMatrix(vector<vector<int>>& m, int i = 0, int j = 0) {
        return i == m.size() - 1 || j == m[i].size() - 1 || (m[i][j] == m[i + 1][j + 1]
        && lc766_isToeplitzMatrix(m, j < m[i].size() - 2 ? i : i + 1, j < m[i].size() - 2 ? j + 1 : 0));
    }

    //771. Jewels and Stones
    //https://leetcode.com/problems/jewels-and-stones/description/
    int lc771_numJewelsInStones(string J, string S) {
        set<char> JewelsSet;
        for (auto j : J)
            JewelsSet.insert(j);
        int num = 0;
        for (auto s : S)
        {
            if (JewelsSet.find(s) != JewelsSet.end())
            {
                num++;
            }

        }
        return num;
    }
    //806. Number of Lines To Write String
    //https://leetcode.com/problems/number-of-lines-to-write-string/description/
    vector<int> lc806_numberOfLines(vector<int>& widths, string S) {
        map<char, int> count;
        vector<int> ret;
        int line = 1;
        int res = 0;
        for (auto i : S)
        {
            if (res + widths[i - 'a'] > 100)
            {
                line++;
                res = widths[i - 'a'];
            }
            else if (res + widths[i - 'a'] == 100)
            {
                line++;
                res = 0;
            }
            else
                res += widths[i - 'a'];
        }

        ret.push_back(line);
        ret.push_back(res);
        return ret;
    }

    //824. Goat Latin
    //https://leetcode.com/problems/goat-latin/description/
    string lc824_toGoatLatin(string S) {
        stringstream iss(S), oss;
        string vowels("aeiouAEIOU"), word, a;
        while (iss >> word)
        {
            a += 'a';
            if (vowels.find_first_of(word[0]) != string::npos)
                oss << ' ' << word << "ma" << a;
            else
                oss << ' ' << word.substr(1) << word[0] << "ma" << a;
        }
        return oss.str().substr(1);
    }
    
    
    //804. Unique Morse Code Words
    //https://leetcode.com/problems/unique-morse-code-words/description/
    int lc804_uniqueMorseRepresentations(vector<string>& words) {
        vector<string> morseVect = { ".-","-...","-.-.","-..",".","..-.","--.",
                                     "....","..",".---","-.-",".-..","--","-.",
                                     "---",".--.","--.-",".-.","...","-","..-",
                                     "...-",".--","-..-","-.--","--.." };
        set<string> morseSet;
        for (auto& str : words)
        {
            string morseStr;
            for (auto i : str)
            {
                morseStr += morseVect[i - 'a'];
            }
            if (!morseStr.empty())
            {
                morseSet.insert(morseStr);
            }
        }
        return morseSet.size();
    }
    //811. Subdomain Visit Count
    //https://leetcode.com/problems/subdomain-visit-count/description/
    vector<string> lc811_subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> m;
        for (const auto& str : cpdomains)
        {
            int i = str.find(" ");
            int num = stoi(str.substr(0, i));
            string domain = str.substr(i + 1, str.size() - i - 1);
            for (int n = domain.size() - 1; n >= 0; n--)
            {
                if (domain[n] == '.') m[domain.substr(n + 1, domain.size() - n - 1)] += num;
                else if (n == 0) m[domain] += num;
            }

        }
        vector<string> v;
        for (const auto& e : m) v.push_back(to_string(e.second) + " " + e.first);
        return v;
    }

    //821. Shortest Distance to a Character
    //https://leetcode.com/problems/shortest-distance-to-a-character/description/
    vector<int> lc821_shortestToChar(string S, char C) {
        vector<int> ret;
        for (int i = 0; i < S.size(); i++)
        {
            int index = lc821_nearestIndex(S, C, i);
            ret.push_back(abs(i - index));
        }
        return ret;
    }
    int lc821_nearestIndex(string S, char C, int index) {
        int left = index, right = index;
        if (S[index] == C) return index;
        while (left >= 0 || right < S.size())
        {
            if (left >= 0 && S[left] == C) { return left; }
            if (right < S.size() && S[right] == C) { return right; }
            left--;
            right++;
        }
        return -1;
    }

    //832. Flipping an Image
    //https://leetcode.com/problems/flipping-an-image/description/
    vector<vector<int>> lc832_flipAndInvertImage(vector<vector<int>>& A) {
        vector<vector<int>> res;
        for (auto& vects : A)
        {
            vector<int> tmp;
            for (vector<int>::reverse_iterator rit = vects.rbegin(); rit != vects.rend(); ++rit)
            {
                tmp.push_back(*rit);
            }
            res.push_back(tmp);
        }
        for_each(res.begin(), res.end(), [](vector<int>& tmp)
        { for (auto& it : tmp)
        {
            it = 1 - it;
        }
        }
        );
        return res;
    }
   

    void quick_sort(vector<int>& vec, int l, int r) {
        if (l > r) {
            return;
        }
        int first = l, last = r, key = vec[first];
        while (first < last) {
            while (vec[last] >= key && first < last) {
                last--;
            }
            while (vec[first] <= key && first < last) {
                first++;
            }
            if (first < last) {
                std::swap(vec[first], vec[last]);
            }
        }
        std::swap(vec[first], vec[l]);
        quick_sort(vec, l, first - 1);
        quick_sort(vec, first + 1, r);
    }
    /*
    *
    * def MergeSort(array):
    *   import math
    *   if (len(array) < 2):
    *       return array
    *   mid = math.floor(len(array)/2)
    *   left,right = array[0:mid],array[mid:]
    *   return Merge(MergeSort(left), MergeSort(right))
    * def Merge(left, right):
    *   res = []
    *   while left and right:
    *       if left[0] < right[0]:
    *           res.append(left.pop(0))
    *       else:
    *           res.append(right.pop(0))
    *   while left:
    *       res.append(left.pop(0))
    *   while right:
    *       res.append(right.pop(0))
    *   return res
    */
    // 剑指 Offer II 085. 生成匹配的括号
    // 正整数 n 代表生成括号的对数，请设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
    void generateParenthesisBT(int n, int l, int r, string& str, vector<string>& ret) {
        if (r > l|| l > n) {
            return;
        }
        if (str.size() == 2 * n) {
            ret.push_back(str);
            return;
        }
        if (l < n) {
            str.push_back('(');
            generateParenthesisBT(n, l + 1, r, str, ret);
            str.pop_back();
        }
        if (r < l) {
            str.push_back(')');
            generateParenthesisBT(n, l, r + 1, str, ret);
            str.pop_back();
        }
    }
    void Heapify(vector<int>& val, int n, int i) {
        if (i >= n) return;
        //int parent = (i - 1) / 2;
        int childrenL = 2 * i + 1;
        int childrenR = 2 * i + 2;
        int max = i;
        if (childrenL < n && val[childrenL] > val[max]) {
            max = childrenL;
        }
        if (childrenR < n && val[childrenR] > val[max]) {
            max = childrenR;
        }
        if (max != i) {
            std::swap(val[i], val[max]);
            Heapify(val, n, max);
        }
    }
    void buildHeap(vector<int>& val, int n) {
        int last_node = n - 1;
        int parent = (last_node - 1) / 2;
        for (int i = parent; i >= 0;  i--)
        {
            Heapify(val, n, i);
        }
    }
    void HeapSort(vector<int>& val) {
        buildHeap(val, val.size());
        for (size_t i = val.size() - 1; i > 0; i--) {
            // 交换
            std::swap(val[i], val[0]);
            // 交换后砍断， i逐渐减小
            // val[0]下沉操作
            Heapify(val, i, 0);
        }

    }
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        string str;
        generateParenthesisBT(n, 0, 0, str, ret);
        return ret;
    }
};

namespace ListNameSpace {
    typedef struct node {
        int data;
        node* next;
    }node;
    /*
    后端算法题
    翻转链表*/

    node* reverse_list(node* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        node* new_node = reverse_list(head->next);
        head->next->next = head;
        head->next = nullptr;
        return new_node;
    }

    /*
    m-n翻转链表---92
    */

    node* reverse_range_m_n(node* head, int m, int n) {
        if (head == nullptr || head->next == nullptr || m > n || m < 0 || n < 0) {
            return head;
        }
        int x = 1;
        node* cur = head;
        node* pre = cur;


        while (x < m) {
            pre = cur;
            cur = cur->next;
            x++;
        }
        node* t1 = pre;
        node* t2 = cur;
        node* tmp;
        while (x <= n) {
            tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
            x++;
        }
        t1->next = pre;
        t2->next = cur;
        return head;

    }
}

#include<stdio.h> //printf()
#include<stdlib.h> //atof()
//https://www.h-schmidt.net/FloatConverter/IEEE754.html
//https://blog.csdn.net/m0_37482190/article/details/87218019
namespace FloatParse{
    typedef struct FloatNode
    {
        unsigned int mantissa : 23; //尾数部分
        unsigned int exponent : 8; //指数部分
        unsigned int sign : 1;  //符号位
    } FloatNode;

    static int GetSign(const FloatNode* fn) //获得符号位
    {
        return fn->sign == 1 ? -1 : 1;
    }

    static int GetExp(const FloatNode* fn) //获得指数位
    {
        return (fn->exponent - 127); //根据IEEE754,减去127才是真正的指数位
    }
    static int Float_To_Int(float num) //将float强转成int
    {
        FloatNode* fn = (FloatNode*)&num;
        int exp = GetExp(fn);

        if (exp >= 0) {
            int mov = 23 - exp;//这个表示
            int res = (fn->mantissa | 1 << 23) >> mov;
            return res * GetSign(fn);
        } else {
            return 0;
        }
    }
    static int float_to_int(float f)
    {
        int* p = (int*)&f;
        int temp = *p;
        int sign = -1;              //判断符号位
        if ((temp & 0x80000000) == 0)
        {
            sign = 1;
        }
        int exp = (((temp >> 23) & 0x000000FF) - 127);//求出指数位
        int tail = (temp & 0x007FFFFF) | 0x00800000;//求出尾数位
        int res = tail >> (23 - exp);              //求出有效数字
        return sign * res;                          //返回整数
    }
};

namespace heapDsa {
    class Heap {
    // https://www.cnblogs.com/hello-shf/p/11393655.html
    public:
        int GetLeftChild(int k) {
            int lIdx = 2*k + 1;
            return lIdx;

        }

        int GetRightChild(int k) {
            int rIdx = 2*k + 2;
            return rIdx;
        }

        int GetParent(int k) {
            int parentIdx = (k -1) / 2;
            return parentIdx;
        }

        void SiftUp(int k) {
            int parent = GetParent(k);
            while (k > 0 && parent > 0 && vals[k] > vals[parent]) {
                std::swap(vals[k], vals[parent]);
                k = GetParent(k);
            }
        }

        void SiftDown(int k) {
            int l = GetLeftChild(k);
            while (l < vals.size()) {
                int r = l + 1;
                if (r < vals.size() && (vals[r] > vals[l])) {
                    l = r;
                }
                if (vals[l] <= vals[k]) {
                    break;
                }
                std::swap(vals[l], vals[k]);
                k = l;
                l = GetLeftChild(k);
            }
        }

        int Replace(int v) {
            int x = vals[0];
            vals[0] = v;
            SiftDown(0);
            return x;
        }

        int Top() {
            std::swap(vals[0], vals[vals.size() - 1]);
            int x = vals.back();
            vals.pop_back();
            SiftDown(0);
            return x;
        }

        void Add(int x) {
            vals.push_back(x);
            SiftUp(vals.size() -1);
        }

    private:
        std::vector<int> vals;
};
};
#endif //PROBLEM_SET_SOLUTION_H
