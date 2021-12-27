GameUnix:
	g++ SourceCode/Startup.cpp lib/concurrency_lib.cpp lib/console_lib.cpp lib/string_helper.cpp lib/file_lib.cpp -o centipedeUnix -std=c++17 -lncurses

GameWindows:
	g++ SourceCode/Startup.cpp lib/concurrency_lib.cpp lib/console_lib.cpp lib/string_helper.cpp lib/file_lib.cpp -o centipedeWindows -std=c++17

TestUnix:
	g++ TestCode/Startup.cpp lib/concurrency_lib.cpp lib/console_lib.cpp lib/string_helper.cpp lib/file_lib.cpp -o centipedeTestUnix -std=c++17 -lncurses

TestWindows:
	g++ TestCode/Startup.cpp lib/concurrency_lib.cpp lib/console_lib.cpp lib/string_helper.cpp lib/file_lib.cpp -o centipedeTestWindows -std=c++17

cleanGame:
	rm centipedeUnix
	rm centipedeWindows

cleanTest:
	rm centipedeTestUnix
	rm centipedeTestWindows