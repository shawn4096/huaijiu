// Room: /xiangyang/bank.c
// Looklove y2k/4/09

inherit ROOM;

void create()
{
        set("short", "宝龙斋");
        set("long", @LONG
这是一家老字号的钱庄，已有几百年的历史，在全国各地都有分店。它发
行的银票信誉非常好，通行全国。
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaoxiang1",
        ]));

        set("objects", ([
                __DIR__"npc/banker" : 1,
          
        ]));
 
        setup();
}
