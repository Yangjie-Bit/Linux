ALL:sem single threadpool productor_consumer pron_con cond mutex exit create
sem:sem.c
	gcc -g $^ -o $@ -lpthread
single:single.cpp
	g++ -g $^ -o $@ -lpthread
threadpool:threadpool.cpp
	g++ -g $^ -o $@ -lpthread
productor_consumer:productor_consumer.cpp
	g++ -g $^ -o $@ -lpthread
pron_con:pron_con.cpp
	g++ -g $^ -o $@ -lpthread
cond:cond.c
	gcc -g $^ -o $@ -lpthread
mutex:mutex.c
	gcc -g $^ -o $@ -lpthread
exit:exit.c
	gcc -g $^ -o $@ -lpthread
create:create.c
	gcc -g $^ -o $@ -lpthread
	
