// /d/wudang/shibapan.c 十八盘
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","十八盘");
        set("long", @LONG
你正在爬一个很大的斜坡，俗称十八盘，大石阶一级一级笔直而
上，颇费脚力。坡上有几家山民开的小店，游客到此略坐小息再往上
爬。向前十里之后即是武当重地灵霄宫。
LONG
        );
        set("exits", ([
                "westup" : __DIR__"shijie3",
                "northdown" :__DIR__"caihong",
        ]));

        set("coor/x",0);
  set("coor/y",-40);
   set("coor/z",60);
   setup();

}
