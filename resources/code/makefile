stu:stuscore.o in.o out.o cal.o
	gcc -o stu stuscore.o in.o out.o cal.o
stuscore.o:stuscore.c stuscore.h
	gcc -c stuscore.c
in.o:in.c stuscore.h
	gcc -c in.c
out.o:out.c stuscore.h
	gcc -c out.c
cal.o:cal.c stuscore.h
	gcc -c cal.c
clean:
	rm stu stuscore.o in.o out.o cal.o
