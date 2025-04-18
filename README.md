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
### Tabela `usuarios`  
```sql
CREATE TABLE usuarios (
    id INT AUTO_INCREMENT PRIMARY KEY,
    nome VARCHAR(50) NOT NULL,
    senha VARCHAR(50) NOT NULL
);
``` 
<!--verificar se precisa de USE -->
### Tabela `usuarios` 
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
    -
- Configuração do banco:
    Crie o banco diario_leitura e as tabelas acima.