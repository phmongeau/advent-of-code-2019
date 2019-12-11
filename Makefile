run: day9
	./$<

%: %.cpp
	@g++ -g -fsanitize=address $< -o $@
