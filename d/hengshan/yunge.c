// Room: /d/hengshan/yunge.c
#include <room.h>
inherit ROOM;
void create()
{
        set("short", "�Ƹ����");
        set("long", @LONG
����ջ�����͵��Ƹ���š�ǰ����ɽ������Է壬��Ҫ������
��������ӡ������Բ���ˮ�������������ؽ��泩��
LONG);
        set("exits", ([ /* sizeof() == 4 */
           "east"      : __DIR__"daziling",
           "northdown" : __DIR__"zhandao",
        ]));
	set("objects", ([
		__DIR__"npc/zhi" : 1,
	]));
        set("outdoors", "��ɽ");

        set("coor/x",50);
  set("coor/y",80);
   set("coor/z",50);
   setup();
}

