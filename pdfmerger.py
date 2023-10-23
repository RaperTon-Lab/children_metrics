import os
from PyPDF2 import PdfMerger

# Directory containing the PDF files to merge
directory = os.getcwd()

# Output merged PDF file
output_file = "merged.pdf"

# Get all PDF files in the directory
pdf_files = [file for file in os.listdir(directory) if file.endswith(".pdf")]

# Sort PDF files alphabetically
pdf_files.sort()

# Initialize PDF merger
merger = PdfMerger()

# Merge all PDF files
for pdf_file in pdf_files:
    file_path = os.path.join(directory, pdf_file)
    merger.append(file_path)

# Save the merged PDF file
merger.write(output_file)
merger.close()

print(f"Merged {len(pdf_files)} PDF files into '{output_file}'.")
