# Amira Ajanaku (25111699)
# Senzo Lukhele (24691497)
# Jay Macaskill (25198387)

# COS 214 (Software Modelling) Practical 4
# Last Modified: 5 September 2026

# Dockerfile

FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y g++ make gdb valgrind git && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /taskforge

COPY . /taskforge/

RUN make

CMD ["./taskforge"]