@echo off
chcp 1251 > NUL

echo --������ ����������: %*
echo --�������� 1: %1
echo --�������� 2: %2
echo --�������� 3: %3
set /a res = %1 %3 %2
echo %res%

pause