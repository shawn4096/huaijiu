// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "���");
	set("long", @LONG
������ľ����ϡ�裬��Զ����һЩ��ׯ�������������𡣴�ׯ��Χ
��һ������أ�������һЩ���ڸ�����ũ�ˡ�
LONG );
	set("exits", ([
		"south" : __DIR__"shulin3",
		"west"  : __DIR__"tiandi2",
		"east"  : __DIR__"tiandi3",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",100);
  set("coor/y",80);
   set("coor/z",0);
   set("coor/x",100);
  set("coor/y",80);
   set("coor/z",0);
   setup();
}

