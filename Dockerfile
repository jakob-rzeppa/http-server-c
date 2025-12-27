FROM gcc:latest

COPY . /docker-c

WORKDIR /docker-c

# Install GNU compiler tools and GDB
RUN apt-get update && \
	apt-get install -y --no-install-recommends build-essential gdb make && \
	rm -rf /var/lib/apt/lists/*

# Build the project using Makefile
RUN make

# Run the server
CMD ["./build/main"]