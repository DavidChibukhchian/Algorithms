PREF_SRC = ./source/
PREF_OBJ = ./build/

test_three_sort_functions : $(PREF_OBJ)test_three_sort_functions.o $(PREF_OBJ)sorts.o
	g++ $(PREF_OBJ)test_three_sort_functions.o $(PREF_OBJ)sorts.o -o $@

test_merge_sort : $(PREF_OBJ)test_merge_sort.o $(PREF_OBJ)sorts.o
	g++ $(PREF_OBJ)test_merge_sort.o $(PREF_OBJ)sorts.o -o $@

test_LSD_sort : $(PREF_OBJ)test_LSD_sort.o $(PREF_OBJ)sorts.o
	g++ $(PREF_OBJ)test_LSD_sort.o $(PREF_OBJ)sorts.o -o $@

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp | build/
	g++	-c $< -o $@

build/ :
	if not exist build mkdir build

.PHONY : clean

clean : 
	if exist *.exe del *.exe
	del /q .\build