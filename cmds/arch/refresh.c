// profile.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object *list, *inv;
	string file;
	int i, j;

	if (!arg) arg = me->query("cwf");
	if (!arg) return notify_fail("你要更新什么档案？\n");
	arg = resolve_path(me->query("cwd"), arg);
	if( !sscanf(arg, "%*s.c") ) arg += ".c"; 
	me->set("cwf", arg);

	list = objects();
	for (i=0;i<sizeof(list);i++) {
		if (!list[i]) continue;
		file = file_name(list[i]);
		if (!clonep(list[i])
		&& inherits(arg, list[i])) {
			j = sizeof(inv = all_inventory(list[i]));
			while (j--)
				if (userp(inv[j])) break;
			if (j >= 0) break;
			printf("%s %d\n", file, inherits(arg, list[i]));
			destruct(list[i]);
			if (file_size(file + ".c") > 0)
				catch(call_other(file, "???"));
		}
	}
	return 1;
}

int help (object me)
{
        write(@HELP
指令格式: refresh
HELP
);
        return 1;
}
