// play.c 
// cck 6/7/97

#include <ansi.h>;

inherit F_CLEAN_UP;

int main(object me, string arg)
{

	if ( !arg || (arg != "music") && (arg != "zheng") && (arg != "gu
	     zheng") && (arg != "wei qi") && (arg != "qi") && (arg != "go") )
	return notify_fail("��Ҫ��ʲô��\n");

	if ( present("gu zheng", this_player()) &&
	     ((arg == "music") || (arg == "zheng") || (arg == "gu zheng"))  )
	{
		if ( random(me->query_skill("art", 1)) < 50 )
		{
		message_vision("$N�ڳ�һ�Ź��ݣ����������˼���ֻ����������"
		"�����£��������Ǻš�\n", me);
		me->receive_damage("jing", random(30) );
		me->receive_damage("qi", random(30) );
		return 1;
		}

		me->receive_damage("jing", 20);
		me->receive_damage("qi", 20);
		if (me->query_skill("art",1) < 200)
		me->improve_skill("art", (int)me->query_int()/4 + (int)me
		    ->query_skill("art", 1)/10);
		tell_object(me, "��ڳ�һ�Ź��ݣ����˵��ң�������������ֻ"
			"������������������������ࡣ\n");
		
		message("vision", "ֻ��" + me->query("name") +
	"���˴󷢣�����������������ֻ����ʱ�����������Įƽɳ������������\n"
	"ʱ��С����ˮ�������˼ҡ�������������������������ʱ��������ࡣ\n",
		environment(me), ({me}) );
		return 1;
	}

	if ( present("wei qi", this_player()) && ((arg == "wei qi") 
	     || (arg == "qi") || (arg == "go")) )
	{
		if ( random(me->query_skill("art", 1)) < 50 )
		{
		message_vision("$N�ڳ�һ�����̣����о�Χ�壬ȴ��"
		"�����ķ����ң�������������\n", me);
		me->receive_damage("jing", random(30) );
		me->receive_damage("qi", random(30) );
		return 1;
		}

		me->receive_damage("jing", 20);
		me->receive_damage("qi", 20);
		if (me->query_skill("art",1) < 200)
		me->improve_skill("art", (int)me->query_int()/4 + (int)me
		    ->query_skill("art", 1)/10);

		tell_object(me, "��ڳ�һ�����̣��о���Χ������ֻ������ƽ"
			    "���ͣ��ܿ�ͷ·��붨�ˡ�\n");

		message("vision", "ֻ��" + me->query("name") +
	"���˴󷢣��������������������·��Ų��ʣ�һ��Ī������ģ����\n",
		environment(me), ({me}) );
	}
		
	return notify_fail("��Ҫ��ʲô��\n");
}
