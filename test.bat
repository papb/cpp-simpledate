@echo OFF
g++ test/*.cpp src/*.cpp -o test.exe
if %errorlevel% neq 0 exit /b %errorlevel%
test.exe