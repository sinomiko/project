//
// Created by mikoxmsong on 2021/12/13.
//


#include <iostream>
#include <string>
#include<vector>
struct BeautifulSequence {
public:
    BeautifulSequence() {
        n = 0;
        ret = false;
    }
    int n;
    std::vector<int> seq;
    bool ret;
    void judge_beautiful_seq() {
        int diff = 0;
        int zero = 0;
        for (auto& i : seq) {
            if (i > 0) {
                diff++;
            } else if(i < 0) {
                diff--;
            } else {
                zero++;
            }
        }
        if (diff < 2) {
            ret = true;
        } else {
            if (abs(zero - abs(diff)) < 2) {
                ret = true;
            } else {
                ret = false;
            }
        }
    }

};
#include<stdio.h>
int TestWinRatio(){
    int T, i, L, j, current_num;
    scanf("%d", &T);
    for(i=1; i<=T; i++){
        scanf("%d", &L);
        int positive_num = 0, negative_num = 0, zero_num = 0;
        for(j=1; j<=L; j++){
            scanf("%d", &current_num);
            if(current_num > 0){
                positive_num++;
            }
            else if(current_num < 0){
                negative_num++;
            }
            else{
                zero_num++;
            }
        }
        if(abs(negative_num - positive_num) > 1 + zero_num)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
void get_input_and_run(){
    int row, col;
    std::string str;
    std::vector<BeautifulSequence> resSeqs;

    while(row --){
        col = 0;
        std::cin >> col;
        if (col <= 0) {
            BeautifulSequence beq;
            beq.ret = true;
            std::cin.ignore();
            getline(std::cin, str);
            resSeqs.push_back(beq);
        } else {
            std::cin.ignore();
            getline(std::cin, str);
            BeautifulSequence beq;

            for (int idx = 0; idx < str.length();) {
                int num = 0;
                int sign = 1;
                while (str[idx] != ' ' && idx < str.length()) {
                    if (str[idx] == '-') {
                        sign = -1;
                    }
                    if(str[idx] >= '0' && str[idx] <= '9') {
                        num = 10*num + (str[idx] - '0');
                        //                    std::cout << __LINE__ << " " << num << std::endl;
                    }
                    idx++;
                }
                idx++;
                //                std::cout << __LINE__ << " " << str[idx] << std::endl;
                //                std::cout << __LINE__ << " " << sign * num << std::endl;
                beq.seq.push_back(sign * num);
            }
            beq.judge_beautiful_seq();
            resSeqs.push_back(beq);
        }
    }
    for (int i = 0; i < resSeqs.size(); ++i) {
        if (resSeqs[i].ret) {
            std::cout << "Yes";
        } else {
            std::cout << "No";
        }
        if (i != resSeqs.size() - 1) {
            std::cout << std::endl;
        }
    }

}
#include<stdio.h>
#include<vector>
int cal_tencent_win_probability() {
    int repeat = 0;
    scanf("%d", &repeat);
    while (repeat--) {
        int team_num, prize_num;
        scanf("%d", &team_num);
        std::vector<int> team_pass, team_hold;
        team_pass.reserve(team_num);
        team_hold.reserve(team_num);
        scanf("%d", &prize_num);
        for(int i=0; i < team_num; i++) {
            int pass = 0;
            scanf("%d", &pass);
            team_pass.push_back(pass);
        }
        for (int i = 0; i < team_num; ++i) {
            int hold = 0;
            scanf("%d", &hold);
            team_hold.push_back(hold);
        }
        int tencent_score_expect = team_pass[0] + team_hold[0];
        int rank = 1;
        for (int i = 1; i < team_num; ++i) {
            if (team_pass[i] > tencent_score_expect) {
                rank++;
            }
        }
        if (rank > prize_num) {
            printf("No\n");
        } else {
            printf("Yes\n");
        }
    }

    return 0;
}
