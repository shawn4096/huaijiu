// Room: /yaocan-ting.c
// Created by Numa 1999-11-21

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIG"ң��ͤ"NOR);
	set("long", @LONG
����һ����ɫ�����̨ͤ������ש�����̹����ɣ�ͤ�Ϻ���һ�ң�
��д��ң��ͤ������������֡��򱱱���ȥ��ԶԶ�ܿ���һ�������
�ߵĴ��ò�׳�ۡ�
LONG);
	set("exits", ([ 
            "north" : __DIR__"tianzhong-ge",
            "south" : __DIR__"shidao1",
        ]));
	set("outdoors", "��ɽ");
	set("coor/x",40);
  set("coor/y",300);
   set("coor/z",110);
   setup();
}
