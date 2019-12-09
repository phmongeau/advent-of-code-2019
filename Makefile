run: day7
	./day7

%: %.cpp
	@g++ -g $< -o $@
