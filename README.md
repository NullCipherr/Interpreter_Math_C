# Interpreter Math C

Bem-vindo ao **Interpreter Math C**, um programa desenvolvido em C que avalia expressões matemáticas, manipula variáveis, suporta funções matemáticas e exibe um histórico dos cálculos realizados.

---

## 🚀 Funcionalidades

- **Cálculo de expressões matemáticas**:
  - Suporte a operações básicas: `+`, `-`, `*`, `/`, `^`, `%`.
  - Suporte a operadores lógicos: `&&` (AND lógico), `||` (OR lógico).
  - Cálculo de fatoriais usando `!`.
  
- **Suporte a funções matemáticas**:
  - `sin(x)`, `cos(x)`, `tan(x)`, `log(x)`, `sqrt(x)`.

- **Manipulação de variáveis**:
  - Definir variáveis: `x = 5`.
  - Usar variáveis em expressões: `x + 10`.

- **Histórico de cálculos**:
  - Exibir histórico.
  - Exportar histórico para um arquivo `.txt`.

- **Interface simples e amigável**:
  - Menus claros e comandos para interagir com o programa.

---

## 🖥️ Como Usar

### 🟢 Comandos Disponíveis:
- `q` ou `sair`: Finalizar o programa.
- `ajuda`: Exibir operadores e funções disponíveis.
- `limpar`: Limpar a tela.
- `historico`: Exibir cálculos realizados anteriormente.
- `exportar`: Salvar o histórico em um arquivo chamado `historico_calculos.txt`.

### 🟢 Exemplos de Uso:
1. Operações básicas:
   - `2 + 3 * 4`
   - `(2 + 3) * 4`
2. Funções matemáticas:
   - `sin(pi/2)`
   - `sqrt(16)`
3. Definir variáveis:
   - `x = 10`
   - `y = x + 5`
4. Usar constantes:
   - `pi * 2`
   - `e^2`

---

## 🧩 Estrutura do Código

### **Principais Componentes**
1. **Manipulação de pilha**:
   - Estruturas para gerenciar números e operadores.
2. **Histórico**:
   - Registra as últimas 10 expressões avaliadas e seus resultados.
   - Exporta o histórico para um arquivo.
3. **Variáveis**:
   - Armazena até 10 variáveis.
   - Suporte a operações envolvendo variáveis.
4. **Funções matemáticas**:
   - Inclui suporte a funções como seno, cosseno, logaritmo, entre outras.

---

## 📄 Exportação de Histórico
O histórico de cálculos pode ser salvo no arquivo `historico_calculos.txt` para referência futura. O arquivo conterá todas as expressões calculadas junto com seus resultados.

---

## ⚙️ Requisitos
- Compilador C (ex.: GCC).
- Sistema operacional Windows, Linux ou macOS.

---

## 🛠️ Compilação e Execução

### **Compilar**:
```bash
gcc -o interpreter_math_c main.c -lm
