#ifndef ILOCEMITTER_H
#define ILOCEMITTER_H

#include <string>
#include <list>
#include <map>
#include <stack>

#include "AST.h"


struct ILOCEmitter : public ASTVisitor
{
    ILOCEmitter();
    virtual void visit(Number *);
    virtual void visit(Plus *);
    virtual void visit(Minus *);
    virtual void visit(Times *);
    virtual void visit(Divide *);
    virtual void visit(Id *);
    virtual void visit(LessThan *);
    virtual void visit(GreaterThan *);
    virtual void visit(EqualTo *);
    virtual void visit(If *);
    virtual void visit(While *);
    virtual void visit(Block *);
    virtual void visit(SList *);
    virtual void visit(Assign *);
    virtual void visit(Declaration *);
    virtual void visit(Read *);
    virtual void visit(Write *);
    virtual void visit(Pass *);
    virtual void visit(Alist *);
    virtual void visit(Plist *);
    virtual void visit(Call *);
    virtual void visit(Proc *);



std::stack < std::list < std::map < std::string, int > > > sym_table;

int temp;
int expr_temp;
int label_temp;
int offset_temp;
};


#endif
