// /d/wudang/shijie3.c 
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short","石阶");
        set("long", @LONG
你走在一条古朴的石阶上，不时地有道士和你擦肩而过。远处的
撞钟声清晰可闻。抬头隐约可见笼罩在云雾中的天柱峰，你知道快到
山顶了，一兴奋顿时忘了浑身的疲倦。
LONG
        );
        set("exits", ([
                  "westup" : __DIR__"shijie4",
                 "eastdown" : __DIR__"shibapan",
        ]));

        set("coor/x",-10);
  set("coor/y",-40);
   set("coor/z",70);
   setup();

}
