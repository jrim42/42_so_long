NAME		=	so_long

RED			=	\033[0;31m
GRN			= 	\033[0;32m
YLW			=	\033[0;33m
BLU			= 	\033[0;36m
DFT			= 	\033[0;37m

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra
AR			=	ar rcs
RM			=	rm -f

LIB_DIR		=	./libft/
LIB_NAME	=	libft.a
LIBS		=	$(addprefix $(LIB_DIR), $(LIB_NAME))
GNL_DIR		=	./gnl/
GNL_NAME	=	gnl.a
GNLS		=	$(addprefix $(GNL_DIR), $(GNL_NAME))
MLX_DIR		=	./mlx/

MLX_FLAGS	=	-L./mlx -lmlx -framework OpenGL -framework Appkit

SRC			=	src/so_long.c\
				src/_map_read.c\
				src/_map_check.c\
				src/_map_gen.c\
				src/_init.c\
				src/_move.c\
				src/_collec.c\
				src/_utils.c\
				
OBJ			=	$(SRC:.c=.o)

all : $(NAME) 

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ)
	@$(MAKE) -C $(LIB_DIR)
	@$(MAKE) -C $(GNL_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) -o $(NAME) $(OBJ) $(LIBS) $(GNLS) $(MLX_FLAGS)
	@echo "$(NAME) is $(GRN)ready$(DFT)"

clean :
	@$(MAKE) -C $(LIB_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@$(RM) $(OBJ)
	@echo "$(RED)cleaned$(DFT)"

fclean : clean
	@$(MAKE) -C $(LIB_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(RED)fcleaned$(DFT)"

re : clean all

PHONY	: all clean fclean re
