// by XiaoYao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "���");
	set("long", @LONG
������һ��Ƭũ���Զ����һЩ��ׯ�������������𡣴�ׯ��Χ
��һ������أ�������һЩ���ڸ�����ũ�ˡ����ﲻʱ����һ������
Ȯ�͡�
LONG );
	set("exits", ([
		"southwest" : __DIR__"tiandi3",
		"north"     : __DIR__"huanghe1",
                "east"      : __DIR__"hsroad2",
	]));
	set("objects", ([
		__DIR__"npc/dog" : 1,
	]));
	set("no_clean_up", 0);
	set("outdoors", "�ƺ�");
	set("coor/x",120);
  set("coor/y",90);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

