// Room: /cmds/leitai/dmd/haitan1.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","��̲");
	set("long",@LONG
�������ǰ�ɫ��Ӳ��ɳ�������м����ű��ǵ���Ƭ�ͱ���ˮ��ˢ�ü���⻬����ʯ��
�����һЩ�����˳��ϰ��ĺ���,�����ɫ���ŵ�ɳ̲������һĨ���̡����СС�Ľ�ʯ��
��ɳ̲��,������Щ�ǳ��޴��ƺ����Բ���������һƬ�ݵء�
LONG
	);
	set("outdoors","���㵺");
	set("exits",([
		"east" : __DIR__"haitan2",
		"north" : __DIR__"xiliu1",
		"south" : __DIR__"dukou",
		"northwest" : __DIR__"caodi1",
	]));
	setup();
}

int valid_leave(object me, string dir)
{

        if ( (!present("bao shi",me) || !me->query_temp("dmd_time")) && dir == "south")
           return notify_fail(CYN"�����ί�е�����û��ɣ�����ô�ܹ��뿪��\n"NOR);

        return ::valid_leave(me, dir);
}