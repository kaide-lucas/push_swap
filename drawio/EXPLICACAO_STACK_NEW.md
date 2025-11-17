# 📚 EXPLICAÇÃO DETALHADA: `stack_new()`

## 🎯 Propósito

A função `stack_new()` é responsável por **criar um novo nó** da lista encadeada que representa a stack (pilha).

---

## 📝 Código

```c
t_stack *stack_new(int value)
{
    t_stack *new;

    new = malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    new->index = -1;
    new->next = NULL;

    return (new);
}
```

---

## 🔍 Análise Linha por Linha

### 1️⃣ **Assinatura da Função**
```c
t_stack *stack_new(int value)
```

**Entrada:** 
- `int value` - O valor numérico a ser armazenado no nó

**Saída:**
- `t_stack *` - Ponteiro para o novo nó criado
- `NULL` - Se a alocação de memória falhar

---

### 2️⃣ **Declaração de Variável**
```c
t_stack *new;
```

Declara um ponteiro `new` que irá apontar para o novo nó alocado.

---

### 3️⃣ **Alocação de Memória**
```c
new = malloc(sizeof(t_stack));
```

**O que faz:**
- Aloca memória suficiente para armazenar uma estrutura `t_stack`
- `sizeof(t_stack)` calcula quantos bytes são necessários
- `malloc()` retorna um ponteiro para o bloco de memória alocado

**Tamanho típico:**
```c
sizeof(t_stack) = sizeof(int)         // value   → 4 bytes
                + sizeof(int)         // index   → 4 bytes  
                + sizeof(t_stack*)    // next    → 8 bytes (64-bit)
                = 16 bytes (com padding)
```

---

### 4️⃣ **Verificação de Erro**
```c
if (!new)
    return (NULL);
```

**O que verifica:**
- Se `malloc()` falhou (retornou `NULL`)
- Isso pode acontecer se não há memória disponível

**Por que é importante:**
- Evita tentar acessar memória inválida
- Permite que a função chamadora trate o erro
- Boa prática de programação defensiva

---

### 5️⃣ **Inicialização: Value**
```c
new->value = value;
```

**O que faz:**
- Armazena o valor passado como parâmetro no campo `value` do nó
- Este é o número original (ex: 42, 21, 84)

**Exemplo:**
```c
t_stack *node = stack_new(42);
// node->value agora é 42
```

---

### 6️⃣ **Inicialização: Index**
```c
new->index = -1;
```

**O que faz:**
- Inicializa o índice como `-1` (valor sentinela)
- `-1` indica que o índice ainda não foi calculado

**Quando é alterado:**
- Mais tarde pela função `normalize_values()`
- Será substituído por 0, 1, 2, 3... (posição relativa ordenada)

**Por que -1:**
```c
// -1 é um valor impossível para índice válido
// Facilita debug: se ver -1, sabe que não foi normalizado
```

---

### 7️⃣ **Inicialização: Next**
```c
new->next = NULL;
```

**O que faz:**
- Define o ponteiro `next` como `NULL`
- Indica que este nó não aponta para nenhum outro (ainda)

**Significado:**
- `NULL` = "fim da lista" ou "nó isolado"
- Será atualizado quando o nó for adicionado à stack

---

### 8️⃣ **Retorno**
```c
return (new);
```

**O que retorna:**
- Ponteiro para o novo nó completamente inicializado
- Pronto para ser adicionado à stack

---

## 🎨 Visualização da Memória

### Antes de `malloc()`:
```
new → [????]  (não inicializado, lixo de memória)
```

### Depois de `malloc()`:
```
new → [Bloco de 16 bytes alocado no heap]
       ┌──────────────────────┐
       │ value:  [lixo]       │
       │ index:  [lixo]       │
       │ next:   [lixo]       │
       └──────────────────────┘
```

### Depois da inicialização completa:
```
new → [Nó completamente inicializado]
       ┌──────────────────────┐
       │ value:  42           │
       │ index:  -1           │
       │ next:   NULL         │
       └──────────────────────┘
```

---

## 🔄 Como é Usado no Projeto

### No `parse_arguments()`:
```c
t_stack *parse_arguments(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *node;
    int num;
    int i;

    stack_a = NULL;
    i = 1;
    while (i < argc)
    {
        if (!safe_atoi(argv[i], &num))
            return (error_exit(&stack_a));
        
        node = stack_new(num);  // ← AQUI: Cria novo nó
        
        if (!node)              // ← Verifica se criou com sucesso
            return (error_exit(&stack_a));
        
        stack_add_back(&stack_a, node);  // Adiciona à lista
        i++;
    }
    return (stack_a);
}
```

---

## 🎯 Exemplo Completo

### Entrada:
```bash
./push_swap 42 21 84
```

### Processo:
```c
// Iteração 1: argv[1] = "42"
num = 42;
node1 = stack_new(42);
// node1: {value: 42, index: -1, next: NULL}

// Iteração 2: argv[2] = "21"
num = 21;
node2 = stack_new(21);
// node2: {value: 21, index: -1, next: NULL}

// Iteração 3: argv[3] = "84"
num = 84;
node3 = stack_new(84);
// node3: {value: 84, index: -1, next: NULL}
```

### Resultado após `stack_add_back()`:
```
stack_a → [42, -1] → [21, -1] → [84, -1] → NULL
          │value │    │value │    │value │
          │index │    │index │    │index │
```

### Depois de `normalize_values()`:
```
stack_a → [42, 1] → [21, 0] → [84, 2] → NULL
          │        │         │
          │        └─ menor valor → índice 0
          └─ valor médio → índice 1
```

---

## ⚠️ Gestão de Memória

### ✅ Alocação:
```c
t_stack *node = stack_new(42);  // Memória alocada no HEAP
```

### ✅ Liberação:
```c
// Feita em stack_clear()
void stack_clear(t_stack **stack)
{
    t_stack *temp;
    
    while (*stack)
    {
        temp = (*stack)->next;
        free(*stack);  // ← Libera cada nó
        *stack = temp;
    }
}
```

### ❌ Memory Leak (se não liberar):
```c
// ERRADO: Não chamar stack_clear()
stack_new(42);  // Memória alocada...
// ... programa termina sem free() → LEAK!
```

---

## 🧪 Teste Mental

### Cenário:
```c
t_stack *a = stack_new(100);
t_stack *b = stack_new(200);
```

### Resultado:
```
Memória:
┌─────────────┐         ┌─────────────┐
│ a           │         │ b           │
├─────────────┤         ├─────────────┤
│ value: 100  │         │ value: 200  │
│ index: -1   │         │ index: -1   │
│ next: NULL  │         │ next: NULL  │
└─────────────┘         └─────────────┘
    ↑                       ↑
    a                       b
```

---

## 📊 Comparação com Outras Abordagens

### ❌ SEM verificação de erro:
```c
t_stack *stack_new_UNSAFE(int value)
{
    t_stack *new = malloc(sizeof(t_stack));
    // E se malloc falhar? SEGFAULT!
    new->value = value;
    return (new);
}
```

### ❌ SEM inicialização completa:
```c
t_stack *stack_new_INCOMPLETE(int value)
{
    t_stack *new = malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    // index e next não inicializados → comportamento indefinido!
    return (new);
}
```

### ✅ CORRETO (seu código atual):
```c
t_stack *stack_new(int value)
{
    t_stack *new = malloc(sizeof(t_stack));
    if (!new)
        return (NULL);
    new->value = value;
    new->index = -1;      // ✓ Inicializado
    new->next = NULL;     // ✓ Inicializado
    return (new);
}
```

---

## 💡 Conceitos-Chave

| Conceito | Explicação |
|----------|------------|
| **malloc** | Aloca memória dinamicamente no heap |
| **sizeof** | Calcula tamanho em bytes de um tipo |
| **Ponteiro** | Endereço de memória onde o nó está |
| **NULL** | Ponteiro para "nada" (endereço 0) |
| **Heap** | Área de memória para alocação dinâmica |
| **-1** | Valor sentinela (indica "não definido") |

---

## 🎓 Perguntas e Respostas

### Q: Por que retornar ponteiro e não a estrutura?
**A:** Porque a estrutura é alocada no heap. Retornar cópia seria ineficiente e perderia o encadeamento.

### Q: O que acontece se malloc falhar?
**A:** Retorna `NULL`, e `parse_arguments()` trata o erro chamando `error_exit()`.

### Q: Por que index começa em -1?
**A:** Para diferenciar de índice 0 (válido). -1 = "ainda não normalizado".

### Q: Posso modificar o nó depois de criado?
**A:** Sim! Os campos são mutáveis. `normalize_values()` altera `index` mais tarde.

### Q: O que acontece se não chamar free()?
**A:** Memory leak. A memória fica ocupada até o programa terminar.

---

## 🚀 Resumo

**TL;DR:**
```c
stack_new(42) → Aloca memória
             → Inicializa {value: 42, index: -1, next: NULL}
             → Retorna ponteiro para o novo nó
             → NULL se falhar
```

**3 responsabilidades:**
1. 🏗️ **Alocar** memória
2. 🎨 **Inicializar** campos
3. ✅ **Validar** sucesso

**Usado para:** Criar cada nó da lista encadeada que representa a stack.

---

**Próximos passos:** O nó criado será passado para `stack_add_back()` para ser conectado à lista! 🔗
