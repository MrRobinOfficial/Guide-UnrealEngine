#!/bin/bash

# Create the virtual environment if it doesn't exist
python3 -m venv .venv

# Activate the virtual environment
source .venv/bin/activate

# Install the dependencies from requirements.txt
pip install -r ./scripts/requirements.txt

# Run the build script
python3 ./scripts/build.py

# Deactivate the virtual environment after building the exe
deactivate

# Exit the script
exit
