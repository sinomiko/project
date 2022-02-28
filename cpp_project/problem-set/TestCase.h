//
// Created by mikoxmsong on 2021/12/13.
//

#ifndef PROBLEM_SET_TESTCASE_H
#define PROBLEM_SET_TESTCASE_H
#include "Solution.h"

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
        int ret = ps.islandPerimeter(input);
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
        auto ret = ps.convert_6(caseStr, 1);
        cout << ret << endl;
    }

    void longestConsecutiveUT(){
        Solution ps;
        vector<int> test{ 9,1,-3,2,4,8,3,-1,6,-2,-4,7 };
        int ret = ps.longestConsecutive(test);
        cout << ret << endl;
    }

    void getLeastNumbersUT() {
        Solution ps;
        vector<int> t2{3,2,1 };

        vector<int> ret = ps.getLeastNumbers(t2, 2);
        for (auto& it : ret)
        {
            cout << it <<"\t";
        }
        
    }

    void romanToIntUT() {
        Solution ps;
        cout << "III" << "\t" << "3" << "\t" << ps.romanToInt("III") << std::endl;
        cout << "IV" << "\t" << "4" << "\t" << ps.romanToInt("IV") << std::endl;
        cout << "IX" << "\t" << "9" << "\t" << ps.romanToInt("IX") << std::endl;
        cout << "LVIII" << "\t" << "58" << "\t" << ps.romanToInt("LVIII") << std::endl;
        cout << "MCMXCIV" << "\t" << "1994" << "\t" << ps.romanToInt("MCMXCIV") << std::endl;
    }

    void nextGreaterElementUT(){
        Solution ps;
        vector<int> t1{ 4,1,2 };
        vector<int> t2{ 1, 3, 4, 2 };

        vector<int> ret = ps.nextGreaterElement(t1, t2);
        for (auto& it : ret)
        {
            cout << it <<"\t";
        }
    }
    void numberOfLinesUT(){
        Solution ps;
        vector<int> t1{ 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 };
        string s = "abcdefghijklmnopqrstuvwxyz";
        vector<int> ret = ps.numberOfLines(t1,s);
        for (auto& it : ret)
        {
            cout << it <<"\t";
        }
    }
    void hasAlternatingBitsUT(){
        Solution ps;
        bool ret = ps.hasAlternatingBits(8);
        cout << ret << "\t";
    }
    void flipAndInvertImageUT(){
        Solution ps;
        vector<vector<int>> input = { {1, 1, 0},{1, 0, 1},{0, 0, 0} };
        auto res = ps.flipAndInvertImage(input);
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
            auto res = ps.longestCommonPrefix(tmp);
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
            auto res = ps.plusOne(tmp);
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
            auto res = ps.addBinary(tmp[0], tmp[1]);
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
            auto res = ps.mySqrt(tmp);
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
        
        ps.merge(input[0], 1, input[1], 1);
        for (size_t i = 0; i < input.size(); i++)
        {
            cout << input[0][i] << "\t";
        }
        cout << endl;
            
        
    }

    void generateUT(){
        Solution ps;
        auto ret = ps.generate(5);
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
        auto ret = ps.isPalindrome(input);
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
}

#endif //PROBLEM_SET_TESTCASE_H
