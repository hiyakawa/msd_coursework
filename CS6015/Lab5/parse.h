/**
 * \file parse.h
 * \brief Declarations of methods to parse input string
 * \author Laura Zhang
 */

#pragma once

#include "expr.h"

Expr* parse(std::istream &in);
Expr* parse_str(const std::string& s);
static Expr* parse_expr(std::istream &in);
static Expr* parse_addend(std::istream &in);
static Expr* parse_multicand(std::istream &in);
static Expr* parse_inner(std::istream &in);
static NumExpr* parse_num(std::istream &in);
static VarExpr* parse_var(std::istream &in);
static LetExpr* parse_let(std::istream &in);
static std::string parse_keyword(std::istream &in);
static void skip_whitespace(std::istream &in);
static void consume(std::istream &in, int expect);
