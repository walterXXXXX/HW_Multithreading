FROM ubuntu:latest
	LABEL v.korolkov=""
	RUN apt-get update
	RUN apt-get install -y g++ clang mc
	WORKDIR /root/Task 2
	COPY main.cpp .
	RUN g++ main.cpp -o decorator_g++
	RUN clang++ main.cpp -o decorator_clang
	CMD ["./decorator_clang"]
	