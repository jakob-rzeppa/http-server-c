FROM gcc:latest

COPY . /docker-c

WORKDIR /docker-c

RUN gcc -o main main.c

CMD ["./main"]