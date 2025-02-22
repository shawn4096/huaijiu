// alias.c
// From ES2
// Modified for XKX by Xiang (12/15/95)

#include <ansi.h>

#define MAX_REPEAT 40
#define MAX_ALIASES 30
#define HISTORY_BUFFER_SIZE 10

mapping alias;

nosave string *history;
nosave int last_cmd, repeat_cnt = 0, last_time = 0;

string process_input(string str)
{
	string *args, cmd, argstr;
	int i, j;
	object me = this_object();

	if (!living(me) && !wizardp(me)) return "";
	if (in_edit() || in_input()) return "";
	for (i=0; i<strlen(str); i++)
		if (str[i]!=' ') {str = str[i..<1]; break;}
	if (str == "") return str;
	if (++repeat_cnt > MAX_REPEAT) {
		if (last_time == time()) {
			mixed busy;

			me->add_busy(1);
			busy = me->query_busy();
			if (intp(busy) && !(busy % 5))
				tell_object(me, "你因为滥用指令，将有" + busy*2 + "秒不能动弹。\n");
			return "";
		}
		repeat_cnt = 0;
		last_time = time();
	}

	if (!wizardp(me)) {
		if (me->query("eff_jing") + me->query_temp("apply/jing") < 0
		|| me->query("eff_qi") + me->query_temp("apply/qi") < 0
		|| me->query("eff_jingli") + me->query_temp("apply/jingli") < 0) {
			tell_object(me, "你马上要死亡了，不能做任何事情。\n");
			return "";
		}
		if (me->query("jing") < 0
		|| me->query("qi") < 0
		|| me->query("jingli") < 0) {
			tell_object(me, "你马上要昏迷了，不能做任何事情。\n");
			return "";
		}
	}

	if (me->query_temp("big5")) str = "/adm/daemons/gb_b5d"->b5_gb(str);

	if( str[0]=='!' && str[0..2]!="!!!") {
		if( pointerp(history) && sizeof(history) ) {
			if( sscanf(str, "!%d", i) )
				str = (string)history[(HISTORY_BUFFER_SIZE + last_cmd - i) % HISTORY_BUFFER_SIZE];
			else
				str = history[last_cmd];
		} else
			return "";
	} else {
		if( !pointerp(history) ) history = allocate(HISTORY_BUFFER_SIZE);
		last_cmd = (last_cmd + 1) % HISTORY_BUFFER_SIZE;
		history[last_cmd] = str;
	}

	if (str[0]=='\'') str = "say " + str[1..<1];
	if( mapp(alias) ) {
		if( !undefinedp(alias[str]) && str != "quit")
			str = replace_string( alias[str], "$*", "" );
		else if( sscanf(str, "%s %s", cmd, argstr)==2 && !undefinedp(alias[cmd]) && cmd != "quit") {
			str = alias[cmd];
			args = explode(argstr, " ");
			if( (j = sizeof(args)) )
				for(i=0; i<j; i++)
					str = replace_string( str, "$" + (i+1), args[i] );
			str = replace_string( str, "$*", argstr );
		}
	}

	return (string)ALIAS_D->process_global_alias(str, me);
}

int set_alias(string verb, string replace)
{
	if( !replace ) {
		if( mapp(alias) ) map_delete(alias, verb);
		return 1;
	} else {
		if (!mapp(alias)) alias = ([]);
		if (undefinedp(alias[verb]) && sizeof(alias) >= MAX_ALIASES)
			return notify_fail("您设定的 alias 太多了，请先删掉一些不常用的。\n");
		alias[verb] = replace;
		return 1;
	}
}

mapping query_all_alias()
{
	return alias;
}
