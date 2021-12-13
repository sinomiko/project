//
// Created by mikoxmsong on 2021/9/9.
//

#ifndef DEMO_PROTO_TYPE_H
#define DEMO_PROTO_TYPE_H
#include <string>
#include <memory>
#include <vector>

#include "parser.h"

// 函数接口
class PrototypeAST {
public:
    PrototypeAST(const std::string& name, std::vector<std::string> args)
    : name_(name), args_(std::move(args)) {}

    const std::string& name() const { return name_; }

private:
    std::string name_;
    std::vector<std::string> args_;
};

// 函数
class FunctionAST {
public:
    FunctionAST(std::unique_ptr<PrototypeAST> proto,
                std::unique_ptr<ExprAST> body)
            : proto_(std::move(proto)), body_(std::move(body)) {}

private:
    std::unique_ptr<PrototypeAST> proto_;
    std::unique_ptr<ExprAST> body_;
};
#endif //DEMO_PROTO_TYPE_H
