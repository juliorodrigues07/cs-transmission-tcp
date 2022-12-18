[![C99](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf)

# Cliente-Servidor (_TCP_)
Implementação de um par cliente-servidor que exercita transmissão unidirecional e comunicação do tipo requisição-resposta sobre o protocolo TCP, por meio de programação com _sockets Unix_ (Trabalho Prático 3 da disciplina de Redes de Computadores I - DCOMP - UFSJ).

# Requisitos (Geração dos Arquivos e Gráficos)

- [Python](https://python.org) 3.6 ou superior

- Gerenciador de pacotes [_pip_](https://pip.pypa.io/en/stable/installation/)

       python -m ensurepip --upgrade
       
- Biblioteca [PyCryptodome](https://pycryptodome.readthedocs.io/en/latest/src/introduction.html)
 
       pip install pycryptodomex
       
- Biblioteca [Matplotlib](https://matplotlib.org/)
 
       pip install matplotlib

# Compilação (Servidor e Cliente)
     
       make

# Execução (Servidor e Cliente)
     
       make run
       
# Observações

- O servidor deve ser executado antes do cliente;
- Os Makefiles (servidor e cliente) podem e devem ser alterados para teste;
- Formato de execução (cliente): `./client <ip> <número da porta> <nome do arquivo> <tamanho do buffer>`;
- Formato de execução (servidor): `./server <número da porta> <tamanho do buffer>`;
- O número da porta deve ser o mesmo para casos de execução em _localhost_ (127.0.0.1);
- A capacidade de _buffer_ suportada até o momento varia somente de 2 a 2048 _Bytes_.
