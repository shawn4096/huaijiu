// by Tie@fy3 hehe
inherit F_CLEAN_UP;
object find_env(object ob);

int main(object me, string str)
{
string output = "";
        me =this_player();
	
        if(!str) return notify_fail("ָ���ʽ: locate <��Ʒ>\n");
      if( me->is_busy() )
      return notify_fail("����æ���أ�\n");  
	output = ("/adm/daemons/questd")->locate_obj(str);
	write(output);
me->start_busy(1);
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ: locate <��Ʒ>

���ָ����������֪ʹ����Ʒ�Ĵ��λ�á�


HELP
	);
	return 1;
}
