#!/usr/bin/env bash

mdmerge -o "../README.md" "../sections/base.md"
doctoc --maxlevel 3 "../README.md"
