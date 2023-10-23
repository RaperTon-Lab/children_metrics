#!/bin/bash

# MySQL configuration
MYSQL_USER="user"
MYSQL_PASSWORD="passworD@123"
MYSQL_DATABASE="angalwadi"
MYSQL_TABLE="April2023adolescent"

# Output file
OUTPUT_FILE="table_data.md"

# MySQL query to retrieve data
QUERY="SELECT Sl_No, Name, Year, Month, Height_cm, Weight_Kg FROM $MYSQL_TABLE"

# Execute MySQL query and redirect output to a Markdown file
mysql -u $MYSQL_USER -p$MYSQL_PASSWORD -D $MYSQL_DATABASE -B -e "$QUERY" > $OUTPUT_FILE

# Convert Markdown to PDF using pandoc
pandoc $OUTPUT_FILE -o table_data.pdf

# Remove the intermediate Markdown file
rm $OUTPUT_FILE

echo "Export complete. The PDF file is 'table_data.pdf'."
