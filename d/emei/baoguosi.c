// Room: /d/emei/baoguoshi.c

inherit ROOM;
#include <ansi.h>
void create()
{
	set("short",HIW "������" NOR);
	set("long",@LONG
�������Ƕ�üɽ�����Ժ֮һ��������ɽ���죬���յ���۵�߷��
�����ߣ���ģ��󡣵��ڷ������������������������ڷ����Ծ���������
����������һ��������(ta)�������������һ��ų߼��������ң������������
��"���µ�һ��"������������Լ����ɴ�����¡�
LONG);
	set("item_desc", ([ 
  "ta" : HIC"    ����һ��ʮ������ͭ�����������������ף��������ѹ���С����ǧ�߰�
��֮�࣬�����С����Ͼ���ȫ��������֣���ұ��������񹤼��ɣ���������
����֮����\n"NOR,
]));
set("objects",([
    __DIR__"npc/xiangke" : 2,
]));
	set("exits", ([ 
	  "southwest" : __DIR__"milin",
	  "enter" : __DIR__"daxiongdian",
	  "west" : __DIR__"baoguosixq",
	  "east" : __DIR__"baoguosm",
]));

	set("coor/x",-190);
  set("coor/y",-120);
   set("coor/z",10);
   setup();
}

void init()
{
	add_action("do_du", "du");
	add_action("do_du", "study");
}

int do_du(string arg)
{
	object me;
	me = this_player();
	if(!living(me)) 	return 0;
	
        if (me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ģ�\n");

	if ((int)me->query("jing") < 20 )
		return notify_fail("��̫���ˣ��޷�����ѧϰ�ˣ�\n");

	if ((int)me->query_skill("dacheng-fofa", 1) > 101 )
		return notify_fail("���Ѿ����������˻������Ϸ𷨵����塣\n");

	if( !arg || arg != "ta" || arg == "")
		return notify_fail("��Ҫ��ʲô��\n");

	if ((int)me->query_skill("literate", 1) < 1 )
		return notify_fail("�㿴�˻������ϵľ��ģ�ֻ����ͷ�����ǣ���������һ����\n");
	
	if( arg == "ta") {
        if ((int)me->query_skill("dacheng-fofa", 1) < 41 ) {
	me->receive_damage("jing", 10+random(10));
	me->improve_skill("dacheng-fofa", me->query("int"));
	message_vision("$N����ר���ж��������ϵĻ��Ͼ��ġ�\n", me);
	return 1; }

     if ( (int)me->query_skill("dacheng-fofa", 1) < 101 ) {
	me->receive_damage("jing", 15+random(15));
	me->improve_skill("dacheng-fofa", me->query("int"));
	message_vision("$N����ר���ж��������ϵĻ��Ͼ��ġ�\n", me); 	
        return 1;}
    }
}
