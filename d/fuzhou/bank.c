// Room: /fouzhou/bank.c

// Looklove y2k/4/09
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"通宝斋"NOR);
        set("long", @LONG
这是福州的一家钱庄，是有几百年历史的中原钱庄联盟的西南分店。它们
联合发行的银票信誉非常好，通行全国。
LONG
        );

        set("exits", ([
                "south" : __DIR__"haigang",
        ]));

        set("objects", ([
                __DIR__"npc/banker" : 1,
          
        ]));
 
        set("coor/x",110);
  set("coor/y",-460);
   set("coor/z",0);
   setup();
}
