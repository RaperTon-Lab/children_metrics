import os
from PyPDF2 import PdfMerger

# Directory containing the PDF files to merge
directory = os.getcwd()
directory += "/output"
OUTPUT_FOLDER = "output"

# Output merged PDF file
output_file = "merged.pdf"

# Get all PDF files in the directory
pdf_files = [file for file in os.listdir(directory) if file.endswith(".pdf")]

# Sort PDF files alphabetically
pdf_files.sort()

# Initialize PDF merger
merger = PdfMerger()

output_path = directory

# Merge all PDF files
for pdf_file in pdf_files:
    file_path = os.path.join(output_path, pdf_file)
    merger.append(file_path)

for pdf_file in pdf_files:
    file_path = os.path.join(directory, pdf_file)
    os.remove(file_path)
# Save the merged PDF file in the "output" folder
output_path = os.path.join(output_path, output_file)
merger.write(output_path)
merger.close()

# Remove all the source PDF files

print(
    f"Merged {len(pdf_files)} PDF files into '{output_path}'. Source files have been removed."
)
