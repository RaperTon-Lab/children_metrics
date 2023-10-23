import mysql.connector
from tabulate import tabulate
from fpdf import FPDF

# MySQL configuration
MYSQL_HOST = "localhost"
MYSQL_USER = "user"
MYSQL_PASSWORD = "passworD@123"
MYSQL_DATABASE = "angalwadi"
TABLES = [
    "October2023infant",
    "October2023children",
    "October2023preschool",
    "October2023adolescent",
]


# PDF page configuration
PAGE_WIDTH = 210  # Width of A4 page in mm
PAGE_HEIGHT = 297  # Height of A4 page in mm
MARGIN = 10  # Margin size in mm


connection = mysql.connector.connect(
    host=MYSQL_HOST, user=MYSQL_USER, password=MYSQL_PASSWORD, database=MYSQL_DATABASE
)
cursor = connection.cursor()

for MYSQL_TABLE in TABLES:
    # Output PDF file
    OUTPUT_FILE = MYSQL_TABLE + ".pdf"

    # MySQL query to retrieve data
    query = f"SELECT Sl_No, Name, Year, Month, Height_cm, Weight_Kg FROM {MYSQL_TABLE}"
    cursor.execute(query)
    data = cursor.fetchall()

    # Format data as a table
    headers = ["Sl_No", "Name", "Year", "Month", "Height_cm", "Weight_Kg"]
    table = tabulate(data, headers=headers, tablefmt="fancy_grid")

    # Create PDF document
    pdf = FPDF()
    pdf.add_page()
    pdf.set_font("Courier", size=10)

    # Add table title
    pdf.set_font("Arial", style="B", size=14)
    pdf.cell(0, 10, f"Table: {MYSQL_TABLE}", ln=True, align="C")

    # Set table boundary style
    pdf.set_fill_color(255)
    pdf.set_draw_color(0)

    # Calculate maximum column widths
    max_width = PAGE_WIDTH - 2 * MARGIN
    column_widths = [pdf.get_string_width(header) + 6 for header in headers]
    for row in data:
        for i, value in enumerate(row):
            width = pdf.get_string_width(str(value)) + 6
            if width > column_widths[i]:
                column_widths[i] = width

    # Calculate table width and adjust column widths if necessary
    table_width = sum(column_widths)
    if table_width > max_width:
        ratio = max_width / table_width
        column_widths = [int(width * ratio) for width in column_widths]

    # Draw table header
    pdf.set_font("Arial", style="B", size=12)
    pdf.set_fill_color(192)
    for i, header in enumerate(headers):
        pdf.cell(column_widths[i], 10, str(header), 1, 0, "C", fill=True)
    pdf.ln()

    # Draw table rows
    pdf.set_font("Arial", size=12)
    pdf.set_fill_color(255)
    for row in data:
        for i, value in enumerate(row):
            pdf.cell(column_widths[i], 10, str(value), 1, 0, "C", fill=True)
        pdf.ln()

    # Save PDF file
    pdf.output(OUTPUT_FILE, "F")

    print(f"Export complete for {MYSQL_TABLE}. The PDF file is {OUTPUT_FILE}.")

# Close MySQL connection
cursor.close()
connection.close()
