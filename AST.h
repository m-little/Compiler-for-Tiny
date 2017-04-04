#ifndef AST_H
#define AST_H

#include <string>

// Forward declaration of the visitor class
struct ASTVisitor;

// AST is the base class for all AST node types.  It is an "abstract base
// class," meaning that each kind of AST node has its own type, and you
// can't directly instantiate an AST.
struct AST
{
    // All AST nodes must be able to accept a visitor.
    virtual void accept(ASTVisitor *) = 0;
};


// Integer literals
struct Number : public AST
{
    Number(int n) : num(n) { }
    virtual void accept(ASTVisitor *);
    int num;
};


struct Plus : public AST
{
    Plus(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct Minus : public AST
{
    Minus(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct Times : public AST
{
    Times(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct Divide : public AST
{
    Divide(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct Id : public AST
{
    Id(char const * str) : text(str) { }
    virtual void accept(ASTVisitor *);
    std::string text;
};


struct LessThan : public AST
{
    LessThan(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct GreaterThan : public AST
{
    GreaterThan(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct EqualTo : public AST
{
    EqualTo(AST * l, AST * r) : lhs(l), rhs(r) { }
    virtual void accept(ASTVisitor *);
    AST *lhs, *rhs;
};


struct If : public AST
{
    If(AST * c, AST * t, AST * f) : test(c), ifTrue(t), ifFalse(f) { }
    virtual void accept(ASTVisitor *);
    AST *test, *ifTrue, *ifFalse;
};


struct While : public AST
{
    While(AST * c, AST * b) : test(c), body(b) { }
    virtual void accept(ASTVisitor *);
    AST *test, *body;
};


// Statement List (aka "sequence"): one statement followed by one or more
// additional statements
struct SList : public AST
{
    SList(AST * f, AST * r) : first(f), rest(r) { }
    virtual void accept(ASTVisitor *);
    AST *first, *rest;
};


// Blocks control variable scoping, the "first" pointer points to the first
// code inside the block, which could be a statement like an If node, another
// Block, or (most likely) as SList (multiple statements)
//
// Note that we haven't implemented the scoping behavior yet; that won't be
// built into the Block type, but into a visitor that processes Blocks
struct Block : public AST
{
    Block(AST * f) : first(f) { }
    virtual void accept(ASTVisitor *);
    AST *first;
};


struct Assign : public AST
{
    Assign(Id * id, AST * e) : name(id), expr(e) { }
    virtual void accept(ASTVisitor *);
    Id * name;
    AST * expr;
};


// In the TINY language, variables are declared with the "var" keyword and
// are always immediately initialized
struct Declaration : public AST
{
    Declaration(Id * id, AST * e) : name(id), expr(e) { }
    virtual void accept(ASTVisitor *);
    Id * name;
    AST * expr;
};


struct Read : public AST
{
    Read(Id * id) : name(id) { }
    virtual void accept(ASTVisitor *);
    Id * name;
};


struct Write : public AST
{
    Write(Id * id) : name(id) { }
    virtual void accept(ASTVisitor *);
    Id * name;
};


// Pass is a do-nothing statement that usually serves as a placeholder
struct Pass : public AST
{
    Pass() { }
    virtual void accept(ASTVisitor *);
};

//part trois
struct Proc : public AST
{
    Proc(Id * id, AST * b, AST * a) : name(id), body(b), alist(a){}
    Proc(Id * id, AST * b) : name(id), body(b), alist(NULL){}
    Id * name;
    AST * body;
    AST * alist;

    virtual void accept(ASTVisitor *);

};
struct Call : public AST
{
    Call(Id * id,AST * a) : name(id), alist(a){}
    Call(Id * id) : name(id), alist(NULL){}
    Id * name;
    AST * alist;

    virtual void accept(ASTVisitor *);
};

struct Alist : public AST
{
    Alist(AST * f, AST * r) : first(f), rest(r) { }
    virtual void accept(ASTVisitor *);
    AST *first, *rest;
};

struct Plist : public AST
{
    Plist(AST * f, AST * r) : first(f), rest(r) { }
    virtual void accept(ASTVisitor *);
    AST *first, *rest;
};


struct ASTVisitor
{
    virtual void visit(Number *) = 0;
    virtual void visit(Plus *) = 0;
    virtual void visit(Minus *) = 0;
    virtual void visit(Times *) = 0;
    virtual void visit(Divide *) = 0;
    virtual void visit(Id *) = 0;
    virtual void visit(LessThan *) = 0;
    virtual void visit(GreaterThan *) = 0;
    virtual void visit(EqualTo *) = 0;
    virtual void visit(If *) = 0;
    virtual void visit(While *) = 0;
    virtual void visit(Block *) = 0;
    virtual void visit(SList *) = 0;
    virtual void visit(Assign *) = 0;
    virtual void visit(Declaration *) = 0;
    virtual void visit(Read *) = 0;
    virtual void visit(Write *) = 0;
    virtual void visit(Pass *) = 0;
    virtual void visit(Proc *) = 0;
    virtual void visit(Call *) = 0;
    virtual void visit(Alist *) = 0;
    virtual void visit(Plist *) = 0;

};

#endif
