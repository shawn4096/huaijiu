// /d/wudang/shijie1.c 石阶
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
你走在一条坚实的石阶上，不时地有游人或进香客从你的身边走过。
一边是悬崖，一边是峭壁，抬头隐约可见山雾环绕的天柱峰，山风拂面，
鸟鸣声声，令人心旷神怡。
LONG
        );
        set("exits", ([
                "southup" : __DIR__"shijie2",
                "northdown" :__DIR__"xuanyuemen",
        ]));

        set("objects",([
                __DIR__"npc/shusheng" : 1,

        ]));
        
        set("coor/x",20);
  set("coor/y",20);
   set("coor/z",10);
   setup();

}
