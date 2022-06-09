g++ -O3 -Wall -shared\
    -std=c++14\
 	-fPIC `python3.7 -m pybind11 --includes`\
	-I ./include\
 	main.cpp mixbox.cpp\
 	-o mixbox`python3.7-config --extension-suffix`
