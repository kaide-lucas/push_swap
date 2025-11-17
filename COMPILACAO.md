# 🛠️ GUIA DE COMPILAÇÃO - PUSH_SWAP

## 🚀 Compilação Básica (SEM visualizador)

### 1️⃣ **Compilar tudo do zero**
```bash
make
```
**O que faz:**
- Compila a libft primeiro
- Compila todos os arquivos .c → .o
- Linka tudo criando o executável `push_swap`

**Resultado:** Cria o arquivo `push_swap` (executável)

---

### 2️⃣ **Recompilar do zero (limpa antes)**
```bash
make re
```
**O que faz:**
- Remove todos os arquivos compilados (.o)
- Remove o executável
- Recompila tudo novamente

**Use quando:** Fizer mudanças e quiser garantir recompilação completa

---

### 3️⃣ **Apenas limpar arquivos objeto**
```bash
make clean
```
**O que faz:**
- Remove arquivos .o
- Mantém o executável `push_swap`

---

### 4️⃣ **Limpar tudo**
```bash
make fclean
```
**O que faz:**
- Remove arquivos .o
- Remove executável `push_swap`
- Remove `libft.a`

---

## 📋 Processo de Compilação Detalhado

### Passo a passo do `make`:

```
1. Compila LIBFT
   └─> cd libft && make
       └─> Cria libft.a

2. Compila cada arquivo .c → .o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c main.c -o main.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c parse_input.c -o parse_input.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c is_valid_input.c -o is_valid_input.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c stack_utilis.c -o stack_utilis.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c cheker.c -o cheker.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c push.c -o push.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c swap.c -o swap.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c rotate.c -o rotate.o
   ├─> gcc -Wall -Wextra -Werror -Ilibft -c reverse.c -o reverse.o
   └─> gcc -Wall -Wextra -Werror -Ilibft -c push_swap.c -o push_swap.o

3. Linka tudo
   └─> gcc -Wall -Wextra -Werror -Ilibft main.o parse_input.o ... libft/libft.a -o push_swap

4. Pronto!
   └─> Executável 'push_swap' criado ✓
```

---

## 🎯 Comandos Rápidos

### Compilar e testar:
```bash
# Compilar
make

# Testar com 3 números
./push_swap 3 2 1

# Contar operações
./push_swap 3 2 1 | wc -l

# Testar com 5 números
./push_swap 5 4 3 2 1

# Testar com números aleatórios (100)
shuf -i 1-100 -n 100 | tr '\n' ' ' | xargs ./push_swap | wc -l
```

---

## 🔄 Workflow Típico

### Durante desenvolvimento:
```bash
# 1. Editar código
vim main.c

# 2. Recompilar
make

# 3. Testar
./push_swap 3 2 1

# 4. Se tiver erro, ver detalhes
make re  # Força recompilação completa
```

### Entregar projeto limpo:
```bash
# Remover todos os compilados
make fclean

# Verificar o que vai ser enviado
git status

# Adicionar apenas código fonte
git add *.c *.h Makefile libft/
```

---

## 📦 Estrutura de Arquivos Após Compilação

### ANTES do `make`:
```
push_swap/
├── main.c
├── parse_input.c
├── push_swap.c
├── ... (outros .c)
├── push_swap.h
├── Makefile
└── libft/
    ├── ft_atoi.c
    ├── ... (outros .c)
    ├── libft.h
    └── Makefile
```

### DEPOIS do `make`:
```
push_swap/
├── main.c
├── main.o          ← NOVO (arquivo objeto)
├── parse_input.c
├── parse_input.o   ← NOVO
├── push_swap.c
├── push_swap.o     ← NOVO
├── ... (outros .c/.o)
├── push_swap       ← NOVO (executável) ★
├── push_swap.h
├── Makefile
└── libft/
    ├── ft_atoi.c
    ├── ft_atoi.o   ← NOVO
    ├── ... (outros .c/.o)
    ├── libft.a     ← NOVO (biblioteca)
    ├── libft.h
    └── Makefile
```

---

## ⚠️ Erros Comuns e Soluções

### Erro 1: "make: *** No rule to make target"
```bash
# Solução: Verificar Makefile
make fclean
make
```

### Erro 2: Warnings virando erros (-Werror)
```bash
# Ver warnings
gcc -Wall -Wextra main.c

# Corrigir o código e recompilar
make re
```

### Erro 3: "undefined reference to ft_..."
```bash
# Libft não compilada
cd libft
make
cd ..
make
```

### Erro 4: "permission denied: ./push_swap"
```bash
# Dar permissão de execução
chmod +x push_swap
./push_swap 1 2 3
```

---

## 🧪 Testando Compilação

### Teste completo:
```bash
# 1. Limpar tudo
make fclean

# 2. Verificar que não tem executável
ls push_swap  # Deve dar erro "No such file"

# 3. Compilar
make

# 4. Verificar que criou
ls -lh push_swap  # Deve mostrar o arquivo

# 5. Testar
./push_swap 3 2 1  # Deve imprimir operações

# 6. Sucesso! ✅
```

---

## 💡 Flags do GCC Explicadas

```bash
gcc -Wall -Wextra -Werror -Ilibft -c main.c -o main.o
    │     │       │        │        │          │
    │     │       │        │        │          └─> Arquivo de saída
    │     │       │        │        └─> Apenas compilar (não linkar)
    │     │       │        └─> Incluir headers da libft
    │     │       └─> Warnings viram erros
    │     └─> Warnings extras
    └─> Todos os warnings
```

---

## 🎓 Diferença: Compilação vs Linkagem

### Compilação (.c → .o):
```bash
gcc -c main.c -o main.o
```
- Transforma código fonte em código objeto
- Um arquivo .o para cada .c
- Ainda não é executável

### Linkagem (.o → executável):
```bash
gcc main.o parse.o ... libft.a -o push_swap
```
- Junta todos os .o e bibliotecas
- Resolve referências entre arquivos
- Cria o executável final

---

## 📊 Comparação de Comandos

| Comando | Limpa .o? | Limpa executável? | Recompila? |
|---------|-----------|-------------------|------------|
| `make` | ❌ | ❌ | ✅ (só mudanças) |
| `make clean` | ✅ | ❌ | ❌ |
| `make fclean` | ✅ | ✅ | ❌ |
| `make re` | ✅ | ✅ | ✅ (tudo) |

---

## 🚀 TL;DR - Comandos Essenciais

```bash
# Compilar
make

# Executar
./push_swap 3 2 1

# Recompilar tudo
make re

# Limpar tudo
make fclean

# Compilar + Testar
make && ./push_swap 5 4 3 2 1 | wc -l
```

---

## 🎯 IMPORTANTE: NÃO Compilar o Visualizador

O visualizador está em `push_swap_visualizer/` e é **separado**.

**Para compilar APENAS o push_swap:**
```bash
# Na raiz do projeto (não entre na pasta do visualizador)
cd /home/kaide/projetos/push_swap
make
```

**Para NÃO mexer no visualizador:**
- Não entre na pasta `push_swap_visualizer/`
- Não rode `cmake` ou `make` dentro dela
- Use apenas `make` na raiz

**O visualizador é opcional!** Seu projeto funciona sem ele.

---

## ✅ Checklist Rápido

```
□ Estou na pasta correta? (raiz do push_swap)
□ Tenho o Makefile?
□ Tenho a pasta libft?
□ Rodei 'make'?
□ Apareceu o arquivo 'push_swap'?
□ Consigo rodar './push_swap 1 2 3'?
□ Funcionou? ✅ Sucesso!
```

---

**Resumo:** Na raiz do projeto, rode `make` e pronto! Não precisa mexer no visualizador para compilar o push_swap. 🎉
