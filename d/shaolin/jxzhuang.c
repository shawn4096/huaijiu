// Room: /d/shaolin/jxzhuang.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIY"聚贤庄"NOR);
        set("long", @LONG
你走到一座高宅大院的门口，大门开着，门前左右有两个石狮子，四五级
青石台阶上是两扇钉满铜钉的大门。看得出这里是一大户人家的住所。门口正
中央高悬着一块黑底金字的大匾“聚贤庄”。
LONG
        );
        set("exits", ([
              "west" : __DIR__"yidao2",
        ]));

        set("objects",([
                __DIR__"npc/youju" : 1,
                __DIR__"npc/youji" : 1,
        ]));
 
        set("coor/x",110);
  set("coor/y",80);
   set("coor/z",0);
   set("coor/x",110);
  set("coor/y",80);
   set("coor/z",0);
   setup();
}
