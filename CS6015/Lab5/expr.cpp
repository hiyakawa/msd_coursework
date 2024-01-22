/**
 * \file expr.cpp
 * \brief Definitions of methods in Expr and its child classes
 * \author Laura Zhang
 */

#include "expr.h"
#include <stdexcept>
#include <sstream>

/*
 * Expr
 */

/**
 * \brief convert stringstream to string
 * \return string version of stringstream
 */
std::string Expr::to_string() {
    std::stringstream st;
    print(st);

    return st.str();
}

/**
 * \brief driver function of pretty_print_at()
 * \param ot ostream
 */
void Expr::pretty_print(std::ostream &ot) {
    std::streampos begin_pos = ot.tellp();
    pretty_print_at(ot, prec_none, false, false, begin_pos);
}

/**
 * \brief for testing
 * \return string version of stringstream
 */
std::string Expr::pretty_print_to_string() {
    std::stringstream st;
    pretty_print(st);

    return st.str();
}

/*
 * NumExpr
 */
NumExpr::NumExpr(int val) {
    val_ = val;
}

/**
 * \brief check if two NumExprs are equal
 * \param e rhs Expr* to be compared
 * \return true if two NumExprs are equal, false if rhs is NULL
 */
bool NumExpr::equals(Expr *e) {
    NumExpr *n = dynamic_cast<NumExpr *>(e);
    
    if (n == nullptr) {
        return false;
    }
    
    return val_ == n->val_;
}

/**
 * \brief returns an int for the value of an expression
 * \return the value of a NumExpr
 */
int NumExpr::interp() {
    return val_;
}

/**
 * \brief returns true if the expression is a variable or contains a variable
 * \return false
 */
bool NumExpr::has_variable() {
    return false;
}

/**
 * \brief everywhere that the expression contains a variable matching the
 * string, the result Expr* should have the given replacement
 * \param parameter the parameter to be substituted
 * \param expr a new expression
 * \return a new object without changing the current object
 */
Expr* NumExpr::subst(std::string parameter, Expr* expr) {
    return new NumExpr(val_);
}

/**
 * \brief print the Expr
 * \param ot ostream
 */
void NumExpr::print(std::ostream &ot) {
    ot << std::to_string(val_);
}

/**
 * \brief print the Expr in a pretty format
 * \param ot ostream
 * \param p precedence of the previous Expr
 * \param left if the current Expr is on the left hand side of the previous Expr
 * \param parenthesized if the previous Expr is parenthesized
 * \param pos the number of characters that have been written to the stream
 */
void NumExpr::pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos) {
    ot << val_;
}

/*
 * AddExpr
 */
AddExpr::AddExpr(Expr *lhs, Expr *rhs) {
    lhs_ = lhs;
    rhs_ = rhs;
}

/**
 * \brief check if two AddExprs are equal
 * \param e rhs Expr* to be compared
 * \return true if two AddExprs are equal, false if rhs is NULL
 */
bool AddExpr::equals(Expr *e) {
    AddExpr *a = dynamic_cast<AddExpr *>(e);
    
    if (a == nullptr) {
        return false;
    }
    
    return lhs_->equals(a->lhs_) && rhs_->equals(a->rhs_);
}

/**
 * \brief returns an int for the value of an expression
 * \return the sum of the subexpression values
 */
int AddExpr::interp() {
    return lhs_->interp() + rhs_->interp();
}

/**
 * \brief returns true if the expression is a variable or contains a variable
 * \return true if either lhs or rhs is a variable or contains a variable
 */
bool AddExpr::has_variable() {
    return lhs_->has_variable() || rhs_->has_variable();
}

/**
 * \brief everywhere that the expression contains a variable matching the
 * string, the result Expr* should have the given replacement
 * \param parameter the parameter to be substituted
 * \param expr a new expression
 * \return a new object without changing the current object
 */
Expr* AddExpr::subst(std::string parameter, Expr* expr) {
    return new AddExpr(lhs_->subst(parameter, expr),
                       rhs_->subst(parameter, expr));
}

/**
 * \brief print the Expr
 * \param ot ostream
 */
void AddExpr::print(std::ostream &ot) {
    ot << "(";
    lhs_->print(ot);
    ot << "+";
    rhs_->print(ot);
    ot << ")";
}

/**
 * \brief print the Expr in a pretty format
 * \param ot ostream
 * \param p precedence of the previous Expr
 * \param left if the current Expr is on the left hand side of the previous Expr
 * \param parenthesized if the previous Expr is parenthesized
 * \param pos the number of characters that have been written to the stream
 */
void AddExpr::pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos) {
    if (p == prec_mult || (p == prec_add && left)) {
        ot << "(";
    }

    lhs_->pretty_print_at(ot, prec_add, true, true, pos);
    ot << " + ";
    rhs_->pretty_print_at(ot, prec_add, false, false, pos);

    if (p == prec_mult || (p == prec_add && left)) {
        ot << ")";
    }
}

/*
 * MultExpr
 */
MultExpr::MultExpr(Expr *lhs, Expr *rhs) {
    lhs_ = lhs;
    rhs_ = rhs;
}

/**
 * \brief check if two MultExprs are equal
 * \param e rhs Expr* to be compared
 * \return true if two MultExprs are equal, false if rhs is NULL
 */
bool MultExpr::equals(Expr *e) {
    MultExpr *m = dynamic_cast<MultExpr *>(e);
    
    if (m == nullptr) {
        return false;
    }
    
    return lhs_->equals(m->lhs_) && rhs_->equals(m->rhs_);
}

/**
 * \brief returns an int for the value of an expression
 * \return the product of the subexpression values
 */
int MultExpr::interp() {
    return lhs_->interp() * rhs_->interp();
}

/**
 * \brief returns true if the expression is a variable or contains a variable
 * \return true if either lhs or rhs is a variable or contains a variable
 */
bool MultExpr::has_variable() {
    return lhs_->has_variable() || rhs_->has_variable();
}

/**
 * \brief everywhere that the expression contains a variable matching the
 * string, the result Expr* should have the given replacement
 * \param parameter the parameter to be substituted
 * \param expr a new expression
 * \return a new object without changing the current object
 */
Expr* MultExpr::subst(std::string parameter, Expr* expr) {
    return new MultExpr(lhs_->subst(parameter, expr),
                        rhs_->subst(parameter, expr));
}

/**
 * \brief print the Expr
 * \param ot ostream
 */
void MultExpr::print(std::ostream &ot) {
    ot << "(";
    lhs_->print(ot);
    ot << "*";
    rhs_->print(ot);
    ot << ")";
}

/**
 * \brief print the Expr in a pretty format
 * \param ot ostream
 * \param p precedence of the previous Expr
 * \param left if the current Expr is on the left hand side of the previous Expr
 * \param parenthesized if the previous Expr is parenthesized
 * \param pos the number of characters that have been written to the stream
 */
void MultExpr::pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos) {
    if (p == prec_mult && left) {
        ot << "(";
    }

    lhs_->pretty_print_at(ot, prec_mult, true, false, pos);
    ot << " * ";
    rhs_->pretty_print_at(ot, prec_mult, false, parenthesized, pos);

    if (p == prec_mult && left) {
        ot << ")";
    }
}

/*
 * VarExpr
 */
VarExpr::VarExpr(std::string var) {
    var_ = var;
}

/**
 * \brief check if two VarExprs are equal
 * \param e rhs Expr* to be compared
 * \return true if two VarExprs are equal, false if rhs is NULL
 */
bool VarExpr::equals(Expr *e) {
    VarExpr *v = dynamic_cast<VarExpr *>(e);
    
    if (v == nullptr) {
        return false;
    }
    
    return var_ == v->var_;
}

/**
 * \brief returns an int for the value of an expression
 * \return throw an std::runtime_error exception
 */
int VarExpr::interp() {
    throw std::runtime_error("no value for variable");
}

/**
 * \brief returns true if the expression is a variable or contains a variable
 * \return true
 */
bool VarExpr::has_variable() {
    return true;
}

/**
 * \brief everywhere that the expression contains a variable matching the
 * string, the result Expr* should have the given replacement
 * \param parameter the parameter to be substituted
 * \param expr a new expression
 * \return a new object without changing the current object
 */
Expr* VarExpr::subst(std::string parameter, Expr* expr) {
    if (parameter == var_) {
        return expr;
    }

    return new VarExpr(parameter);
}

/**
 * \brief print the Expr
 * \param ot ostream
 */
void VarExpr::print(std::ostream &ot) {
    ot << var_;
}

/**
 * \brief print the Expr in a pretty format
 * \param ot ostream
 * \param p precedence of the previous Expr
 * \param left if the current Expr is on the left hand side of the previous Expr
 * \param parenthesized if the previous Expr is parenthesized
 * \param pos the number of characters that have been written to the stream
 */
void VarExpr::pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos) {
    ot << var_;
}

/*
 * LetExpr
 */
LetExpr::LetExpr(std::string var, Expr* rhs, Expr* body) {
    var_ = var;
    rhs_ = rhs;
    body_ = body;
}

/**
 * \brief check if two LetExprs are equal
 * \param e rhs Expr* to be compared
 * \return true if two LetExprs are equal, false if rhs is NULL
 */
bool LetExpr::equals(Expr *e) {
    LetExpr *l = dynamic_cast<LetExpr *>(e);

    if (l == nullptr) {
        return false;
    }

    return (var_ == l->var_) &&
           (body_->equals(l->body_)) &&
           (rhs_->equals(l->rhs_));
}

/**
 * \brief returns an int for the value of an expression
 * \return the substitute interp of body_
 */
int LetExpr::interp() {
    return body_->subst(var_, new NumExpr(rhs_->interp()))->interp();
}

/**
 * \brief returns true if the expression is a variable or contains a variable
 * \return true if either lhs or rhs is a variable or contains a variable
 */
bool LetExpr::has_variable() {
    return (body_->has_variable()) ||
           (rhs_->has_variable());
}

/**
 * \brief everywhere that the expression contains a variable matching the
 * string, the result Expr* should have the given replacement
 * \param parameter the parameter to be substituted
 * \param expr a new expression
 * \return a new object without changing the current object
 */
Expr* LetExpr::subst(std::string parameter, Expr *expr) {
    if (parameter == var_) {
        return new LetExpr(var_, rhs_->subst(parameter, expr), body_);
    }

    return new LetExpr(var_, rhs_->subst(parameter, expr), body_->subst(parameter, expr));
}

/**
 * \brief print the Expr
 * \param ot ostream
 */
void LetExpr::print(std::ostream &ot) {
    ot << "(_let " << var_ << "=";
    rhs_->print(ot);
    ot << " _in ";
    body_->print(ot);
    ot << ")";
}

/**
 * \brief print the Expr in a pretty format
 * \param ot ostream
 * \param p precedence of the previous Expr
 * \param left if the current Expr is on the left hand side of the previous Expr
 * \param parenthesized if the previous Expr is parenthesized
 * \param pos the number of characters that have been written to the stream
 */
void LetExpr::pretty_print_at(std::ostream &ot, precedence_t p, bool left, bool parenthesized, std::streampos& pos) {
    if ((parenthesized && (! left)) || left) {
        ot << "(";
    }

    int indent = ot.tellp() - pos;

    ot << "_let " << var_ << " = ";
    rhs_->pretty_print_at(ot, prec_none, false, false, pos);
    ot << "\n";
    pos = ot.tellp();

    // print spaces in the front of a new line
    ot << std::string(indent, ' ');

    ot << "_in ";
    body_->pretty_print_at(ot, prec_none, false, false, pos);

    if ((parenthesized && (! left)) || left) {
        ot << ")";
    }
}
