#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;

	int nbfils = 0;
	for (int i=1, j=N; i<=N && j==N ; i++ ) {
		if (fork() == 0){
			nbfils = 0;
		}
		else{
			nbfils++;
		}
		std::cout << "pid="<< getpid() << " " << "ppid="<<getppid()<< " i:j " << i << ":" << j << std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if (fork() == 0) {
				nbfils = 0;
				j=0;
				std::cout << "pid="<< getpid() << " " << "ppid="<<getppid() << " k:j " << k << ":" << j << std::endl;
			} else {
				nbfils++;	
			}
		}
	}
	for (int i = 0; i < nbfils; i++) {
		int status;
		int pid = wait(&status);
		std::cout << getpid() << " tue le fils avec pid=" << pid << std::endl;
	}
	std::cout << "suicide du pere " << getpid() << " apres le massacre."  << std::endl;


	return 0;
}
