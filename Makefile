NAME	= plazza

GUI	= plazza_gui

SRCSFO	= sources/

INCSFO	= includes/

QTFO	= qt/

SRCS	= $(SRCSFO)main.cpp \
	  $(SRCSFO)ThreadPool.cpp \
	  $(SRCSFO)ProcessManager.cpp \
	  $(SRCSFO)Process.cpp \
	  $(SRCSFO)NamedPipe.cpp \
	  $(SRCSFO)Xor.cpp \
	  $(SRCSFO)AEncryptionMethod.cpp \
	  $(SRCSFO)Cesar.cpp \
	  $(SRCSFO)ProcessData.cpp \
	  $(SRCSFO)Parser.cpp \
	  $(SRCSFO)Log.cpp \
	  $(SRCSFO)BruteForcer.cpp

OBJS	= $(SRCS:.cpp=.o)
GCC	= clang++ -o

RM	= rm -rf

CFLAGS	= -Wall -Wextra -Werror -std=c++11 -I$(INCSFO)
LDFLAGS	= -lpthread -lboost_regex

all: $(NAME)

ui: $(GUI)

$(NAME): $(OBJS)
	$(GCC) $(NAME) $(OBJS) $(LDFLAGS)

$(GUI): $(OBJS)
	cd $(QTFO) && test -f Makefile && qmake-qt4 .
	cd $(QTFO) && make && cd ..
	mv $(QTFO)$(GUI) .

%.o: %.cpp
	$(GCC) $@ -c $< $(CFLAGS)

debug: CFLAGS = -Wall -Wextra -std=c++11 -I$(INCSFO) -g3
debug: $(NAME)

clean:
	-cd $(QTFO) && make clean && cd ..
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(GUI)

re: fclean all

.PHONY: all ui debug clean fclean re
