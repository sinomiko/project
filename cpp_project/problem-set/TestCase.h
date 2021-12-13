//
// Created by mikoxmsong on 2021/12/13.
//

#ifndef PROBLEM_SET_TESTCASE_H
#define PROBLEM_SET_TESTCASE_H
#include "Solution.h"

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

    void longestConsecutiveUT(){
        Solution ps;
        vector<int> test{ 9,1,-3,2,4,8,3,-1,6,-2,-4,7 };
        int ret = ps.longestConsecutive(test);
        cout << ret << endl;
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
