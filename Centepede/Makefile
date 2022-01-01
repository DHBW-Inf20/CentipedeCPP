Game:
	g++ SourceCode/Startup.cpp lib/concurrency_lib.cpp lib/console_lib.cpp lib/string_helper.cpp lib/file_lib.cpp SourceCode/Common/centipedeSettings.cpp -o centipede -std=c++17

Test:
	g++ TestCode/Startup.cpp lib/concurrency_lib.cpp lib/console_lib.cpp lib/string_helper.cpp lib/file_lib.cpp TestCode/centipedeSettingsMock.cpp -o centipedeTest -std=c++17

cleanGame:
	rm centipede

cleanTest:
	rm centipedeTest