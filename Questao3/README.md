# Aplicação TCP Cliente Servidor Utilizando Socket

A solução consiste na conexão e comunicação entre cliente e servidor, onde primeiramente o servidor deve estar rodando, e define o IP e porta para poder ser acessado. Posteriormente o cliente se conecta ao servidor e dialoga de forma bidirecional. Dentro do arquivo tcpClient.c foi utilizada uma tratativa para o sinal SIGINT (CTRL+C).

## Limitações da solução
- Ao executar o programa, deve ser respeitado os momentos de envio e recebimento de mensagens para evitar bugs
- Vários clientes podem enviar mensagens simultaneamente para o servidor, porém o servidor não envia mensagem para todos os clientes de uma só vez

## Funções Utilizadas

### socket
    A função socket (int socket(int domain, int type, int protocol)) cria um ponto de comunicação e retorna um descritor. Os argumentos são, respectivamente, domínio da comunicação, que para TCP/IP utiliza-se AF_INET. O tipo da comunicação, que para TCP é SOCK_STREAM. Caso queira usar um protocolo em particular, deve-se passar como o último argumento da função.
### htonl/ntohs
    As funções convertem e retornam um o endereço passado como parâmetro para um ordenamento de byte significativo. Sendo que as funções htons e htonl retornam o valor na ordem de bytes da rede e as funções ntohs e ntohl retornam o valor na ordem de bytes de um host.
### bind
    A função  bind (int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);) atribui o endereço especificado por addr para o soquete referido pelo descritor de arquivo sockfd.
### sizeof
    Retorna a quantidade de bytes que uma variável consome no programa
### scanf
    Para realizar a entrada de valores para as variáveis deve ser utilizada a função scanf. 
### send
    A função send é utilizada em conexões TCP ou orientada a conexão. Ela é usada para enviar uma mensagem para outro socket. Retorna o número de bytes enviados ou –1 se houve erro.
### strlen 
    Esta função irá retornar a quantidade de caracteres existentes em uma string.
### perror
    A função perror mapeia o erro numérico, contido na variável global errno, para uma mensagem de erro. Em seguida, a função imprime essa mensagem de erro na saída de erro padrão (stderr).
### recv
    A função recv é utilizada para receber mensagens de ambas as conexões de um socket (cliente ou servidor). A função retorna o número de bytes lidos ou –1 se houve erro.
### fork
    A função fork é utilizada para criar novos processos dentro do programa, onde esses processos são chamados de filhos. Nesse contexto, eles geram novos clientes para as requisições de conexão com o servidor.

### accept
    Após ter utilizado a função listen para habilitar as conexões, é necessário aceitar a conexões. A função accept aceita as conexões efetuadas pelos clientes. Deve ser passado para a função o socket aberto, a estrutura que irá receber os dados do cliente e o tamanho do endereço. A função irá retornar um descritor para a conexão aceita ou –1 se houve erro.

### close
    A função close é utilizada para fechar um arquivo.

### memset
    Descrição A função da biblioteca C memset(str, c, n) copia o caracter c (um unsigned char) para os n primeiros caracteres da string apontada por str.
### inet_addr
    A função inet_addr converte o endereço passado (inclusive com pontos) para um valor binário (ordenado) em bytes.
### inet_ntoa
    A função inet_ntoa realiza a operação inversa de inet_aton. A partir de um valor binário (estrutura) ela retorna o endereço em formato string (inclusive com pontos).
