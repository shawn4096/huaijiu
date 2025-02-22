// more.c

#include <ansi.h>

nosave string *text;
nosave int size;
nosave int width;

private void more(string cmd, int line)
{
	int i;

	write(REST+ESC+"[K");
	switch(cmd) {
		case "q":
			return;
		case "b":
			line -= 46;
			if (line < 1) line = 1;
		default:
			for (i=line + 23; line <= size && line < i; line++) {
				if (size > 23)
					write(sprintf("%*d: ", width, line));
				write(sprintf("%s\n", text[line-1]));
			}
			if (line > size) return;
	}
	write(sprintf(SAVEC+"== 还剩 "HIY"%*d"NOR" 行 == (ENTER 继续下一页，q 离开，b 前一页)"+ESC+"[A",
		width, size - line + 1)
	);
	input_to((:more:), 3, line);
}

void start_more(string msg)
{
	if (!stringp(msg)) return;
	write("\n"+SAVEC);
	text = explode(msg, "\n");
	size = sizeof(text);
	width = strlen(size+"");
	more("", 1);
}
