#!/usr/bin/env node

"use strict";

import fs from "node:fs";
import { readFile } from "fs/promises";

import { createSpinner } from "nanospinner";
import chalk from "chalk";
import chalkAnimation from "chalk-animation";
import inquirer from "inquirer";
import gradient from "gradient-string";
import logSymbols from "log-symbols";

import { deleteAsync } from "del";
import { report, sleep } from "../common/utils.js";

const filePath = "src/lab.cpp";

/**
 * Performs the setup tasks asynchronously.
 *
 * @return {Promise<void>} Promise that resolves when setup tasks are complete
 */
export async function setup() {
    const action = await inquirer.prompt({
        name: "action",
        type: "list",
        message: "What do you want to do?",
        choices: [
            {
                name: "Create lab",
                value: "create",
            },
            {
                name: "Recreate lab",
                value: "recreate",
            },
            {
                name: "Remove lab",
                value: "remove",
            },
            {
                name: "Validate lab",
                value: "validate",
            },
        ],
    });

    switch (action.action) {
        case "create":
            await createLab();
            break;
        case "recreate":
            await recreateLab();
            break;
        case "remove":
            await removeLab();
            break;
        case "validate":
            await validateLab();
            break;
    }
}

export async function createLab() {
    const spinner = createSpinner("Setting up...").start();

    // TODO: Create directory if it doesn't exist

    try {
        if (!fs.existsSync(filePath)) {
            fs.writeFileSync(filePath, getCppContent());
            spinner.success("Created file: " + chalk.greenBright(filePath));
        } else {
            spinner.warn(
                "File already exists: " + chalk.yellowBright(filePath)
            );
        }
    } catch (error) {
        if (error.code === "EEXIST") {
            spinner.warn(
                "File already exists: " + chalk.yellowBright(filePath)
            );
        } else {
            spinner.error("Failed to create file");
            console.error(error);
        }
    }
}

export async function removeLab() {
    const spinner = createSpinner("Removing file...").start();

    try {
        if (fs.existsSync(filePath)) {
            await deleteAsync([filePath]);
            spinner.success("Removed file: " + chalk.greenBright(filePath));
        } else {
            spinner.warn("File doesn't exist: " + chalk.yellowBright(filePath));
        }
    } catch (error) {
        spinner.error("Failed to remove file");
        console.error(error);
    }
}

export async function recreateLab() {
    await removeLab();
    await createLab();
}

export async function validateLab() {
    // const code = await readFile(filePath, "utf8");
    // const tasks = [
    //     {
    //         name: "Task 1",
    //         description: "Create a variable named 'Health' initialized to 100",
    //         startComment: "//__TASK_1_START__",
    //         endComment: "//__TASK_1_END__",
    //         expected: "int32 Health = 100;",
    //     },
    //     {
    //         name: "Task 2",
    //         description: "Set the value of 'Health' to 500",
    //         startComment: "//__TASK_2_START__",
    //         endComment: "//__TASK_2_END__",
    //         expected: "Health = 500;",
    //     },
    //     {
    //         name: "Task 3",
    //         description:
    //             "Define a constant variable 'MaxHealth' with value 1000",
    //         startComment: "//__TASK_3_START__",
    //         endComment: "//__TASK_3_END__",
    //         expected: "const int32 MaxHealth = 1000;",
    //     },
    //     // Add more tasks as needed
    // ];
    // await report(code, tasks);
}

function getCppContent() {
    return `
/**
 * Welcome to this introduction!
 * Here, you will learn how to write C++ code and get familiar with syntax.
 * 
 * Happy coding!
 */

// === EXAMPLES ===

/**
 * Task 0: Create a variable named 'Age', which is of type 'int32'.
 * The value of 'Age' should be initialized to 18.
 */
  int32 Age = 18;

// === EXERCISES ===

/**
 * Task 1: Create a variable named 'Health', which is of type 'int32'.
 * The value of 'Health' should be brace initialized to 100.
 * 
 * Hint! You may want to get familiar with 'brace initialization'
 * More details here: https://github.com/MrRobinOfficial/Guide-UnrealEngine/tree/dev?tab=readme-ov-file#initialization
 */

  // CODE HERE

/**
 * Task 2: The value of 'Health' should be set to 500.
 * 
 * Hint! You may want to get familiar with 'assignment' operator.
 * More details here: https://github.com/MrRobinOfficial/Guide-UnrealEngine/tree/dev?tab=readme-ov-file#initialization
 */

  //__TASK_1_START__

  // CODE HERE

  //__TASK_1_END__

/**
 * Task 2: Define a constant variable named 'MaxHealth' of type 'const int32'.
 * Assign a value of 1000 to 'MaxHealth'.
 * 
 * Hint! You may want to get familiar with 'const' keyword.
 * More details here: https://github.com/MrRobinOfficial/Guide-UnrealEngine/tree/dev?tab=readme-ov-file#constants
 */

  //__TASK_2_START__

  // CODE HERE

  //__TASK_2_END__

/**
 * Task 3: Create a another variable named 'HealthNormalized', which is of type 'float'.
 * The value of 'HealthNormalized' should be set to health divide by max health.
 */

  //__TASK_3_START__

  // CODE HERE

  //__TASK_3_END__

/**
 * Task 4: Implement a function named 'DecreaseHealth(int32 Amount)'.
 * This function should decrease the 'Health' variable by the 'Amount' specified.
 */

  //__TASK_4_START__

  // CODE HERE

  //__TASK_4_END__

/**
 * Task 5: Write a function called 'IsPlayerAlive()' that returns a boolean value.
 * This function should return true if 'Health' is greater than 0, otherwise, it should return false.
 */

  //__TASK_5_START__

  // CODE HERE

  //__TASK_5_END__
`;
}

await setup();
