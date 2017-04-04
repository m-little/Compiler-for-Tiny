OBJS= obj/main.o obj/scanner.o obj/parser.o obj/AST.o obj/GVEmitter.o \
	  obj/ILOCEmitter.o

tiny : $(OBJS)
	g++ $(OBJS) -o tiny

obj/main.o : main.cpp AST.h GVEmitter.h ILOCEmitter.h
	g++ -c main.cpp -o obj/main.o

gen/scanner.c : tiny.l
	flex tiny.l

obj/scanner.o : gen/scanner.c gen/parser.h
	g++ -c gen/scanner.c -Igen -I./ -o obj/scanner.o

gen/parser.c gen/parser.h : tiny.y
	bison tiny.y

obj/parser.o : gen/parser.c AST.h
	g++ -c gen/parser.c -I./ -o obj/parser.o

obj/AST.o : AST.cpp AST.h
	g++ -c AST.cpp -o obj/AST.o

obj/GVEmitter.o : GVEmitter.cpp GVEmitter.h AST.h
	g++ -c GVEmitter.cpp -o obj/GVEmitter.o

obj/ILOCEmitter.o : ILOCEmitter.cpp ILOCEmitter.h AST.h
	g++ -c ILOCEmitter.cpp -o obj/ILOCEmitter.o

clean :
	rm -f tiny obj/* gen/*

