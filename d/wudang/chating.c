// /d/wudang/chating.c 茶亭
#include <ansi.h>
inherit ROOM;


void create()
{
        set("short", "茶亭");
        set("long", @LONG
这是三叉路口旁边而建的茶亭，喝着香茶，还能欣赏远处的风景，
这真所谓偷得浮生半日闲! 没有比这更好的歇脚方法了。亭里三五成
群的游人围着桌子(table)，坐在椅子(chair)上，有的闲聊，有的乘
凉，好不逍遥自在。
LONG
        );

        set("exits", ([
                "northwest" : "/d/wudang/wdroad8",
        ]));
        
    set("item_desc", ([
            "table" : "一张典雅的桃木小桌，上面放着水果盘和饮茶器具。\n",
            "chair" : "一只青竹打制的靠椅，躺上去摇摇晃晃，好舒服耶！\n",
        ]));
                                        

        set("objects",([
                __DIR__"npc/taohua" : 1,
                __DIR__"obj/mitao" : 2,
                __DIR__"obj/xiangcha" : 1,
        ]));
        
        
        set("coor/x",40);
  set("coor/y",20);
   set("coor/z",0);
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
        if( !objectp(cui = present("tao hua", environment(me))) )
                return notify_fail("你敲了敲桌子，却还是没人理你。你突然感觉一陈失落。\n");
                                
        if( !me->query_temp("marks/sit") )  
                return notify_fail("你敲了敲桌子，所有的人都回头愕然地看着你，"
                        +"\n你突然感觉自己很愚蠢。\n");
        
    if( me->query_temp("marks/served") )
    {
        message_vision("桃花不耐烦地对$N说道：刚给你上过茶你接着就要，"+
                                "你是个饭桶不是啊?！\n", me);
        return notify_fail("");
    }

        message_vision("$N端坐在桌前，轻轻扣了下桌面，桃花一甩小辩，过来招呼。\n", me);
        
        cui->serve_tea(me) ;

    me->set_temp("marks/served", 1);
//  remove_call_out("delete_served");
      call_out("delete_served", 300, me);

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

        if (  (dir == "north")
           && ( present("xiang cha", this_player())
                || present("mi tao", this_player()) ) 
           && objectp(present("tao hua", environment(me))) )
        switch ( random(2) ) 
        {
        case 0: 
         return notify_fail
                ("桃花把嘴一撇：吃饱了喝足了还不够，临走怀里还揣上一些，小女子也替您脸红呢！\n");
         break;
        case 1:
         message_vision("桃花对$N道了个万福：村长规定，饮食不得带出茶房。", me);
         return notify_fail("\n");
         break;
        }
        
        me->delete_temp("marks/sit");
        me->delete_temp("tea_cup");
        return ::valid_leave(me, dir);
}


