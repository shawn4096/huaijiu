// /d/wudang/shijie4.c 
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","石阶");
        set("long", @LONG
你走在一条古朴的石阶上，不时地有进香客从你的身边走过。远处
的撞钟声清晰可闻。抬头隐约可见笼罩在云雾中的天柱峰，你知道快到
山顶了，一兴奋顿时忘了浑身的疲倦。
LONG
        );
        set("exits", ([
                "southup" : __DIR__"zxgdamen",
                "eastdown" :__DIR__"shijie3",
        ]));

        set("objects",([
                __DIR__"npc/jingxiangke" : 2,

        ]));

        set("coor/x",-20);
  set("coor/y",-40);
   set("coor/z",80);
   setup();

}
