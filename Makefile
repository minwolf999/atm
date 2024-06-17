objects = src/main.o src/login.o src/database.o src/menuController.o
libs = -lsqlite3

atm : $(objects)
	cc -o atm $(objects) $(libs)
	rm -f $(objects)

clean :
	rm -f $(objects)
