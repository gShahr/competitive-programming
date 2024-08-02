@echo off

for /l %%i in (1, 1, 100) do (
    echo %%i

    1994-C-generator.exe %%i 10 7 > input.txt
    1994-C.exe < input.txt > output.txt
    1994-C-naive.exe < input.txt > answer.txt

    fc output.txt answer.txt || goto :out
)

:out