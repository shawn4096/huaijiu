// Room: /d/xingxiu/yili1.c
// by snowman@SJ

#include <ansi.h>
inherit ROOM;

void quarter_pass();

void create()
{
        set("short", "伊犁城门");
        set("long", @LONG
伊犁，又名惠远，西通波斯，南到天竺，东与阳关、玉门相连，扼中
西交通的要冲，是丝绸之路上重要的旅站之一。伊犁城墙在伊犁河北岸度
地而筑，城高一丈四，地势险要。城墙上满布着炮台、枪眼，戒备森严。
LONG
        );
        set("outdoors", "yili");
        set("exits", ([
                "south" : __DIR__"yilihe",
                "north" : __DIR__"yili2",
        ]));

        set("objects", ([
                __DIR__"npc/bing" : 2,
                __DIR__"npc/shangren" : 1,
        ]));
        set("coor/x",-300);
  set("coor/y",150);
   set("coor/z",0);
   set("coor/x",-300);
 set("coor/y",150);
   set("coor/z",0);
   setup();
        quarter_pass();
}

void quarter_pass()
{
        string local;
    
        local = NATURE_D->query_daytime();
        
        switch(local){
            case "event_night":
            case "event_midnight": 
                  set("long", @LONG
伊犁，又名惠远，西通波斯，南到天竺，东与阳关、玉门相连，扼中
西交通的要冲，是丝绸之路上重要的旅站之一。伊犁城墙在伊犁河北岸度
地而筑，城高一丈四，地势险要。城墙上满布着炮台、枪眼，戒备森严。
现在是夜间，城门已关，只有几个回族士兵在城门口守夜。
LONG);       
        	  delete("exits/north");
                  break;
            default: set("long", @LONG
伊犁，又名惠远，西通波斯，南到天竺，东与阳关、玉门相连，扼中
西交通的要冲，是丝绸之路上重要的旅站之一。伊犁城墙在伊犁河北岸度
地而筑，城高一丈四，地势险要。城墙上满布着炮台、枪眼，戒备森严。
LONG);
                  set("exits/north", __DIR__"yili2");
        	  break;            
        }
        call_out("quarter_pass", 60);
}
