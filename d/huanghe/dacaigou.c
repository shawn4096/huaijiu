// by xiaoyao

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
��񹵵��Ʋ���������������Ҫ���Ƚ�ƽ̹���ٵ�����ȫ�����֣�
ʱ�����Է򿳲�����������д�����
LONG );
	set("exits", ([
		"southwest" : __DIR__"gulang",
		"north"     : __DIR__"wuqiao",
	]));
	set("objects", ([
		__DIR__"npc/qiaofu" : 1,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",70);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

