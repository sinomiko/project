//
// Created by mikoxmsong on 2021/9/9.
//
#ifndef DEMO_LEX_H
#define DEMO_LEX_H

#include <string>

// 如果不是以下5种情况，Lexer返回[0-255]的ASCII值，否则返回以下枚举值
enum Token {
    TOKEN_EOF = -1,         // 文件结束标识符
    TOKEN_DEF = -2,         // 关键字def
    TOKEN_EXTERN = -3,      // 关键字extern
    TOKEN_IDENTIFIER = -4,  // 名字
    TOKEN_NUMBER = -5       // 数值
};

std::string g_identifier_str;  // Filled in if TOKEN_IDENTIFIER
double g_number_val;           // Filled in if TOKEN_NUMBER

// 从标准输入解析一个Token并返回
int GetToken() {
    static int last_char = ' ';
    // 忽略空白字符
    while (isspace(last_char)) {
        last_char = getchar();
    }
    // 识别字符串
    if (isalpha(last_char)) {
        g_identifier_str = last_char;
        while (isalnum((last_char = getchar()))) {
            g_identifier_str += last_char;
        }
        if (g_identifier_str == "def") {
            return TOKEN_DEF;
        } else if (g_identifier_str == "extern") {
            return TOKEN_EXTERN;
        } else {
            return TOKEN_IDENTIFIER;
        }
    }
    // 识别数值
    if (isdigit(last_char) || last_char == '.') {
        std::string num_str;
        do {
            num_str += last_char;
            last_char = getchar();
        } while (isdigit(last_char) || last_char == '.');
        g_number_val = strtod(num_str.c_str(), nullptr);
        return TOKEN_NUMBER;
    }
    // 忽略注释
    if (last_char == '#') {
        do {
            last_char = getchar();
        } while (last_char != EOF && last_char != '\n'  && last_char != '\r');
        if (last_char != EOF) {
            return GetToken();
        }
    }
    // 识别文件结束
    if (last_char == EOF) {
        return TOKEN_EOF;
    }
    // 直接返回ASCII
    int this_char = last_char;
    last_char = getchar();
    return this_char;
}
#endif //DEMO_LEX_H
