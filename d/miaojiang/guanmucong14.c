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
		"south" : __DIR__"guanmucong"+(random(13)+1),
		"north" : __DIR__"mjqj",
		"east" : __DIR__"guanmucong"+(random(13)+1),
		"west" : __DIR__"guanmucong"+(random(13)+1),
	]));

	set("outdoors", "miaojiang");
	setup();
}
 
