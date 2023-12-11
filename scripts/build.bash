#!/usr/bin/env bash

# Make sure you have install mdmerge and doctoc CLIs.
# You can find mdmerge: https://github.com/JeNeSuisPasDave/MarkdownTools
# You can find doctoc: https://github.com/thlorenz/doctoc

mdmerge -o "../README.md" "../sections/base.md"
doctoc "../README.md"
