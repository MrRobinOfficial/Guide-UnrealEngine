"""
The build script is used to build the project.
"""

import os
import re

from rich.console import Console
console = Console()

import humanize
import datetime as dt

# Constants
constants = {
    "avg_wpm": 238,  # words per minute
    "output_filename": "README.md",
    "cpp_output_filename": "README_CPP.md",
    "sections_folder": "sections",
    "toc_placeholder_start": "<!-- START doctoc -->",
    "toc_placeholder_end": "<!-- END doctoc -->",
    "input_files": {
        "README": "sections/base.md",
        "README_CPP": "sections/summary_of_cpp_and_programming_world.md"
    }
}

def read_file(file_path):
    """Reads the content of a file."""
    with open(file_path, 'r', encoding='utf-8') as file:
        return file.read()

def resolve_includes(content, base_path, excluded_files, output_file):
    """Resolve the <<[filename.md] directives by including the content of the specified files."""
    # Find all <<[filename.md] directives
    include_pattern = r'<<\[(.*?)\]'
    matches = re.findall(include_pattern, content)

    for match in matches:
        include_file = os.path.join(base_path, match)

        # Avoid infinite loop by excluding files already being processed
        if include_file not in excluded_files and os.path.exists(include_file):
            include_content = read_file(include_file)
            content = content.replace(f'<<[{match}]', include_content)

            # Recursively resolve includes in the included file
            content = resolve_includes(content, base_path, excluded_files, output_file)

            excluded_files.append(include_file)  # Prevent future recursion for this file
        else:
            print(f"Skipping {include_file} to avoid infinite loop or missing file.")

    return content

def count_words_in_markdown(content):
    """Count the number of words in the Markdown content, excluding code blocks and headers."""
    # Remove code blocks (```) and inline code
    content = re.sub(r'```.*?```', '', content, flags=re.DOTALL)
    content = re.sub(r'`.*?`', '', content)

    # Remove links and images
    content = re.sub(r'!\[.*?\]\(.*?\)', '', content)
    content = re.sub(r'\[.*?\]\(.*?\)', '', content)

    # Count words (splitting by any whitespace)
    words = content.split()
    return len(words)

def generate_toc(file_path):
    """Generate a Table of Contents (TOC) for the Markdown file with indentation."""
    toc = "## Table of Contents\n\n"
    content = read_file(file_path)

    # Find all headers (e.g., ## Header, ### Subheader)
    headers = re.findall(r'^(##+)\s*(.*)', content, flags=re.MULTILINE)

    for header in headers:
        level = len(header[0])  # Count `#` to determine the level of the header
        title = header[1]
        # Convert header title to a valid anchor link
        anchor = title.lower().replace(' ', '-').replace('[', '').replace(']', '')
        toc += f"{'  ' * (level - 2)}- [{title}](#{anchor})\n"

    return toc

def replace_toc_placeholder(file_path, toc):
    """Replace the placeholder with the newly generated TOC."""
    content = read_file(file_path)

    # Find the TOC placeholder and replace it with the new TOC
    content = re.sub(
        rf"{constants['toc_placeholder_start']}.*?{constants['toc_placeholder_end']}",
        f"{constants['toc_placeholder_start']}\n\n{toc}\n{constants['toc_placeholder_end']}",
        content,
        flags=re.DOTALL
    )

    # Write the modified content back to the file
    with open(file_path, 'w', encoding='utf-8') as file:
        file.write(content)

def merge_markdown_files(input_file, output_file):
    """Merge markdown files, read from the input file and replace includes in the output file."""
    content = read_file(input_file)

    # Exclude the input file from being included (to avoid infinite loop)
    excluded_files = [input_file]

    # Resolve includes (<<[filename.md] patterns) only in the output file
    content = resolve_includes(content, constants['sections_folder'], excluded_files, output_file)

    # Write the final content to the output file
    with open(output_file, 'w', encoding='utf-8') as file:
        file.write(content)

def main():
    # Merge the main README content
    input_file = constants['input_files']['README']
    output_file = constants['output_filename']
    merge_markdown_files(input_file, output_file)
    print(f"Merged files into {output_file}")

    # Generate and replace TOC for the main README
    toc = generate_toc(output_file)
    replace_toc_placeholder(output_file, toc)
    print(f"Replaced TOC placeholder in {output_file}")

    # Count words in the main README
    content = read_file(output_file)
    word_count = count_words_in_markdown(content)
    print(f"Word count for {output_file}: {word_count}")

    # Merge the C++ README content
    input_file_cpp = constants['input_files']['README_CPP']
    cpp_output_file = constants['cpp_output_filename']
    merge_markdown_files(input_file_cpp, cpp_output_file)
    print(f"Merged C++ section into {cpp_output_file}")

    # Generate and replace TOC for the C++ README
    toc_cpp = generate_toc(cpp_output_file)
    replace_toc_placeholder(cpp_output_file, toc_cpp)
    print(f"Replaced TOC placeholder in {cpp_output_file}")

    # Calculate reading time (in minutes)
    reading_time = word_count / constants['avg_wpm']

    # Convert reading time to timedelta
    delta = dt.timedelta(minutes=reading_time)

    # Convert to the most appropriate unit and human-readable format
    human_readable_time = humanize.precisedelta(delta, suppress=["seconds"])

    # Print word count and human-readable reading time
    console.print(f"Word count: {word_count}")
    console.print(f"Reading time: {human_readable_time}")

if __name__ == "__main__":
    main()
