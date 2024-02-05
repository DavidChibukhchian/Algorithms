PREF_SRC = ./source/
PREF_OBJ = ./build/

array : array_tests.exe

array_tests.exe : $(PREF_OBJ)main.o $(PREF_OBJ)tests.o $(PREF_OBJ)Stack_array.o
	g++ $(PREF_OBJ)main.o $(PREF_OBJ)tests.o $(PREF_OBJ)Stack_array.o -o array_tests.exe

list : list_tests.exe

list_tests.exe : $(PREF_OBJ)main.o $(PREF_OBJ)tests.o $(PREF_OBJ)Stack_list.o
	g++ $(PREF_OBJ)main.o $(PREF_OBJ)tests.o $(PREF_OBJ)Stack_list.o -o list_tests

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp | build/
	g++	-c $< -o $@

build/ :
	if not exist build mkdir build

.PHONY : clean

clean : 
	if exist list_tests.exe del list_tests.exe
	if exist array_tests.exe del array_tests.exe
	del /q .\build