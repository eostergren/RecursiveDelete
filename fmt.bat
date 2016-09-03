:@REM "C:\Program Files\AStyle\bin\Astyle.exe" --options=Astyle_opt.txt Source\*.cpp Source\*.hpp Source\*.c Source\*.h
:@REM  seems to stop processing when an extension type is not found

"C:\Program Files\AStyle\bin\Astyle.exe" --options=Astyle_opt.txt Source\*.cpp
"C:\Program Files\AStyle\bin\Astyle.exe" --options=Astyle_opt.txt Source\*.hpp
"C:\Program Files\AStyle\bin\Astyle.exe" --options=Astyle_opt.txt Source\*.c
"C:\Program Files\AStyle\bin\Astyle.exe" --options=Astyle_opt.txt Source\*.h
