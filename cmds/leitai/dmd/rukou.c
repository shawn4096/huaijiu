// Room: /d/dzd/rukou.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","ʯ�����");
	set("long",@LONG
���ٲ���Ծ��������һ���������ɽ�����,���µ�ʯͷ���ڳ��걻ˮ��ˢ��Ū��ʪ������
����������濴���ƺ����ɽ���ܴ�һ�����º������ļ�,ˮ�����������
LONG
	);
	set("exits",([
		"northwest" : __DIR__"shidong1",
		"northeast" : __DIR__"shidong3",
		"north" : __DIR__"shidong2",
	]));
	setup();
}

/* void init()
{
	add_action("do_tiao","tiao");
}

int do_tiao(string arg)
{
	object me = this_player();
	if(me->is_busy() || me->is_fighting())
		return notify_fail("����æ���ء�\n");
	if(!arg || arg == "" || arg!="out")
		return notify_fail("�������Ķ�����\n");

	message_vision(HIW"$N�ż��أ������������ȥ!\n"NOR,me);
	me->delete_temp("dzd_quest/shidong");	
	me->move(__DIR__"pubu");
	message_vision(HIW"$N˳�ƶ��£���������ڵ���!\n"NOR,me);
	return 1;
} */
