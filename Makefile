PROJECT 	:= minishell 
CC 			:= gcc
NAME		:= minishell
CFLAGS		:= -Wextra -Wall -Werror #-g -fsanitize=address
MLX42FLAGS	:= -ldl -lglfw -pthread -lm

LIBFT		:= ./lib/libft/libft.a
INCLUDE 	:= -I ./includes -I ./lib/MLX42/include

SRC			:= ./src/

OBJ_DIR 	:= obj

OBJ 		:= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE 	:= \033[96m
RESET   := \033[0m

all: $(NAME)

$(NAME): $(MLX42) $(LIBFT) $(OBJ)
	@echo "Compiling $(YELLOW)$(PROJECT)$(RESET) with $(BLUE)$(CFLAGS)$(RESET)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MLX42) $(MLX42FLAGS) $(LIBFT)
	@echo "$(GREEN)Done! ✅$(RESET)"
	@echo "$(RED)------------------------------$(RESET)"

$(LIBFT):
	@$(MAKE) --no-print-directory -C ./lib/libft

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory clean -C ./lib/libft
	@rm -rf ./lib/MLX42/build

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) --no-print-directory fclean -C ./lib/libft
	@rm -f $(MLX42)
	@rm -rf ./lib/MLX42/build

re: clean all

.PHONY: all, clean, fclean, re