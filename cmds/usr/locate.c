// by Tie@fy3 hehe
inherit F_CLEAN_UP;
object find_env(object ob);

int main(object me, string str)
{
string output = "";
        me =this_player();
	
        if(!str) return notify_fail("指令格式: locate <物品>\n");
      if( me->is_busy() )
      return notify_fail("你正忙着呢！\n");  
	output = ("/adm/daemons/questd")->locate_obj(str);
	write(output);
me->start_busy(1);
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式: locate <物品>

这个指令是用来得知使命物品的大概位置。


HELP
	);
	return 1;
}
