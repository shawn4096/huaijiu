// miaojiang

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
		"northeast" : __DIR__"guanmucong"+(random(13)+1),
		"southwest" : __DIR__"guanmucong2",
		"northwest" : __DIR__"guanmucong"+(random(13)+1),
		"southeast" : __DIR__"guanmucong"+(random(13)+1),
		"down" : __DIR__"shanya2",
	]));

      set("outdoors", "miaojiang");

	setup();

}
 
