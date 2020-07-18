NAME = ush

LIB = ./libmx/libmx.a

INC = ./inc/ush.h

HEAD = ush.h

SRC = src

SRCOUT = main.c \
		 mx_get_commands.c \
		 mx_config_init.c \
		 mx_get_term_params.c \
		 mx_loop.c \
		 mx_raw_mode_on.c \
		 mx_get_cursor.c \
		 mx_refresh_line.c \
		 mx_refresh_screen.c \
		 mx_cooked_mode_on.c \
		 mx_process_key.c \
		 mx_qoutes_handling.c \
		 mx_editor_processing.c \
		 mx_read_key.c \
		 mx_arrows_motion.c \
		 mx_die.c \
		 mx_itoa.c \
		 mx_strdup.c \
		 mx_strcpy.c \
		 mx_strndup.c \
		 mx_strncpy.c \
		 mx_strnew.c \
		 mx_return_action.c \
		 mx_tab_action.c \
		 mx_backspace_action.c \
		 mx_clear_screen.c \
		 mx_free_assumptions.c \
		 mx_set_cursor.c \
		 mx_hist_init.c \
		 mx_history.c \
		 mx_clear.c \
		 mx_sighandler.c \
		 mx_help.c \

SRCS = $(addprefix ./src/, $(SRCOUT))

OBJOUT = $(SRCOUT:%.c=%.o)

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror

all: install

install:
	@make install -C libmx
	@cp $(SRCS) .
	@cp $(INC) .
	@cp $(LIB) .
	@clang $(CFLAGS) -c $(SRCOUT) -I $(HEAD)
	@clang -ltermcap $(CFLAGS) $(LIB) $(OBJOUT) -o $(NAME)
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
