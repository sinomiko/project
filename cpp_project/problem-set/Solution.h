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

class Solution {
public:
    //771. Jewels and Stones
    //https://leetcode.com/problems/jewels-and-stones/description/
    int numJewelsInStones(string J, string S) {
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

    //804. Unique Morse Code Words
    //https://leetcode.com/problems/unique-morse-code-words/description/
    int uniqueMorseRepresentations(vector<string>& words) {
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

    //461. Hamming Distance
    //https://leetcode.com/problems/hamming-distance/description/
    int hammingDistance(int x, int y) {
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

    //657. Judge Route Circle
    //https://leetcode.com/submissions/detail/151706850/
    bool judgeCircle(string moves) {
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

    //617. Merge Two Binary Trees
    //https://leetcode.com/problems/merge-two-binary-trees/description/
    /**
    * Definition for a binary tree node.
    */
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr)
            return t2;
        else if (t2 == nullptr)
            return t1;
        t1->val += t2->val;
        t1->left = mergeTrees(t1->left, t2->left);
        t1->right = mergeTrees(t1->right, t2->right);
        return t1;
    }

    /*
    88. Lowest Common Ancestor of a Binary Tree
    https://www.lintcode.com/zh-cn/problem/lowest-common-ancestor-of-a-binary-tree/
    * @param root: The root of the binary search tree.
    * @param A: A TreeNode in a Binary.
    * @param B: A TreeNode in a Binary.
    * @return: Return the least common ancestor(LCA) of the two nodes.
    */
    TreeNode *dfs(TreeNode * root, TreeNode * A, TreeNode * B) {
        if ((root == NULL) || (root == A) || (root == B))
        {
            return root;
        }
        TreeNode *left = dfs(root->left, A, B);
        TreeNode *right = dfs(root->right, A, B);
        if ((left!=NULL)&&(right!=NULL))
        {
            return root;
        }
        else {
            return left==NULL ? right : left;
        }
    }
    TreeNode * lowestCommonAncestor(TreeNode * root, TreeNode * A, TreeNode * B) {
        // write your code here
        return dfs(root, A, B);
    }

    //728. Self Dividing Numbers
    //https://leetcode.com/problems/self-dividing-numbers/description/
    vector<int> selfDividingNumbers(int left, int right) {
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

    //561. Array Partition I
    //https://leetcode.com/problems/array-partition-i/description/
    int arrayPairSum(vector<int>& nums) {
        int sum = 0;
        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 1; i += 2)
            sum += nums[i];
        return sum;
    }

    //811. Subdomain Visit Count
    //https://leetcode.com/problems/subdomain-visit-count/description/
    vector<string> subdomainVisits(vector<string>& cpdomains) {
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
    int nearestIndex(string S, char C, int index) {
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

    vector<int> shortestToChar(string S, char C) {
        vector<int> ret;
        for (int i = 0; i < S.size(); i++)
        {
            int index = nearestIndex(S, C, i);
            ret.push_back(abs(i - index));
        }
        return ret;
    }

    //476. Number Complement
    //https://leetcode.com/problems/number-complement/description/
    int findComplement(int num) {
        unsigned int mask = ~0;
        while (num & mask) mask <<= 1;
        return  ~num&~mask;

    }

    //344. Reverse String
    //https://leetcode.com/problems/reverse-string/description/
    string reverseString(string s) {
        int index = 0;
        int len = s.size();
        while (index < len / 2) {
            std::swap(s[index], s[len - 1 - index]);
            index++;
        }
        return s;
    }

    //557. Reverse Words in a String III
    //https://leetcode.com/problems/reverse-words-in-a-string-iii/description/
    string reverseWords(string s) {
        size_t front = 0;
        for (int i = 0; i <= s.length(); ++i) {
            if (i == s.length() || s[i] == ' ') {
                reverse(&s[front], &s[i]);
                front = i + 1;
            }
        }

        return s;
    }

    //500. Keyboard Row
    //https://leetcode.com/problems/keyboard-row/description/
    vector<string> findWords(vector<string>& words) {
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

    //669. Trim a Binary Search Tree
    //https://leetcode.com/problems/trim-a-binary-search-tree/description/
    struct TreeNode* trimBST(struct TreeNode* root, int L, int R) {
        bool notFound = 0;
        if (root == nullptr) {
            return root;
        }
        
        if (root->val < L) {
            return trimBST(root->right, L, R);
        }
        if (root->val > R) {
            return trimBST(root->left, L, R);
        }

        root->left = trimBST(root->left, L, R);
        root->right = trimBST(root->right, L, R);

        return root;
    }

    //682. Baseball Game
    //https://leetcode.com/problems/baseball-game/description/
    int calPoints(vector<string>& ops) {
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

    //575. Distribute Candies
    //https://leetcode.com/problems/distribute-candies/description/
    int distributeCandies(vector<int>& candies) {
        unordered_set<int> kinds;
        for (int kind : candies) {
            kinds.insert(kind);
        }
        return min(kinds.size(), candies.size() / 2);
    }

    //412. Fizz Buzz
    //https://leetcode.com/problems/fizz-buzz/description/
    vector<string> fizzBuzz(int n) {
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
    //leetcode-6 Z 字形变换
    string convert_6(string s, int numRows) {
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

    //offer 40
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
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
    * @lc app=leetcode.cn id=9 lang=cpp
    *
    * [9] 回文数
    */
    bool isPalindrome(int x) {
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

    /*
    * @lc app=leetcode.cn id=13 lang=cpp
    *
    * [13] 罗马数字转整数
    */
    int romanToInt(string s) {
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
    string longestCommonPrefix(vector<string>& strs) {
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
    * @lc app=leetcode.cn id=27 lang=cpp
    *
    * [27] 移除元素
    */
    int removeElement(vector<int>& nums, int val) {
        int new_idx = 0;
        if (nums.empty())
        {
            return 0;
        }

        for (size_t i = 0; i < nums.size(); i++)
        {
           if (nums[i] != val) {
               new_idx++;
               nums[new_idx] = nums[i];
           }
        }
        return new_idx;
        
        
    }
    //463. Island Perimeter
    //https://leetcode.com/problems/island-perimeter/description/
    int islandPerimeter(vector<vector<int>>& grid) {
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

    /**
    * @param num: A list of integers
    * @return: An integer
    124. 最长连续序列
    https://www.lintcode.com/zh-cn/problem/longest-consecutive-sequence/
    */
    int longestConsecutive(vector<int> &num) {
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

    //566. Reshape the Matrix
    //https://leetcode.com/problems/reshape-the-matrix/description/
    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
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

    //766. Toeplitz Matrix
    //https://leetcode.com/problems/toeplitz-matrix/description/
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
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
    bool isToeplitzMatrix(vector<vector<int>>& m, int i = 0, int j = 0) {
        return i == m.size() - 1 || j == m[i].size() - 1 || (m[i][j] == m[i + 1][j + 1]
        && isToeplitzMatrix(m, j < m[i].size() - 2 ? i : i + 1, j < m[i].size() - 2 ? j + 1 : 0));
    }

    //824. Goat Latin
    //https://leetcode.com/problems/goat-latin/description/
    string toGoatLatin(string S) {
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

    //496. Next Greater Element I
    //https://leetcode.com/problems/next-greater-element-i/description/
    vector<int> nextGreaterElement(vector<int>& findNums, vector<int>& nums) {
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

    //806. Number of Lines To Write String
    //https://leetcode.com/problems/number-of-lines-to-write-string/description/
    vector<int> numberOfLines(vector<int>& widths, string S) {
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

    //637. Average of Levels in Binary Tree
    //https://leetcode.com/problems/average-of-levels-in-binary-tree/description/
    int TreeNodeAtLevel(TreeNode* pRoot, int level, double& avg, int& num)
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
        return TreeNodeAtLevel(pRoot->left, level - 1, avg, num) + TreeNodeAtLevel(pRoot->right, level - 1, avg, num);
    }

    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> ret;
        for (int i = 0;; i++)
        {
            double avg = 0;
            int num = 0;
            if (!TreeNodeAtLevel(root, i, avg, num))
            {
                break;
            }
            else {
                ret.push_back(avg/num);
            }
        }
        return ret;
    }

    //107. Binary Tree Level Order Traversal II
    //https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
    int TreeNodeAtLevel(TreeNode* pRoot, int level, vector<int>& levelContent)
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
        return TreeNodeAtLevel(pRoot->left, level - 1, levelContent) + TreeNodeAtLevel(pRoot->right, level - 1, levelContent);
    }

    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> ret;
        for (int i; ; i++)
        {
            vector<int> levelContent;
            if (!TreeNodeAtLevel(root, i, levelContent))
            {
                break;
            }
            ret.push_back(levelContent);
        }

        reverse(ret.begin(), ret.end());
        return ret;
    }

    //693. Binary Number with Alternating Bits
    //https://leetcode.com/problems/binary-number-with-alternating-bits/description/
    bool hasAlternatingBits(int n) {
        return !((n - (n >> 2))&(n - (n >> 2) - 1));
    }

    //832. Flipping an Image
    //https://leetcode.com/problems/flipping-an-image/description/
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
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
    //69 给定一个非负整数，求它的开方，向下取整。
    int MinSquare(int a) {
        if (a == 0) {
            return 0;
        }
        int l = 0, r = a, mid = l + (r - l) / 2, sqr = 0;
        while (l <= r) {
            mid = l + (r - l) / 2;
            sqr = a / mid;
            if (sqr == mid) {
                return mid;
            } else if (sqr < mid) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }

        }
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
#endif //PROBLEM_SET_SOLUTION_H
