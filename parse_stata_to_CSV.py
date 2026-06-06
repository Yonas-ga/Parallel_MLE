# This script was generated with help from an LLM.
# We considered it would not be worth it to spend too much time understanding Stata files. Instead we use this file to convert it into a CSV file 
# that we will ourselves parse into a Data_vector.

import csv
import re
from pathlib import Path


BASE_FOLDER = Path(__file__).resolve().parent

STATA_SETUP_FILE = BASE_FOLDER / "Data/1988" / "FAM1988.do"
RAW_DATA_FILE = BASE_FOLDER / "Data/1988" / "FAM1988.txt"
OUTPUT_CSV_FILE = BASE_FOLDER / "Data/parsed/FAM1988_parsed_full.csv"

stata_text = STATA_SETUP_FILE.read_text(errors="replace")

infix_block_match = re.search(
    r"\binfix\s+(.*?)\s+using\s+",
    stata_text,
    flags=re.S | re.I
)

if infix_block_match is None:
    raise RuntimeError("Could not find the 'infix ... using ...' block in the Stata file.")

infix_block = infix_block_match.group(1)


variable_layout = []

matches = re.findall(
    r"\b([A-Za-z][A-Za-z0-9_]*)\s+(\d+)\s*-\s*(\d+)",
    infix_block
)

for variable_name, start_column, end_column in matches:
    variable_layout.append(
        (
            variable_name,
            int(start_column),
            int(end_column)
        )
    )

if len(variable_layout) == 0:
    raise RuntimeError("No variables were found in the Stata infix block.")

column_names = []

for variable_name, start_column, end_column in variable_layout:
    column_names.append(variable_name)


last_column_needed = 0

for variable_name, start_column, end_column in variable_layout:
    if end_column > last_column_needed:
        last_column_needed = end_column


def parse_fixed_width_line(line):

    line = line.rstrip("\n\r")

    if len(line) < last_column_needed:
        line = line.ljust(last_column_needed)

    values = []

    for variable_name, start_column, end_column in variable_layout:
        value = line[start_column - 1:end_column]
        value = value.strip()
        values.append(value)

    return values

number_of_rows = 0

with RAW_DATA_FILE.open(encoding="utf-8", errors="replace") as raw_file, \
     OUTPUT_CSV_FILE.open("w", newline="", encoding="utf-8") as csv_file:

    csv_writer = csv.writer(csv_file, quoting=csv.QUOTE_ALL)
    csv_writer.writerow(column_names)

    for raw_line in raw_file:
        parsed_values = parse_fixed_width_line(raw_line)
        csv_writer.writerow(parsed_values)
        number_of_rows += 1


print(f"Finished parsing {number_of_rows} rows.")
print(f"Wrote CSV file to: {OUTPUT_CSV_FILE}")