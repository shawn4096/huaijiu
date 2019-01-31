// Room: /d/huashan/jitan.c
// Date: Look 99/03/25

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short", "��̳");
	set("long",@long
�����ǻ�ɽ���������Ǽ�������ļ�̳����ɽ���Ӷ�Ҫ��ɽ�������壬��
��ȡ�ϲԶԻ�ɽ���յı��ӡ�
long);
	set("exits", ([
	"out" : __DIR__"yunuci",
]));
	set("objects", ([
	__DIR__"npc/lingshan" : 1,
	__DIR__"npc/shitong" : 1,
]));
	setup();
}

void init()
{
	add_action("do_jitan", "jitan");
}

int do_jitan(string arg)
{
	object me, ob, ling;
	int addskill;
	me = this_player();
	ob = this_object();
	ling = present("ling pai", me);
	if(!living(me) ) return 0;
	
	if(!ling)
	return notify_fail("������û��������θ�οӢ�ҵ�����֮�飿\n");

        if (me->is_busy() || me->is_fighting())
	return notify_fail("����æ���ģ�\n");

	if( !me->query_temp("jitan") )
	return notify_fail("��Ҫ��ʲô��\n");

	if(!arg || arg =="" ||
	  ( arg != "strike" && arg != "hand" && arg != "claw" && arg!= "force" &&
	    arg != "cuff" && arg != "finger" && arg != "leg"))
	return notify_fail("��Ҫ��ʲô��\n");

	message_vision("$N�����ش���ͯ���нӹ������ˣ��ڷ��ڼ�̳ǰ�������ؿ���������ͷ��\n", me);
        write(HIW"ͻȻ����н���һ�����磬���������ˡ�ֻ��������һ���ҽУ��ʹ���ȥ��\n"NOR, me);
	addskill = (int)me->query("int",1) * 2 + (int)me->query("kar",1) * 2 + random((int)me->query("hs_job", 1) / 15);
        addskill = random(addskill) + 1;
	if (arg != "force")
	{
		me->improve_skill( arg , addskill);
	        write("���"+to_chinese(arg)+"�õ���"+CHINESE_D->chinese_number(addskill)+"����ߡ�\n", me);
	}
	else
	{
            addskill=random(addskill/10) + 2;
                me->improve_skill( me->query_skill_mapped("force") , addskill);
	        write("���"+to_chinese(me->query_skill_mapped("force"))+"�õ���"+CHINESE_D->chinese_number(addskill)+"����ߡ�\n", me);
	}
	
	ling->add_temp("done", 1);
	me->delete_temp("jitan");
	return 1;
}		
