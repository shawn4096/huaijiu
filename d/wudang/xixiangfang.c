// /d/wudang/xixiangfang.c
// by ydh

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "北厢房");
        set("long", @LONG
武当弟子想下山，要到这里等待摊派任务或领取盘缠; 如果下山归来
也要来这签到汇报。加上一些来送行的，接风的人，使得这人气旺盛
好不热闹。房的正里放着一张红木八仙椅，武当七侠正坐在上面处理
事务，旁边站着两个记事理财道童。墙壁上挂着一幅字画(zihua)。
LONG
        );
        set("exits", ([
                "south" : __DIR__"xiaolu7",
        ]));
        set("objects",([
                "/kungfu/class/wudang/moshenggu" : 1,
              BINGQI_D("fr_zhen") : 1,
                __DIR__"npc/daotong" : 2,

        ]));
        

        set("item_desc", ([
                "zihua" :
HIW"


    ※※※※※※※※※※※※※※※※※※※※※※
    ※※※※　　　　　　　　　　　　　　※※※※
    ※※※※　                  　      ※※※※
    ※※※※ 　 　道,可道,非常道; 　　　※※※※
    ※※※※　                          ※※※※
    ※※※※　　　　　　　　　　　　　　※※※※
    ※※※※　                          ※※※※
    ※※※※ 　 　名,可名,非常名!   　　※※※※
    ※※※※　                          ※※※※
    ※※※※　　　　　　　　　　　　　　※※※※
    ※※※※※※※※※※※※※※※※※※※※※※\n"NOR,
        ]));
        
   setup();
}
