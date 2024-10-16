#!/bin/bash

# Prompt for task number
echo "Enter the task number:"
read task_number

# Create a directory named Task-<task number>
task_dir="Task-$task_number"
mkdir "$task_dir"

# Change to the new directory
cd "$task_dir" || exit

touch "Turn1-ModelA.cpp"
touch "Turn1-ModelB.cpp"
touch "Turn2-ModelA.cpp"
touch "Turn2-ModelB.cpp"
touch "Turn3-ModelA.cpp"
touch "Turn3-ModelB.cpp"

echo "Task-$task_number created with 6 dummy .cpp files."
