# Create the virtual environment if it doesn't exist
if (-Not (Test-Path ".\.venv")) {
    python -m venv .\.venv
}

# Activate the virtual environment
& .\.venv\Scripts\Activate.ps1

# Install the dependencies from requirements.txt
pip install -r .\scripts\requirements.txt

# Run the build script
python .\scripts\build.py

# Deactivate the virtual environment
deactivate

# Exit the script
exit
