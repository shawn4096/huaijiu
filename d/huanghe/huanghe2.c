// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ƺӰ���");
	set("long", @LONG
�����ǻƺӰ��ߡ��ƺ����ʵ�����Ѿ���ɳ�����ˡ���ɫ�ĺ�ˮ
�ںӴ��﷭���ţ������ţ�����һ�����޴�����ѡ�
LONG );
	set("exits", ([
		"east"  : __DIR__"huanghe3",
		"west"  : __DIR__"huanghe1",
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",130);
  set("coor/y",100);
   set("coor/z",0);
   setup();
}

