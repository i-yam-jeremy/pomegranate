#pragma once


#include "antlr4-runtime.h"
#include "LsystemVisitor.h"


namespace lsystem {

class  LsystemExecutorVisitor : public LsystemVisitor {
public:

  virtual antlrcpp::Any visitLsystem(LsystemParser::LsystemContext *ctx) override {
    return ctx->INT()->toString();
  }


};

}  // namespace lsystem
