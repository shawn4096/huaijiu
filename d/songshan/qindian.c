// Room: qindian.c
// Created by Numa 1999-11-21

#include <ansi.h>
#include <wanted.h>
inherit ROOM;

void create()
{
	set("short", HIC"�޵�"NOR);
	set("long", @LONG
��������ɽ�ɵ��ӵ���Ϣ֮����ÿ���峿�������Ƕ���ȥ��������
������ϰ���ա��ϱ����߷ֱ����У�Ů���ӵ���Ϣ�ң�������������ɽ
���������������ҡ�
LONG);
	set("exits", ([ 
		"north" : __DIR__"nv-room",
		"south" : __DIR__"nan-room",
		"east" : __DIR__"zmwshi",
		"west" : __DIR__"suishilu3",
	]));
	set("objects", ([ 
		CLASS_D("songshan") + "/gao" : 1,
	]));
	set("outdoors", "��ɽ");
	set("coor/x",60);
	set("coor/y",340);
	set("coor/z",120);
	setup();
}

int valid_leave(object me, string dir)
{
	if ((dir == "north" || dir == "south") && is_wanted(me))
		return 0;
	if (dir == "south" && me->query("gender") == "Ů��")
		return notify_fail("�������Ҫ�����ߣ���Ȼ�������涼�ǹ���ӵ��е��ӣ����æ���������˳�����\n");


	if (dir == "north" && me->query("gender") != "Ů��")
		return notify_fail("�������Ҫ�����ߣ�ȴ�������洫��һ��Ů���ӵļ���������ŵø�æ���˳�����\n");

	return ::valid_leave(me, dir);
}
