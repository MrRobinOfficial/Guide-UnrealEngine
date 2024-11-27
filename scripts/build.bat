@echo off

REM Create the virtual environment if it doesn't exist
python -m venv .venv

REM Activate the virtual environment
CALL .venv\Scripts\activate.bat

REM Install the dependencies from requirements.txt
pip install -r .\scripts\requirements.txt

REM Run the build script
python .\scripts\build.py

REM Deactivate the virtual environment after building the exe
deactivate

REM Exit the script
exit
