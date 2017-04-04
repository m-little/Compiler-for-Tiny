#include <iostream>

#include "AST.h"
#include "ILOCEmitter.h"

using namespace std;


ILOCEmitter::ILOCEmitter()
:temp(0), label_temp(0)
{
	std::map < std::string, int > new_map;
	std::list < std::map < std::string, int > > new_list;
	new_list.push_back(new_map);
	sym_table.push(new_list);

	//std::cout << sym_table.size() << '\n';
}

void ILOCEmitter::visit(Number * n)
{
	std::cout << "loadI " << n->num << " -> r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;

}

void ILOCEmitter::visit(Plus * p)
{
	p->lhs->accept(this);
	int x = expr_temp;
	p->rhs->accept(this);
	std::cout << "add r" << x;
	std::cout << ", r" << expr_temp << " -> r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(Minus * m)
{
	m->lhs->accept(this);
	int x = expr_temp;
	m->rhs->accept(this);
	std::cout << "sub r" << x;
	std::cout << ", r" << expr_temp << " -> r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(Times * t)
{
	t->lhs->accept(this);
	int x = expr_temp;
	t->rhs->accept(this);
	std::cout << "mult r" << x;
	std::cout << ", r" << expr_temp << " ->r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(Divide * d)
{
	d->lhs->accept(this);
	int x = expr_temp;
	d->rhs->accept(this);
	std::cout << "div r" << x;
	std::cout << ", r" << expr_temp << " ->r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(LessThan * d)
{
	d->lhs->accept(this);
	int x = expr_temp;
	d->rhs->accept(this);
	std::cout << "comp_LT r" << x;
	std::cout << ", r" << expr_temp << " ->r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(GreaterThan * d)
{
	d->lhs->accept(this);
	int x = expr_temp;
	d->rhs->accept(this);
	std::cout << "comp_RT r" << x;
	std::cout << ", r" << expr_temp << " ->r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(EqualTo * d)
{
	d->lhs->accept(this);
	int x = expr_temp;
	d->rhs->accept(this);
	std::cout << "comp_EQ r" << x;
	std::cout << ", r" << expr_temp << " ->r" << temp;
	std::cout << std::endl;
	expr_temp = temp++;
}

void ILOCEmitter::visit(Id * i)
{
	std::list < std::map < std::string, int > >::reverse_iterator iter;
	int x = -1;
	
	std::list < std:: map < std::string, int > > *temp_table = &sym_table.top();

	for(iter = temp_table->rbegin(); iter != temp_table->rend(); iter++)
	{
		
		if(iter->find(i->text) != iter->end())
		{
			x = (*iter)[i->text];
			break;
		}
	}
	if(x == -1)
	{
		temp_table = &sym_table.top();
		temp_table -> back()[i->text]= temp;
		x = temp++;
	}
	expr_temp = x;
}

void ILOCEmitter::visit(If * f)
{
	int x = label_temp++;
	int y = label_temp++;
	int z = label_temp++;

	f->test->accept(this);
	std::cout << "cbr r" << expr_temp << " ->" << "label" << x << ", label" << y;
	std::cout << std::endl;
	std::cout << "label" << x << ": nop\n";
	
	f->ifTrue->accept(this);
	std::cout << "jumpI label" << z << std::endl;
	std::cout << "label" << y << ": nop\n";

	f->ifFalse->accept(this);
	std::cout << "label" << z << ": nop\n";

}

void ILOCEmitter::visit(While * w)
{
	int x = label_temp++;
	int y = label_temp++;
	int z = label_temp++;
	std::cout << "label" << x << ": nop\n";
	
	w->test->accept(this);
	std::cout << "cbr r" << expr_temp << " ->" << "label" << y << ", label" << z;
	std::cout << std::endl;
	std::cout << "label" << y << ": nop\n";
	w->body->accept(this);
	std::cout << "jumpI label" << x << std::endl;
	std::cout << "label" << z << ": nop\n";


}

void ILOCEmitter::visit(Block * b)
{
	b->first->accept(this);
}

void ILOCEmitter::visit(SList * s)
{
	s->first->accept(this);
	s->rest->accept(this);
}

void ILOCEmitter::visit(Declaration * d)
{
	d->expr->accept(this);
	std::list < std:: map < std::string, int > > *temp_table = &sym_table.top();
	std::cout << "i2i r" << expr_temp;
	std::cout << " -> r" << temp << '\n';
	temp_table->back()[d->name->text] = temp++;
}

void ILOCEmitter::visit(Assign * a)
{
	a->expr->accept(this);
	std::cout << "i2i r" << expr_temp;
	a->name->accept(this);
	std::cout << " -> r" << expr_temp << '\n';
}

void ILOCEmitter::visit(Read * r)
{
	
	r->name->accept(this);
	std::cout << "read r" << expr_temp;
	std::cout << std::endl;
}

void ILOCEmitter::visit(Write * w)
{
	w->name->accept(this);
	std::cout << "write r" << expr_temp;
	std::cout << std::endl;
}

void ILOCEmitter::visit(Pass *)
{
}


//part quatre
void ILOCEmitter::visit(Proc * p)
{
	std::cout << p->name->text << ": nop\n";

	//prolog code
	std::map < std::string, int > new_map;
	std::list < std::map < std::string, int > > new_list;
	new_list.push_back(new_map);
	sym_table.push(new_list);	

	if(p->alist != NULL)
	{
		p->alist->accept(this);
		if(expr_temp != -1)
		{
			std::cout << "loadAI SP, " << -2 << "  ->r" << expr_temp << '\n';
		}	
	}

	p->body->accept(this);
	sym_table.pop();

	
	//epilog code
	std::cout << "loadAI SP, -1 -> r" << temp << '\n';
	std::cout << "jump r" << temp++ << '\n';

}


//part quatre
void ILOCEmitter::visit(Alist * n)
{
	n->first->accept(this);
	offset_temp = -2;
	std::cout << "loadAI SP, " << offset_temp-- << "-> r" << expr_temp << '\n';

	if (n->rest != NULL)
	{
		n->rest->accept(this);
		if(expr_temp != -1)
		{
			std::cout << "loadAI SP, " << offset_temp-- << "-> r" << expr_temp << '\n';
		}
	}
	expr_temp= -1;
}

void ILOCEmitter::visit(Plist * n)
{
	
	if (n->rest != NULL)
	{
		n->rest->accept(this);
		if(expr_temp != -1)
		{
			std::cout << "storeAI r" << expr_temp << "-> SP" << offset_temp++ << '\n';
		}
	}
	
	n->first->accept(this);
	offset_temp = -2;
	std::cout << "storeAI r" << expr_temp << "-> SP" << offset_temp++ << '\n';
	
	expr_temp= -1;
}


void ILOCEmitter::visit(Call * c)
{
	// pre-call
	offset_temp = 0;
	
	// store values of variables
	list<map< string, int > >::iterator iter1;
	map< string, int >::iterator iter2;
	list<map< string, int > > * table1 = &sym_table.top();
	for(iter1 = table1->begin(); iter1 != table1->end(); iter1++) {
		for (iter2 = iter1->begin(); iter2 != iter1->end(); iter2++) {
			std::cout << "storeAI r" << iter2->second << " -> SP, " << offset_temp++ << '\n';
		}
		
	}

	// evaluate alist and place on stack
	c->alist->accept(this);
	if (expr_temp != -1)
		std::cout << "storeAI r" << expr_temp << " -> SP, " << offset_temp++ << '\n';
	
	expr_temp = -1;

	// place return address on stack
	int label = label_temp++;
	std::cout << "loadI L" << label << " -> r" << temp << '\n';
	std::cout << "storeAI r" << temp++ << " -> SP, " << offset_temp++ << '\n';

	// update stack pointer
	std::cout << "addI SP, " << offset_temp << " -> SP\n";

	std::cout << "jumpI " << c->name->text << '\n';

	// post-call
	std::cout << "L" << label << ": nop\n";

	std::cout <<  "subI SP, " << offset_temp << " -> SP\n";

	// restore variable values
	offset_temp = 0;
	for(iter1 = table1->begin(); iter1 != table1->end(); iter1++) {
		for (iter2 = iter1->begin(); iter2 != iter1->end(); iter2++) {
			std::cout << "loadAI SP, " << offset_temp++ << " -> r" << iter2->second << '\n';
		}
		
	}
}