@echo off
chcp 1251 > NUL

echo -- ������ ����������: %*
echo -- �����: %1
echo -- ��� �����: %2

if "%1" equ "" (
	echo ---++  z03-06 ����� ����
	echo ---++  ����� = {�������, �������}
	echo ---++  ����  = ��� �����
	goto EXIT
)


if not "%1" equ "�������" if not "%1" equ "�������" if not "%1" equ "" (
	echo ---+ ����� ����� �����������
	goto EXIT
)

if "%1" equ "�������" if not "%1" equ "" if not "%2" equ "" if not exist "%2" (
	echo ---+ ���� %2 �� ������
	goto EXIT
)

if "%1" equ "�������" if exist "%2" (
	echo ---+ ���� %2 ��� ����������
	goto EXIT
)

if "%1" equ "�������" if "%2" equ "" (
	echo ---+ �� ������ ��� �����
	goto EXIT
)
if "%1" equ "�������" if "%2" equ "" (
	echo ---+ �� ������ ��� �����
	goto EXIT
)

if "%1" equ "�������" (
	copy /y NUL %2 > NUL
	echo ---+ ���� %2 ������
)

if "%1" equ "�������" (
	del "%2"
	echo ---+ ���� %2 ������
)

:EXIT
pause