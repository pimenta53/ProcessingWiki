LEX=scan
NAME=processar_Wiki
objects=TrabInputs.o htmlCreate.o
installFiles = Makefile estrutura.h htmlCreate.c htmlCreate.h processar_Wiki.c scan.l TrabInputs.c TrabInputs.h 
flags=-c

$(NAME):$(NAME).c $(objects)
	cc -o  $(NAME) $(NAME).c $(objects) #-lfl
$(NAME).c:$(LEX).l 
	flex -o  $(NAME).c $(LEX).l  
TrabInputs.o:TrabInputs.c TrabInputs.h estrutura.h
	gcc $(flags) TrabInputs.c
htmlCreate.o:htmlCreate.c htmlCreate.h estrutura.h
	gcc $(flags) htmlCreate.c
clean:
	$(RM) $(objects) $(NAME).c
teste:$(NAME)
	./$(NAME) < lol.xml

install:$(NAME)
	mkdir -p Install
	mkdir -p XML
	mv $(installFiles) ./Install/
	rm $(objects) 
	#rm Makefile
