# Use an official Python base image
FROM gcc:latest 
FROM python:3.9

# Create and activate a virtual environment
#RUN python3 -m venv /venv
#ENV PATH="/venv/bin:$PATH"

# Set the working directory inside the container
WORKDIR /app
# Set the working directory inside the container

# Copy the entire project files into the container
COPY . /app
# Copy only the necessary Python files for installation
#COPY requirements.txt /app/requirements.txt

# Install Python dependencies


# Use an official GCC base image


RUN apt-get update && \
    apt-get install -y python3 python3-pip

# Install MySQL connector for C++
RUN apt-get install -y libmysqlcppconn-dev
RUN pip install --upgrade pip

RUN pip install -r requirements.txt

# Build the C++ application
RUN g++ -Wall -I/usr/include/cppconn -o main src/main.cpp -L/usr/lib -lmysqlcppconn
