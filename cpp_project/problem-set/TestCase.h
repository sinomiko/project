//
// Created by mikoxmsong on 2021/12/13.
//

#ifndef PROBLEM_SET_TESTCASE_H
#define PROBLEM_SET_TESTCASE_H
#include "Solution.h"
#include "MallocTest.h"
using namespace std;

namespace TestCase {
    void testPSQuickSort() {
        Solution ps;
        std::vector<int> arr;
        for (int i = 50; i > 35; --i) {
            arr.push_back(i);
        }
        for (int i = 50; i < 65; ++i) {
            arr.push_back(i);
        }
        for (auto i :arr) {
            std::cout << i << " ";
        }
        std::cout << "" << std::endl;

        ps.quick_sort(arr, 0, arr.size()-1);
        for (auto i :arr) {
            std::cout << i << " ";
        }

    }
   
    void islandPerimeterUT(){
        Solution ps;
        vector<vector<int>> input{ {0, 1, 0, 0},{1, 1, 1, 0},{0, 1, 0, 0 },{1, 1, 0, 0} };
        int ret = ps.lc463_islandPerimeter(input);
        cout << ret << endl;
    }

    void minStackUT(){
        Solution::MinStack ms;
        ms.push(1);
        cout << ms.pop() << endl;
        ms.push(2);
        ms.push(3);
        cout << ms.min() << endl;
        ms.push(1);
        cout << ms.min() << endl;
    }
    
    void zStringTransUT(){
        Solution ps;
        string caseStr = "abc";
        auto ret = ps.lc6_convert_6(caseStr, 1);
        cout << ret << endl;
    }

    void lc5_longestPalindromeUT(){
        Solution ps;
        string caseStr = "babad";
        auto ret = ps.lc5_longestPalindrome2(caseStr);
        cout << ret << endl;
    }
    
    void lc53_maxSubArrayUT(){
        Solution ps;
        vector<int> test{5,4,-1,7,8};
        auto ret = ps.lc53_maxSubArray(test);
        cout << ret << endl;
    }
    
    void longestConsecutiveUT(){
        Solution ps;
        vector<int> test{ 9,1,-3,2,4,8,3,-1,6,-2,-4,7 };
        int ret = ps.lc124_longestConsecutive(test);
        cout << ret << endl;
    }

    void getLeastNumbersUT() {
        Solution ps;
        vector<int> t2{3,2,1 };

        vector<int> ret = ps.lc_offer_40_getLeastNumbers(t2, 2);
        for (auto& it : ret)
        {
            cout << it <<"\t";
        }
        
    }

    void lc22_generateParenthesisUT() {
        Solution ps;
        ps.lc22_generateParenthesis(2);
    }

    void romanToIntUT() {
        Solution ps;
        cout << "III" << "\t" << "3" << "\t" << ps.lc13_romanToInt("III") << std::endl;
        cout << "IV" << "\t" << "4" << "\t" << ps.lc13_romanToInt("IV") << std::endl;
        cout << "IX" << "\t" << "9" << "\t" << ps.lc13_romanToInt("IX") << std::endl;
        cout << "LVIII" << "\t" << "58" << "\t" << ps.lc13_romanToInt("LVIII") << std::endl;
        cout << "MCMXCIV" << "\t" << "1994" << "\t" << ps.lc13_romanToInt("MCMXCIV") << std::endl;
    }

    void nextGreaterElementUT(){
        Solution ps;
        vector<int> t1{ 4,1,2 };
        vector<int> t2{ 1, 3, 4, 2 };

        vector<int> ret = ps.lc496_nextGreaterElement(t1, t2);
        for (auto& it : ret)
        {
            cout << it <<"\t";
        }
    }

    void numberOfLinesUT(){
        Solution ps;
        vector<int> t1{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
        string s = "abcdefghijklmnopqrstuvwxyz";
        vector<int> ret = ps.lc806_numberOfLines(t1,s);
        for (auto& it : ret)
        {
            cout << it <<"\t";
        }
    }

    void hasAlternatingBitsUT(){
        Solution ps;
        bool ret = ps.lc693_hasAlternatingBits(8);
        cout << ret << "\t";
    }

    void flipAndInvertImageUT(){
        Solution ps;
        vector<vector<int>> input = { {1, 1, 0},{1, 0, 1},{0, 0, 0} };
        auto res = ps.lc832_flipAndInvertImage(input);
        for_each(res.begin(), res.end(), [](vector<int>& tmp){
            for (auto& it : tmp)
            {
                cout << it << endl;
            }
        }
        );
    }

    void longestCommonPrefixUT(){
        Solution ps;
        vector<vector<string>> input = { {"flower","flow","flight"},
        {"dog","racecar","car"} };
        for_each(input.begin(), input.end(), [&ps](vector<string>& tmp){
            auto res = ps.lc14_longestCommonPrefix(tmp);
            {
                cout << res << endl;
            }
        }
        );
    }

    void plusOneUT(){
        Solution ps;
        vector<vector<int>> input = { 
        //     {1,2,3},
        // {9},
        {8,9,9,9} };
        for_each(input.begin(), input.end(), [&ps](vector<int>& tmp){
            auto res = ps.lc66_plusOne(tmp);
            {
                for (auto& it : res)
                {
                    cout << it << "\t";
                }
                cout  << endl;

            }
        }
        );
    }

    void addBinaryUT(){
        Solution ps;
        vector<vector<string>> input = { 

        {"11","1"},
        {"1010","1011"},
        };
        for_each(input.begin(), input.end(), [&ps](vector<string>& tmp){
            auto res = ps.lc67_addBinary(tmp[0], tmp[1]);
            {
                cout << res << endl;
             
            }
            }
        );
    }

    void mySqrtUT(){
        Solution ps;
        vector<int> input = {4, 8};
        for_each(input.begin(), input.end(), [&ps](int tmp){
            auto res = ps.lc69_mySqrt(tmp);
            cout << tmp << "\t" << res << endl;
            }
        );
    }

    void mergeUT(){
        Solution ps;
        vector<vector<int>> input = { 
        // {1,2,3,0,0,0},
        // {2,5,6},
        {2,0},
        {1}
        };
        
        ps.lc88_merge(input[0], 1, input[1], 1);
        for (size_t i = 0; i < input.size(); i++)
        {
            cout << input[0][i] << "\t";
        }
        cout << endl;    
    }

    void mylengthOfLIS(){
        Solution ps;
        vector<int> input = {1,7,3,5,9,4,8};
        auto res = ps.lc300_lengthOfLIS(input);
        cout << "\t" << res << endl;
    }

    void generateUT(){
        Solution ps;
        auto ret = ps.lc118_generate(5);
        for (int i = 0; i < ret.size(); i++)
        {
            for (int j = 0; j < ret[i].size(); j++) {
                std::cout << ret[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    void isPalindromeUT(){
        Solution ps;
        string input = "0P";
        auto ret = ps.lc125_isPalindrome(input);
        std::cout << ret << "\t" << std::endl;
    }
    
    void vecIterUT(){
        vector<int> input = { 1,2,3,4,5,6 };

        vector<int>::iterator itBegin = input.begin();
        vector<int>::iterator next = itBegin;
        cout << *next << endl;
        for (auto& it : input)
        {
            cout << it << endl;
        }
        itBegin++;
        cout << *next << endl;
    }
    void FloatToIntUT(){
        cout << FloatParse::Float_To_Int(-1.23) << endl;
    }

    void TestMallocUT() {
        ActualClass* p1 = new ActualClass;
        p1->print();

        ActualClass* p2 = new ActualClass;
        p2->print();
        delete p1;

        p1 = new ActualClass;
        p1->print();

        ActualClass* p3 = new ActualClass;
        p3->print();

        delete p1;
        delete p2;
        delete p3;
    }
    void lc42_trapUT(){
        Solution ps;
        vector<int> t1{0,1,0,2,1,0,1,3,2,1,2,1};
        auto ret = ps.lc42_trap(t1);
        cout << ret <<"\t"; 
    }
    void lc240_searchMatrixUT(){
        Solution ps;
        vector<vector<int>> matrix  {{1,4,7,11,15},{2,5,8,12,19},{3,6,9,16,22},{10,13,14,17,24},{18,21,23,26,30}};
        int target = 5;

        auto ret = ps.lc240_searchMatrix(matrix, target);
        cout << ret <<"\t"; 
    }
    void lc105_buildTreeUT(){
        Solution ps;
        vector<int> pre{3,9,20,15,7};
        vector<int> in{9,3,15,20,7};
        auto ret = ps.lc105_buildTree(pre, in);
    }
}

#endif //PROBLEM_SET_TESTCASE_H
