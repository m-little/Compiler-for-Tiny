#include "AST.h"


void Number::accept(ASTVisitor * v) { v->visit(this); }
void Plus::accept(ASTVisitor * v) { v->visit(this); }
void Minus::accept(ASTVisitor * v) { v->visit(this); }
void Times::accept(ASTVisitor * v) { v->visit(this); }
void Divide::accept(ASTVisitor * v) { v->visit(this); }
void LessThan::accept(ASTVisitor * v) { v->visit(this); }
void GreaterThan::accept(ASTVisitor * v) { v->visit(this); }
void EqualTo::accept(ASTVisitor * v) { v->visit(this); }
void If::accept(ASTVisitor * v) { v->visit(this); }
void While::accept(ASTVisitor * v) { v->visit(this); }
void Block::accept(ASTVisitor * v) { v->visit(this); }
void SList::accept(ASTVisitor * v) { v->visit(this); }
void Assign::accept(ASTVisitor * v) { v->visit(this); }
void Declaration::accept(ASTVisitor * v) { v->visit(this); }
void Read::accept(ASTVisitor * v) { v->visit(this); }
void Write::accept(ASTVisitor * v) { v->visit(this); }
void Id::accept(ASTVisitor * v) { v->visit(this); }
void Pass::accept(ASTVisitor * v) { v->visit(this); }

//part trois
void Proc::accept(ASTVisitor * v) { v->visit(this); }
void Call::accept(ASTVisitor * v) { v->visit(this); }
void Alist::accept(ASTVisitor * v) { v->visit(this); }
void Plist::accept(ASTVisitor * v) { v->visit(this); }
