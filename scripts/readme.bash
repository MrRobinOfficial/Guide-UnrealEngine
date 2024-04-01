#!/usr/bin/env bash

# NOTE! Make sure you have install readtime and mwc CLIs.
# And install these tools globally!

# You can find readtime: https://github.com/guedesfelipe/readtime_cli
# You can find mwc: https://github.com/gandreadis/markdown-word-count

readtime md "../README.md" --wpm 183

mwc "../README.md"