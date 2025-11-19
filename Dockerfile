FROM gcc:latest

COPY . /docker-c

WORKDIR /docker-c

# Install GNU compiler tools and GDB
RUN apt-get update && \
	apt-get install -y --no-install-recommends build-essential gdb && \
	rm -rf /var/lib/apt/lists/*

# RUN gcc -o main main.c

# CMD ["./main"]