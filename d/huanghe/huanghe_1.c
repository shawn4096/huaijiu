// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺ�");
	set("long", @LONG
�ƺ����ɹŸ�ԭ�ϱ������ʣ���̫��ɽ������������תͷ���£�
�γɽ��µķֽ硣������������и��ɿڡ�
LONG );
	set("exits", ([
		"south"     : __DIR__"weifen",
		"west"      : __DIR__"hetao",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",120);
  set("coor/y",120);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

