// BY XIAOYAO

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
��������߰�����ֻ������ͷ���ϴ���һЩ�����������ż����ï
�ܵ�Ҷ��͸����һ�߹������Ҷ�ڷ��衣��ľ���õ���ζ�����ᴫ��Ұ
�޵�Х��ʹ�˲�����ԥ��ǰ���ĽŲ���
LONG );
	set("exits", ([
		"east"  : __DIR__"shulin1",
		"north" : __DIR__"shulin4",
	]));
	set("objects", ([
                __DIR__"npc/wolf" : 1,
	]));
	set("outdoors", "�ƺ�");
	set("coor/x",90);
  set("coor/y",50);
   set("coor/z",0);
   setup();
}

