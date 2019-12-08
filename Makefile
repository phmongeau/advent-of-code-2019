run: day6
	./day6

day6: day6.cpp
	@g++ -g day6.cpp -o day6

day5: day5.cpp
	@g++ -g day5.cpp -o day5

day4: day4.cpp
	@g++ -g day4.cpp -o day4
	./day4
	@rm day4

day3: day3.cpp
	@g++ -g day3.cpp -o day3
	./day3
	@rm day3

day2: day2.cpp
	@g++ -g day2.cpp -o day2
	./day2
	@rm day2

day1: day1.cpp
	@g++ day1.cpp -o day1
	./day1
	@rm day1

