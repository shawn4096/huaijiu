// /d/city/kongchang

inherit ROOM;
#include <guanfu.h>

void create()
{
        set("short", "广场");
        set("long", @LONG
这是知府旁边的一片小空场，在东边的墙上贴了几张官府悬赏捉拿
朝廷要犯的告示 (wanted list)，下面围观了许多看热闹的人，当中不
乏一些武林高手，但是要捉拿的要犯都很扎手，很少有人随便揭榜(jie)。 
但也有不少武林后起之秀在一旁跃跃欲试。
LONG
        );

        set("item_desc", ([
                "wanted list" : (: GF_WANTED->look_wanted() :),
        ]));

        set("exits", ([
                "southwest" : "/d/city/guangchangbei",
        ]));

   	setup();
        call_out( (:call_other:), 1, GF_WANTED, "???");
}

void init()
{
        if( this_player()->query_condition("killer") )
                return;
        add_action("do_jie", ({"xian","jie"}));
}

int do_jie(string arg)
{
        return GF_WANTED->do_jie(arg);
}
