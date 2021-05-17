#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define QLEN 5               /* tamanho da fila de clientes  */
#define MAX_SIZE 80		/* tamanho do buffer */

int main(int argc, char *argv[]){
   struct sockaddr_in endServ;  /* endereco do servidor   */
   struct sockaddr_in endCli;   /* endereco do cliente    */
   int    sd, novo_sd;          /* socket descriptors */
	int    pid, alen,n; 

	if (argc<3) { // Verifica a quantidade de argumentos passados no terminal
		printf("Digite IP e Porta para este servidor\n");
		exit(1); 
	}


   memset((char *)&endServ,0,sizeof(endServ)); /* limpa variavel endServ    */
   endServ.sin_family 		= AF_INET;           	/* familia TCP/IP   */
   endServ.sin_addr.s_addr 	= inet_addr(argv[1]); 	/* endereco IP      */
   endServ.sin_port 		= htons(atoi(argv[2])); /* PORTA	    */

   /* Cria socket */
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "Falha ao criar socket!\n");
		exit(1); 
	}

   /* liga socket a porta e ip */
	if (bind(sd, (struct sockaddr *)&endServ, sizeof(endServ)) < 0) {
		fprintf(stderr,"Ligacao Falhou!\n");
		exit(1); 
	}

   /* Ouve porta */
	if (listen(sd, QLEN) < 0) {	
		fprintf(stderr,"Falhou ouvindo porta!\n");
		exit(1); 
	}


	printf("Servidor ouvindo no IP %s, na porta %s ...\n\n", argv[1], argv[2]);
   /* Aceita conexoes */
	alen = sizeof(endCli);
	for ( ; ; ){
		 /* espera nova conexao de um processo cliente ... */	
		if ( (novo_sd=accept(sd, (struct sockaddr *)&endCli, &alen)) < 0) {
			fprintf(stdout, "Falha na conexao\n");
			exit(1); 
		}
		if(fork() == 0){ // Cria processos filho para os clientes
			fprintf(stdout, "Cliente %s: %u conectado. PID: %d\n\n", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port), getpid()); 
			atende_cliente(novo_sd, endCli); // Função do comportamento do cliente
			exit(0); //Encerra o processo após a entrada FIM

		}


	} /* fim for */

	//close(sd);
	close(novo_sd);
	return 0;

} /* fim do programa */


int atende_cliente(int descritor, struct sockaddr_in endCli)  {

	char bufin[MAX_SIZE]; // buffer de dados recebidos
	char bufout[MAX_SIZE]; // buffer de dados enviados
	int  n; // número de caracteres lidos do cliente
	while (1) {

		memset(&bufin, 0x0, sizeof(bufin));
		n = recv(descritor, &bufin, sizeof(bufin),0); // recebendo dados da função send do cliente
		if (strncmp(bufin, "FIM", 3) == 0) // Verifica se o cliente quer encerrar a conexão
			break;
		fprintf(stdout, "Cliente >> %s", bufin); // Mensagens enviadar do cliente para o servidor
		if(strcmp(bufin, "LIBERADO\n") == 0){ // Se a mensagem que o cliente enviou for igual a LIBERADO,
			do{								  // agora o servidor pode enviar mensagens para o cliente
				printf("> ");
				scanf("%s", bufout); // scaneia mensagem que será enviada para o cliente
				bufout[n] = '\0'; // define fim da string
				send(descritor, bufout, strlen(bufout), 0); // Envia dados para o cliente
				
			}while(strcmp(bufout, "LIBERADO") != 0); // Envia dados enquanto for diferente de LIBERADO
		}
		

   } /* fim while */
		fprintf(stdout, "Encerrando conexao com %s:%u ...\n\n", inet_ntoa(endCli.sin_addr), ntohs(endCli.sin_port));
		close (descritor); // fecha socket
 } /* fim atende_cliente */
