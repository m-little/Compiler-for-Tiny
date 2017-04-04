#include <iostream>

#include "AST.h"
#include "GVEmitter.h"

using std::cout;
using std::endl;

GVEmitter::GVEmitter()
:x(0)
{
}

void GVEmitter::visit(Number * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"" << n->num << "\"]\n";
}


void GVEmitter::visit(Plus * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"+\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}


void GVEmitter::visit(Minus * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"-\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}


void GVEmitter::visit(Times * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"*\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}


void GVEmitter::visit(Divide * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"/\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}


void GVEmitter::visit(Id * id)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"" << id->text << "\"]\n";
}


void GVEmitter::visit(LessThan * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"<\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}

void GVEmitter::visit(GreaterThan * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\">\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}

void GVEmitter::visit(EqualTo * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"=\"]\n";

	std::cout << "node" << number << "->";
	n->lhs->accept(this);

	std::cout << "node" << number << "->";
	n->rhs->accept(this);
}

void GVEmitter::visit(If * ifNode)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"if\"]\n";

	std::cout << "node" << number << "->";
	ifNode->test->accept(this);

	std::cout << "node" << number << "->";
	ifNode->ifTrue->accept(this);

	std::cout << "node" << number << "->";
	ifNode->ifFalse->accept(this);

	}

void GVEmitter::visit(While * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"while\"]\n";

	std::cout << "node" << number << "->";
	n->test->accept(this);

	std::cout << "node" << number << "->";
	n->body->accept(this);
}

void GVEmitter::visit(Block * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"block\"]\n";

	std::cout << "node" << number << "->";
	n->first->accept(this);

}

void GVEmitter::visit(SList * n)
{
	int number = x++;

	if(number != 0)
	{
		std::cout << "node" << number << '\n';
	}
	std::cout << "node" << number <<"[label=\";\"]\n";
	
	std::cout << "node" << number << "->";
	n->first->accept(this);

	std::cout << "node" << number << "->";
	n->rest->accept(this);
}
	

void GVEmitter::visit(Assign * a)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\":=\"]\n";

	std::cout << "node" << number << "->";
	a->name->accept(this);

	std::cout << "node" << number << "->";
	a->expr->accept(this);
}

void GVEmitter::visit(Declaration * a)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"var\"]\n";

	std::cout << "node" << number << "->";
	a->name->accept(this);

	std::cout << "node" << number << "->";
	a->expr->accept(this);


}

void GVEmitter::visit(Read * r)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"read\"]\n";

	std::cout << "node" << number << "->";
	r->name->accept(this);

	
}

void GVEmitter::visit(Write * w)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"write\"]\n";

	std::cout << "node" << number << "->";
	w->name->accept(this);

}

void GVEmitter::visit(Pass * w)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"pass\"]\n";
}

void GVEmitter::visit(Proc * p)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"proc\"]\n";

	std::cout << "node" << number << "->";
	p->name->accept(this);
  
	if (p->alist != NULL) {
	  std::cout << "node" << number << "->";
	  p->alist->accept(this);
	}

	std::cout << "node" << number << "->";
	p->body->accept(this);
}

void GVEmitter::visit(Call * c)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number << "[label=\"Call\"]\n";

	std::cout << "node" << number << "->";
	c->name->accept(this);

	if (c->alist != NULL) {
	  std::cout << "node" << number << "->";
	  c->alist->accept(this);
	}
}

void GVEmitter::visit(Alist * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number <<"[label=\",\"]\n";
	
	std::cout << "node" << number << "->";
	n->first->accept(this);

	std::cout << "node" << number << "->";
	n->rest->accept(this);
}

void GVEmitter::visit(Plist * n)
{
	int number = x++;
	std::cout << "node" << number << '\n';
	std::cout << "node" << number <<"[label=\",\"]\n";
	
	std::cout << "node" << number << "->";
	n->first->accept(this);

	std::cout << "node" << number << "->";
	n->rest->accept(this);
}
