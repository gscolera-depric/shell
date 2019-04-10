#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# include "libft.h"
# include "ft_printf.h"
# include <limits.h>
# include <termios.h>
# include <termcap.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <pwd.h>
# include <dirent.h>
# include <fcntl.h>

# define TERM_ACTION(x)	tputs(sh->rd.esc[x], fileno(stdin), ft_putchar)
# define QUOTE(c)		(c == '\'' || c == '\"')
# define NQT(f)			(!(f & SQT) && !(f & DQT))
# define BSLASH(c)		(c == '\\')
/*
 ************DEFAULT_SETTINGS****************************** 
 */
# define DEFAULT_TERM	"xterm-256color"
# define CONFIG_FILE	"config"
# define HISTORY_SIZE	1000
# define HOST_NAME		255
# define BUFF_SIZE		100
# define VAR_NAME_MAX	512
/*
 ************KEYMAP**************************************** 
 */

# define KEYUP			1792833
# define KEYDOWN		1792834
# define KEYRIGHT		1792835
# define KEYLEFT		1792836
# define KEYDEL			458961790
# define KEYHOME		1792840
# define KEYEND			1792838
# define KEYENTER		10
# define KEYTAB			9
# define KEYESC			27
# define KEYBS			127
# define KEYCRTLD		4
# define SHKEYLEFT		30078481936964
# define SHKEYRIGHT		30078481936963
# define SHKEYUP		30078481936961
# define SHKEYDOWN		30078481936962
/*
 **************FLAGS****************************************
 */
# define READING		(1 << 0)
# define BSL			(1 << 1)
# define SQT			(1 << 2)
# define DQT			(1 << 3)
# define SPC			(1 << 4)
# define CHOOSING		(1 << 5)
/*
 *************ACCES FLAGS**********************************
 */
# define FILE_EXISTS	0
# define FILE_EXEC		1
# define FILE_WR		2
# define FILE_RD		3
# define FILE_RDWR		4

enum					s_options
{
	RIGHT,
	LEFT,
	UPB,
	DOWN,
	DEL,
	CLR,
	SAVEC,
	RSRC,
	CD,
	TOTAL
};

typedef struct			s_coordinate
{
	short				x;
	short				y;
}						t_coordinate;

typedef struct			s_buffer
{
	char				*data;
	size_t				size;
	size_t				id;
	struct s_buffer		*prev;
	struct s_buffer		*next;
}						t_bufflist;

typedef struct			s_settings
{
	struct termios		term_default;
	struct termios		term_shell;
	t_coordinate		window_size;
	char				promt[LINE_MAX];
	size_t				history_buffsize;
	size_t				promt_len;
	uid_t				uid;
}						t_settings;

typedef	struct			s_reader
{
	t_bufflist			*history;
	t_bufflist			*buffptr;
	t_bufflist			*buffend;
	char				buffer[LINE_MAX];
	char				*esc[TOTAL];
	size_t				il;
	size_t				ic;
	size_t				buff_size;
	t_coordinate		crs;
}						t_reader;

typedef struct			s_cmplt
{
	char				*option;
	struct s_cmplt		*next;
}						t_cmplt;

typedef struct			s_command
{
	char				*cmd;
	char				**argv;
	struct s_command	*next;
}						t_command;

typedef struct			s_shell
{
	t_settings			settings;
	t_reader			rd;
	t_command			*cmd_list;
	t_cmplt				*cmp_list;
	t_cmplt				*act_list;
	char				cmp[LINE_MAX];
	char				*binary;
	char				*input;
	char				**path;
	char				**env;
	size_t				flags;
}						t_shell;

#endif
