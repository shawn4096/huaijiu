// Room: peitian-fang.c
// Created by Numa 1999-11-21

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIC"��������"NOR);
	set("long", @LONG
�����б���λ����ɽ֮�۵ķ���̨������ȥ��ң���ɸ����ţ���
������һ�ߣ��������������������ڣ����������������ص�����ɽ�塣
LONG);
	set("exits", ([ 
            "southdown" : __DIR__"shidao3",
            "northup" : __DIR__"fengchantai",
        ]));
	set("outdoors", "��ɽ");
	set("coor/x",40);
  set("coor/y",360);
   set("coor/z",140);
   setup();
}
