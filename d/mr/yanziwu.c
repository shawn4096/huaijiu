// /u/beyond/mr/yanziwu.c
// this is made by beyond
// update 1997.6.20
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "Ժ��");
	set ("long",@long
��������Ļ��������֮��, Ļ������Ϧ�մ�����ĺ���, �����ռ�ʽ΢, 
�������ȴһ��һ����⸴���ࡣ���书�������Ա�֮��, ��ʩ����, �˵�
ʮ��������
long);
	 set("exits",([
"south" : __DIR__"xiaojing1-2",
"west" : __DIR__"houyuan1",
	     "east" : __DIR__"wuchang",
]));
set("objects",([
	"/d/mr/npc/murong-fu" : 1,
]));
     "/clone/board/murong_b.c"->foo(); 
	 setup();
}

void init()
{
    object me=this_player();
  
	if( me->query("family/family_name") == "����Ľ��" 
	&& me->query("mr/addtimes") < 1)
	{
	if(me->query("combat_exp") < 1000000 && me->query("combat_exp") > 500000)
	{       
		me->set("mr/addtimes", 1); 
		me->add("mr_job",300);
		tell_object(me, HIY "\nϵͳ�Ѿ��Զ�Ϊ���������ٴε�Ľ������\n" NOR);
		return;
	}
		
	if(me->query("combat_exp") < 2000000 && me->query("combat_exp") > 1000000)
	{      
		me->set("mr/addtimes", 1); 
		me->add("mr_job",500);
		tell_object(me, HIY "\nϵͳ�Ѿ��Զ�Ϊ��������ٴε�Ľ������\n" NOR);
		return;
	}
	
	if(me->query("combat_exp") < 3000000 && me->query("combat_exp") > 2000000)
	{
		me->set("mr/addtimes", 1); 
		me->add("mr_job",1000);
		tell_object(me, HIY "\nϵͳ�Ѿ��Զ�Ϊ������һǧ�ε�Ľ������\n" NOR);
		return;
	}
	
	if(me->query("combat_exp") < 4000000 && me->query("combat_exp") > 3000000)
	{
		me->set("mr/addtimes", 1); 
		me->add("mr_job",1500);
		tell_object(me, HIY "\nϵͳ�Ѿ��Զ�Ϊ������һǧ��ٴε�Ľ������\n" NOR);
		return;
	}
	
	if(me->query("combat_exp") > 4000000)
	{
		me->set("mr/addtimes", 1); 
		me->add("mr_job",2000);
		tell_object(me, HIY "\nϵͳ�Ѿ��Զ�Ϊ�����϶�ǧ�ε�Ľ������\n" NOR);
		return;
	}
	return;
}
}
