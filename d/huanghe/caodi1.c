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
                "south" : "/d/city/hsroad1",
		"west" : __DIR__"caodi2",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",120);
  set("coor/y",50);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",50);
   set("coor/z",0);
   setup();
}

