// Room: /d/taishan/.c
// Date: CSWORD 96/03/25

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������̩ɽʮ���̵���㡣�˴�ɽ�ƶ��ͣ���ɽ����һ����
С�ĺ����ױ����鵽�¹�֮�С�
LONG
	);

	set("exits", ([
		"northup" : __DIR__"shengxian",
		"southdown" : __DIR__"wudafu",
	]));

        set("objects",([
                __DIR__"npc/chibaicheng" : 1,
        ]));
        set("outdoors", "̩ɽ");
	set("coor/x",170);
  set("coor/y",190);
   set("coor/z",80);
   setup();
}

void init()
{
	object me = this_player();
	
        if( random((int)me->query_skill("dodge")) <= 20 && userp(me) )
	{
		me->receive_damage("qi", 50);
		me->receive_wound("qi",  50);
		me->set_temp("last_damage_from", "��ɽ�Ϲ�����ˤ");
		message_vision(HIR"$Nһ��С�Ľ���̤�˸��գ�... ��...��\n"NOR, me);
		me->move(__DIR__"daizong");
		tell_object(me, HIR"���ɽ�Ϲ���������ֻ���û����޴����ۣ������˼����ˡ�\n"NOR);
		message("vision", HIR"ֻ��" + me->name() + "��ɽ�Ϲ�µµ�ع������������ڵ��ϰ�������������\n"NOR, environment(me), me);
	}
}
