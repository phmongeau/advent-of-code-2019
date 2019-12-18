run: day11
	./$<

%: %.cpp
	# @g++ -g -fsanitize=address $< -o $@
	@g++ -g $< -o $@
