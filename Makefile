# Configurações do compilador 
CXX       := g++
CXXFLAGS  := -Wall -Wextra -Werror -Iinclude -std=c++17

# Configurações do arquivador para criar a biblioteca estática 
AR        := ar
ARFLAGS   := rcs

# Pastas
SRCDIR    := source
INCDIR    := include
TESTDIR   := tests
BUILDDIR  := build

# Arquivo de biblioteca final
LIB_NAME    := ifnum
LIBTARGET   := $(BUILDDIR)/lib$(LIB_NAME).a # Biblioteca deve ter nome com prefixo 'lib'

# Coleta todos os arquivos fonte para a biblioteca
LIB_SRCS  := $(wildcard $(SRCDIR)/*.cpp)
LIB_OBJS  := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(LIB_SRCS))

# Coleta os arquivos fonte dos testes (cada um com sua própria main())
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)

# Os nomes dos executáveis serão os mesmos dos arquivos de teste.
TEST_BINS := $(patsubst $(TESTDIR)/%.cpp, $(BUILDDIR)/%, $(TEST_SRCS))

# Alvo padrão: compilar a biblioteca e, em seguida, os testes
all: $(LIBTARGET)

# Alvo para gerar os executáveis de teste
tests: $(TEST_BINS)

# Compila a biblioteca estática a partir dos arquivos objeto
$(LIBTARGET): $(LIB_OBJS)
	@echo "Arquivando biblioteca -> $@"
	$(AR) $(ARFLAGS) $@ $^

# Regra para compilar arquivos fonte da biblioteca em arquivos objeto
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	@echo "Compilando $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para compilar cada executável de teste
$(BUILDDIR)/%: $(TESTDIR)/%.cpp $(LIBTARGET) | $(BUILDDIR)
	@echo "Linkando $< -> $@"
	$(CXX) $(CXXFLAGS) $< -L$(BUILDDIR) -l$(LIB_NAME) -o $@

# Cria o diretório build, se não existir
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Regra para gerar a documentação com Doxygen
docs:
	@echo "Gerando documentação..."
	doxygen Doxyfile

# Limpezas dos artefatos de compilação
clean:
	@echo "Limpando..."
	find $(BUILDDIR) -maxdepth 1 -type f ! -name '.gitignore' -exec rm -f {} \;

.PHONY: all clean
