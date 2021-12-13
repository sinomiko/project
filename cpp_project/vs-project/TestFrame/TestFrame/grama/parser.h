//
// Created by mikoxmsong on 2021/9/9.
//

#ifndef DEMO_PARSER_H
#define DEMO_PARSER_H
#include <string>
#include <vector>

// 所有 `表达式` 节点的基类
class ExprAST {
public:
    virtual ~ExprAST() {}
};

// 字面值表达式
class NumberExprAST : public ExprAST {
public:
    NumberExprAST(double val) : val_(val) {}

private:
    double val_;
};

// 变量表达式
class VariableExprAST : public ExprAST {
public:
    VariableExprAST(const std::string& name) : name_(name) {}

private:
    std::string name_;
};

// 二元操作表达式
class BinaryExprAST : public ExprAST {
public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs,
                  std::unique_ptr<ExprAST> rhs)
            : op_(op), lhs_(std::move(lhs)), rhs_(std::move(rhs)) {}

private:
    char op_;
    std::unique_ptr<ExprAST> lhs_;
    std::unique_ptr<ExprAST> rhs_;
};

// 函数调用表达式
class CallExprAST : public ExprAST {
public:
    CallExprAST(const std::string& callee,
    std::vector<std::unique_ptr<ExprAST>> args)
    : callee_(callee), args_(std::move(args)) {}

private:
    std::string callee_;
    std::vector<std::unique_ptr<ExprAST>> args_;
};
#endif //DEMO_PARSER_H
