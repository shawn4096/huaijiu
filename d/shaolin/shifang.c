// Room: /d/shaolin/shifang.c
// Date: YZC 96/01/19

#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", BLU"ʯ��"NOR);
    set("long", 
"һ���޴���Ʒ��������Ƭɽ��֮�䣬�Ʒ����Ϸ���������������֣�\n"
"��"HIY"���µ�һ��ɲ"NOR"�����ּ���Щ���䣬����ȥ�����Ϊ��Զ�ˡ�ǰ����һƫ��\n"
"��Ĺ㳡��վ����ǰ���������ͺ�һЩ�����ϵĺ�ʿ�������������µ�ɽ\n"
"�ŵ�ʹ����ڹ㳡����һ�ࡣ\n"

    );

    set("exits", ([
        "north" : __DIR__"guangchang1",
        "south" : __DIR__"shijie11",
    ]));

    set("outdoors", "shaolin");
   
    set("coor/x",50);
  set("coor/y",190);
   set("coor/z",110);
   set("coor/x",50);
 set("coor/y",190);
   set("coor/z",110);
   setup();
}

