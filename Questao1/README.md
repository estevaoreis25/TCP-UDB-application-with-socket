# Aplicação UDP Cliente Servidor Utilizando Socket

Essa solução aplica os conceitos de um servidor UDP, onde é iniciado uma aplicação servidor que o tempo inteiro espera dados de uma aplicação cliente. A aplicação cliente é incializada informando os dados de endereço de ip e porta do servidor e ai então pode enviar mensagens ao servidor. Quando o servidore recebe a mensagem, ele apresenta a mensagem recebida e reenvia para o cliente a mesma mensagem como uma forma de confirmar que recebeu aquela mensagem.

## Limitações da solução
Esta solução é limitada nas seguntes questões:
- Sempre que o cliente deseja enviar alguma mensagem para o servidor, ele precisa inicializar o programa passando sempre as informações de endereço de IP e porta para se conectar ao servidor
- O servidor sempre reenvia a mesma mensagem para o cliente, nao sendo possivel personalizar a mensagem de confirmação de recebimento dos dados enviados para o cliente.

## Funções Utilizadas
### printf
    printf é uma função utilizada para imprimir mensagens na tela do usuário.
### socket
    A função socket cria um ponto de comunicação e retorna um descritor para um arquivo ou –1 se houve algum erro (como as funções creat e open).
### htonl/ntohs
    As funções convertem e retornam um o endereço passado como parâmetro para um ordenamento de byte significativo. Sendo que as funções htons e htonl retornam o valor na ordem de bytes da rede e as funções ntohs e ntohl retornam o valor na ordem de bytes de um host.
### bind
    A função bind associa o socket criado a porta local do sistema operacional. Nesta associação é verificado se a porta já não está sendo utilizada por algum outro processo. Será através desta associação (porta) que o programa irá receber dados (bytes) de outros programas. É passada para a função a estrutura criada anteriormente assim como o socket criado. A função bind retorna 0 (zero) em caso de sucesso e –1 em caso de erro.
### sizeof
    Existe um operador em C que indica o tamanho em bytes que uma determinada variável está utilizando na memória. Pode-se também colocar um determinado tipo como parâmetro que o resultado será o mesmo.
### scanf
    Para realizar a entrada de valores para as variáveis deve ser utilizada a função scanf. 
### sendto
    A função send é utilizada para enviar uma mensagem para outro socket.A função retorna o número de bytes enviados ou –1 se houve erro. A função sendto é utilizada para comunicação não orientada a conexão (UDP).
### strlen 
    Esta função irá retornar a quantidade de caracteres existentes em uma string, não considerando o caractere NULL na contagem dos caracteres.
### perror
    A função perror mapeia o erro numérico, contido na variável global errno, para uma mensagem de erro. Em seguida, a função imprime essa mensagem de erro na saída de erro padrão (stderr).
### recvfrom
    A função recv é utilizada para receber (ler) uma mensagem de um socket. Para leitura de mensagens, também pode ser utilizada a função read. A função retorna o número de bytes lidos ou –1 se houve erro. As função recvfrom é utilizada para comunicação não orientada a conexão (UDP).

### close
    A função close é utilizada para fechar um arquivo. Quando se fecha um arquivo, todas as operações de saída pendentes em memória são gravadas no disco e as estruturas de controle interno são liberadas pelo sistema operacional.

### memset
    Descrição A função da biblioteca C memset(str, c, n) copia o caracter c (um unsigned char) para os n primeiros caracteres da string apontada por str.
### inet_addr
    A função inet_addr converte o endereço passado (inclusive com pontos) para um valor binário (ordenado) em bytes.
### inet_ntoa
    A função inet_ntoa realiza a operação inversa de inet_aton. A partir de um valor binário (estrutura) ela retorna o endereço em formato string (inclusive com pontos).
