NAME = ush

LIB = ./libmx/libmx.a

INC = ./inc/ush.h

HEAD = ush.h

SRCOUT = main.c \
        mx_init_struct.c \
        mx_replace_cmd.c \
        mx_malloc_err.c \
        mx_split_line.c \
        mx_split_backup.c \
        mx_loop.c \
        mx_command_pars.c \
        mx_simple_commands.c \
        mx_streams.c \
        mx_check_slash.c \
        mx_check_env.c \
        mx_get_env.c \
        mx_complex_cmd.c \

SRCS = $(addprefix ./src/, $(SRCOUT))

OBJOUT = $(SRCOUT:%.c=%.o)

CFLAG = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install

install:
	@make install -C libmx
	@cp $(SRCS) .
	@cp $(INC) .
	@cp $(LIB) .
	@clang $(CFLAGS) -c $(SRCOUT) -I $(HEAD)
	@clang $(CFLAGS) $(LIB) $(OBJOUT) -o $(NAME)
	@mkdir -p obj
	@mv $(OBJOUT) ./obj

clean:
	@rm -rf $(OBJOUT) $(SRCOUT) $(HEAD) obj
	@make uninstall -C libmx

uninstall: clean
	@make clean -C libmx
	@rm -rf $(NAME)
	@rm -rf libmx.a

reinstall: uninstall install
