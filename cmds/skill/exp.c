#include <ansi.h>
#define X 5
#define Y 5
#define S 1

int help(object me)
{
	int y, x, lvl, exp, mylvl = me->query("max_pot")-101, start;
	string str;

	write("�ȼ��;���������ձ�\n");
	start = mylvl - X * Y / 2;
	if (start < 0)
		start = 0;
	for (y = 1; y <= Y; y++) {
		str = "";
		for (x = 0; x < X; x++) {
			lvl = (y + x * Y) * S - 1 + start;
			exp = lvl * lvl * lvl / 10;
			if (lvl > mylvl && lvl <= mylvl + S)
				str += HIY;
			str += sprintf("%3d %8d", lvl + 1, exp);
			if (lvl > mylvl && lvl <= mylvl + S)
				str += NOR;
			if (x < X-1)
				str += " | ";
		}
		write(str + "\n");
	}
	return 1;
}
