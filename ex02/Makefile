NAME		= PmergeMe
SRCS		= main.cpp PmergeMe.cpp
INCS		= PmergeMe.hpp
OBJDIR		= .obj
OBJS		= $(SRCS:%.cpp=$(OBJDIR)/%.o)
RM			= rm -rf
CPPFLAGS	= -Wall -Wextra -Werror -std=c++98 -g3
CPPC		= c++

$(OBJDIR):
	@mkdir $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS) $(INCS)
	$(CPPC) $(CPPFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: %.cpp
	$(CPPC) $(CPPFLAGS) -o $@ -c $^

all: $(NAME)

clean:
	@echo removing $(OBJS)
	@$(RM) $(OBJS) $(OBJDIR)

fclean: clean
	@echo removing $(NAME)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
