// /d/wudang/wangbeipo.c 望背坡
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"望背坡"NOR);
        set("long", @LONG
山势到这突然陡峭，两边都是万丈深渊。上山的人都紧抓左右两
边的大铁链，一步一顿，因只能看见前行人的背脊而得此名。你大胆
伸头下探，隐约看见涧水流动，仿如蛇行。
LONG
        );
        set("exits", ([
                "southdown" : __DIR__"caihong",
                "eastdown" :__DIR__"shanlu1",
        ]));

        set("coor/x",0);
  set("coor/y",-20);
   set("coor/z",60);
   setup();

}
