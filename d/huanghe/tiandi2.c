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
		"southwest" : __DIR__"shulin5",
		"east"      : __DIR__"tiandi1",
	]));
	set("objects", ([
		__DIR__"npc/cow" : 1,
	]));
	set("outdoors", "�ƺ�");
	set("coor/x",90);
  set("coor/y",80);
   set("coor/z",0);
   setup();
}

