FROM ubuntu:latest
	LABEL v.korolkov=""
	RUN apt-get update
	RUN apt-get install -y g++ mc
	WORKDIR /root/hello_docker
	COPY hello_docker.cpp .
	RUN g++ hello_docker.cpp -o hello_docker
	CMD ["./hello_docker"]

	