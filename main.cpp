#include <iostream>
#include <string>
#include "AST.h"
#include "GVEmitter.h"
#include "ILOCEmitter.h"

int yyparse(AST ** rootpointer);

int main(int argc, char const * argv[])
{
    AST * root;
    int error = yyparse(&root);

    if (error) return error;

    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " [-gv OR -iloc] < \"infile\" > \"outfile\"\n";
    }
    else {
        std::string arg = argv[1];
        if (arg == "-gv") {
            // Builds a parse tree in graphviz
            GVEmitter gve;
            std::cout << "digraph {" << std::endl;
            root->accept(&gve);
            std::cout << "}" << std::endl;
        }
        else if (arg == "-iloc") {
            //compiles supplied code to ILOC intermediate representation
            ILOCEmitter ie;
            root->accept(&ie);
        }
        else {
            std::cout << "usage: " << argv[0] << " [-gv OR -iloc] < \"infile\" > \"outfile\"\n";
        }
    }

    return 0;
}
