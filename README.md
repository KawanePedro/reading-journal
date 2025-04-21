# 📚 Reading Journal  

Um diário de leitura em C com MySQL para registrar livros lidos, autores, datas e notas.  

## 🛠️ Tecnologias  
- **Linguagem**: C  
- **Banco de dados**: MySQL  
- **Bibliotecas**: `mysql.h` (MySQL Connector/C)  

## ✨ Funcionalidades  
- ✅ **Cadastro de usuários** (nome e senha).  
- 🔑 **Login seguro** (validação no banco de dados).  
- 📖 **Registro de leituras**:  
  - Título, autor, data e nota (1-10).  
- 📋 **Listagem de leituras** por usuário.  

## 🗄️ Estrutura do Banco de Dados 
O software DBeaver foi usado para criação e visualização do banco de dados, porém outra aplicação pode ser usada, como também o terminal.
### Banco de dados `diario_leitura`
```sql
CREATE DATABASE diario_leitura;
```

### Tabela `usuarios`  
```sql
USE diario_leitura,

CREATE TABLE usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(50) NOT NULL,
    senha VARCHAR(50) NOT NULL
);
```
 
<!--verificar se precisa de USE -->
### Tabela `leituras` 
```sql
CREATE TABLE leituras (
    id INT AUTO_INCREMENT PRIMARY KEY,
    titulo VARCHAR(200) NOT NULL,
    autor VARCHAR(100) NOT NULL,
    data_leitura DATE NOT NULL,
    nota INT CHECK (nota BETWEEN 1 AND 10),
    usuario_id INT,
    FOREIGN KEY (usuario_id) REFERENCES usuarios(id)
);
``` 
 
 ### Como executar
- Pré-requisitos:
    - Instalar a API de C de MySQL (libmysqlclient), que está inclusa no MySQL 8.0: https://dev.mysql.com/downloads/installer/;
    - Configurar o MySQL no Code Blocks (IDE usada):
        -   Settings -> Compiler -> Search directories -> Compiler -> Adicionar pasta "include" do MySQL
        -   Settings -> Compiler -> Search directories -> Linker -> Adicionar pasta "lib" do MySQL
        -   Settings -> Compiler -> Linker settings -> Adicionar arquivo "libmysql.lib" da pasta "lib" do MySQL
    - Caso ocorra erro do arquivo "libcrypto-3-x64.dll" não foi encontrado, baixe a biblioteca OpenSLL versão 3 compatível com seu sistema (https://slproweb.com/products/Win32OpenSSL.html) e copie os arquivos "libcrypto-3-x64.dll" e "libssl-3-x64.dll" na pasta do seu projeto.