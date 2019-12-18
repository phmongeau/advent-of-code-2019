run: day12
	./$<

%: %.cpp
	# @g++ -g -fsanitize=address $< -o $@
	@g++ -g $< -o $@
