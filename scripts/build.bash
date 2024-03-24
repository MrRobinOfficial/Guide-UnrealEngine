#!/usr/bin/env bash

# NOTE; Make sure you have install mdmerge and doctoc CLIs.
# Don't install wrong mdmerge! And install these tools globally!

# You can find mdmerge: https://github.com/JeNeSuisPasDave/MarkdownTools
# You can find doctoc: https://github.com/thlorenz/doctoc

mdmerge --out="../README.md" "../sections/base.md"
doctoc "../README.md"

mdmerge --out="../README_CPP.md" "../sections/summary_of_cpp_and_programming_world.md"
doctoc "../README_CPP.md"
