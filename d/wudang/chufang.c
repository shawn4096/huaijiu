// chufang.c (kunlun)
// copied from wudang, modify later.
// cck modified on 17/6/97

#include <ansi.h>
inherit ROOM;

void init();
int do_tap(string arg);
int do_sit(string arg);
void delete_served(object me);

void create()
{
        set("short", "厨房");
        set("long", @LONG
这里是武当派弟子用餐的地方。屋里布置很简单, 只摆着几张桌椅, 几位
武当弟子一声不响地吃着。大凡入道之人生活简朴, 只见碗中仅是粗茶谈饭。
LONG
        );

        set("exits", ([
                "west" : __DIR__"donglang2",
        ]));

        set("objects",([
                __DIR__"npc/daotong" : 1,
                __DIR__"obj/rice" : 2,
                __DIR__"obj/doufu" : 1,
                __DIR__"obj/xiangcha" : 1,
                __DIR__"obj/dawancha" : 2,
        ]));

        set("no_fight", 1);

        set("coor/x",0);
  set("coor/y",-80);
   set("coor/z",100);
   setup();
}

void init()
{
        add_action("do_tap", "tap");
        add_action("do_tap", "knock");
        add_action("do_sit", "sit");
}

int do_tap(string arg)
{
        object me;
        object cui;

        if (!arg || (arg != "desk" && arg != "table"))
        {
                return notify_fail("你要敲什么？\n");
        }

        me = this_player();
        if( !objectp(cui = present("daotong", environment(me))) )
                return notify_fail("你敲了敲桌子，却还是没人理你。你突然感觉自己很无聊。\n");

        if( !me->query_temp("marks/sit") )
                return notify_fail("你敲了敲桌子，却没想到有对年轻人从桌底下钻出来，愕然地看着你，"
                        +"\n你突然感觉自己很愚蠢。\n");

         if( me->query_temp("marks/served") )
         {
                  message_vision("道童不耐烦地对$N说道：刚给你上过茶你接着就要，"+
                                "你不累可我累啊！\n", me);
                  return notify_fail("");
         }

        message_vision("$N端坐在桌前，轻轻扣了下桌面，道童连忙过来招呼。\n", me);

        cui->serve_tea(me) ;

         me->set_temp("marks/served", 1);
//  remove_call_out("delete_served");
         call_out("delete_served", 10, me);

        return 1;
}


void delete_served(object me)
{
        if ( objectp(me) ) me->delete_temp("marks/served");
}


int do_sit(string arg)
{

        if ( !arg || (arg != "chair") )
                return notify_fail("你要坐什么上面？\n");

        if (this_player()->query_temp("marks/sit"))
                return notify_fail("你已经有了个座位了。\n");

        this_player()->set_temp("marks/sit", 1);
        return notify_fail("你找了个空位座下，等着上茶。\n");
}


int valid_leave(object me, string dir)
{

        if (  (dir == "west")
                && ( present("xiang cha", me)
                          || present("mi fan", me)
                          || present("doufu", me))
                && objectp(present("daotong", environment(me))) )
        switch ( random(2) )
        {
        case 0:
    message_vision("道童伸手拦住了$N：还是先把东西吃完了再走吧。\n", me);
        return notify_fail("\n");
         break;
        case 1:
         message_vision("道童拦住$N道：武当山的规矩, 饮食不得带出厨房。\n", me);
         return notify_fail("\n");
         break;
        }

        me->delete_temp("marks/sit");
        me->delete_temp("tea_cup");
        return ::valid_leave(me, dir);
}
