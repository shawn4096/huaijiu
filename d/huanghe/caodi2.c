// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
������һ��������Ĳݵأ�����һ����ɫ��̺�����ڵ��ϡ��ݴ���
����һЩ��֪����С�����к�ġ��Ƶģ������ϵġ������ϡ���Ҷ�ϵ�
¶�����ž�Ө�Ĺ⡣
LONG );
	set("exits", ([
		"east" : __DIR__"caodi1",
		"west" : __DIR__"shulin1",
	]));
	set("objects", ([
                __DIR__"npc/obj/shikuai" : 1,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",110);
  set("coor/y",50);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",50);
   set("coor/z",0);
   setup();
}

