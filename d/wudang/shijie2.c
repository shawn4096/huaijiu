// /d/wudang/shijie2.c 石阶
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "石阶");
        set("long", @LONG
你走在一条坚实的石阶上，不时地有游人或进香客从你的身边走
过。一边是悬崖，一边是峭壁，抬头隐约可见山雾环绕的天柱峰，山
风拂面，鸟鸣声声，令人心旷神怡。再往前是一大片松林。
LONG
        );
        set("exits", ([
                "southup" : __DIR__"sldadao",
                "northdown" :__DIR__"shijie1",
        ]));

        set("objects",([
                __DIR__"npc/jingxiangke" : 2,

        ]));
        
        set("coor/x",20);
  set("coor/y",10);
   set("coor/z",20);
   setup();

}
