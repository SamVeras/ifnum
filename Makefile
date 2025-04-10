# Configurações do compilador 
CXX       := g++
CXXFLAGS  := -Wall -Wextra -Werror -Iinclude -std=c++17

# Configurações do arquivador para criar a biblioteca estática 
AR        := ar
ARFLAGS   := rcs

# Pastas
SRCDIR    := source
INCDIR    := include
DOCSDIR   := docs
TESTDIR   := tests
BUILDDIR  := build

# Arquivo de biblioteca final
LIB_NAME    := ifnum
LIBTARGET   := $(BUILDDIR)/lib$(LIB_NAME).a # Biblioteca deve ter nome com prefixo 'lib'

# Coleta todos os arquivos fonte para a biblioteca
LIB_SRCS  := $(wildcard $(SRCDIR)/*.cpp)
LIB_OBJS  := $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(LIB_SRCS))

# Coleta todos os arquivos de cabeçalho para a biblioteca
LIB_HDRS  := $(wildcard $(INCDIR)/*.hpp)
LIB_TPPS  := $(wildcard $(INCDIR)/*.tpp)

# Coleta os arquivos fonte dos testes (cada um com sua própria main())
TEST_SRCS := $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJS := $(patsubst $(TESTDIR)/%.cpp, $(BUILDDIR)/%_test.o, $(TEST_SRCS))

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

# Regra para compilar os arquivos de teste em objetos
$(BUILDDIR)/%.test.o: $(TESTDIR)/%.cpp | $(BUILDDIR)
	@echo "Compilando teste $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para linkar os objetos de teste com a biblioteca e gerar os executáveis
$(BUILDDIR)/%: $(BUILDDIR)/%.test.o $(LIBTARGET) | $(BUILDDIR)
	@echo "Linkando teste -> $@"
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

# Limpezas da documentação
clean-docs:
	@echo "Limpando documentação..."
	find $(DOCSDIR) -type f ! -name '.gitignore' -exec rm -f {} \;
	find docs -type d -empty -delete

.PHONY: all docs clean clean-docs
