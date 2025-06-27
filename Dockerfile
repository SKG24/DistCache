# Dockerfile
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y \
  build-essential cmake git curl wget \
  libgtest-dev libmsgpack-dev libssl-dev libboost-all-dev \
  pkg-config

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Build project
RUN mkdir -p build && cd build && cmake .. && make

# Default command
CMD ["/bin/bash"]
