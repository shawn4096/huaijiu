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
		"west" : __DIR__"guanmucong"+(random(13)+1),
		"east" : __DIR__"guanmucong9",
		"south" : __DIR__"guanmucong"+(random(13)+1),
		"north" : __DIR__"guanmucong"+(random(13)+1),
	]));

	set("outdoors", "miaojiang");
	setup();
}
 

