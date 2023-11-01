import os
import re

# Specify the directory where your .gdml files are located
root_directory = 'buildNa/geometry'

# Define the search and replacement strings
search_string = 'scratch'
replace_string = 'Users'

# Recursively traverse through all files and subdirectories
for root, _, files in os.walk(root_directory):
    for filename in files:
        if filename.endswith('.gdml'):
            file_path = os.path.join(root, filename)

            # Read the contents of the file
            with open(file_path, 'r') as file:
                file_contents = file.read()

            # Perform the replacement using regular expressions
            updated_contents = re.sub(search_string, replace_string, file_contents)

            # Write the updated contents back to the file
            with open(file_path, 'w') as file:
                file.write(updated_contents)

            print(f'Replaced occurrences in {file_path}')
