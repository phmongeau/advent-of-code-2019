run: day8
	./day8

%: %.cpp
	@g++ -g $< -o $@
