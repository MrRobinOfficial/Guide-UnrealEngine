#!/usr/bin/env node

"use strict";

import { createSpinner } from "nanospinner";
import chalk from "chalk";
import chalkAnimation from "chalk-animation";
import logSymbols from "log-symbols";

import RegexParser from "regex-parser";
import { find } from "regexpbuilder";

export const sleep = (ms = 1500) => new Promise((r) => setTimeout(r, ms));

export async function report(code, tasks) {
    const spinner = createSpinner({ text: "Validating lab..." }).start();

    const results = [];

    for (const test of tasks) {
        spinner.clear();
        spinner.start({ text: `Validating ${test.name}...` });
        await sleep(1500);

        const startRegex = new RegExp(test.startComment + "[\\s\\S]*?");
        const endRegex = new RegExp(test.endComment);
        const startMatch = code.match(startRegex);
        const endMatch = code.slice(startMatch.index).match(endRegex);
        const actualCode = code
            .slice(
                startMatch.index + startMatch[0].length,
                startMatch.index + endMatch.index
            )
            .trim();

        const result = {
            name: test.name,
            description: test.description,
            actual: actualCode.trim(),
            expected: test.expected.trim(),
            isValid: actualCode.trim() === test.expected.trim(),
        };

        results.push(result);
    }

    spinner.success({ text: "Finish validating lab" });
    await sleep(1500);
    spinner.stop();

    const failedTasks = results.filter((task) => !task.isValid);

    if (failedTasks.length === 0) {
        console.log(logSymbols.success, chalk.green("All tasks passed!"));
    } else {
        console.log(
            logSymbols.error,
            chalk.red(` ${failedTasks.length} task(s) failed:`)
        );
        console.error(`
${failedTasks
    .map(
        (test) => `
  * ${test.name} - ${test.description}
  ${chalk.greenBright("Expected")}: ${test.expected}
  ${chalk.redBright("Actual")}: ${test.actual}`
    )
    .join("\n\n\t")}
`);
    }
}
