// miaojiang guanmucong

#include <room.h>
inherit ROOM;


void create()
{
	set("short", "��ľ��");
	set("long", @LONG
������һƬһ�˶�ߵĹ�ľ�ԣ������Ѿ������㼣��һ��紵������ľ��
����ɳɳ��������
LONG
	);

	set("exits", ([
		"north" : __DIR__"guanmucong"+(random(13)+1),
		"south" : __DIR__"guanmucong11",
		"east" : __DIR__"guanmucong"+(random(13)+1),
		"west" : __DIR__"guanmucong"+(random(13)+1),
	]));

	set("outdoors", "miaojiang");
	setup();
}
 

