// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
���Ե����ƺӾź�������һ�ס������׵������ϵͳ������ط�
�֣�����ׯ�ڵĺõط���
LONG );
	set("exits", ([
		"southwest" : __DIR__"huangtu",
		"east"      : __DIR__"huanghe_1",
		"west"      : __DIR__"qingcheng",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",110);
  set("coor/y",120);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

