// by xiaoyao

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
���˳ǽ������ܣ��������䣬�������ں����������ˡ�����������
������ëƤ��ɢ�أ������������Ƥ����һ�����żҿڣ���һ��������
�����ˣ����˹�����������ʮ������ˮ�Ӽ������ݡ�
LONG );
	set("exits", ([
		"south"     : __DIR__"yongdeng",
		"east"      : __DIR__"yaocaidian",
		"west"      : __DIR__"xiaojiaqiao",
		"northeast" : __DIR__"dacaigou",
	]));
	set("objects", ([
          "/d/taishan/npc/dao-ke1" : 1,
	]));

	set("outdoors", "�ƺ�");
	set("coor/x",60);
  set("coor/y",90);
   set("coor/z",0);
   setup();
}

