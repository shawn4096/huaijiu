// Room : /d/wudang/conglin3.c 丛林
// By lius 99/8

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIR"烈火丛林"NOR);
        set("long", @LONG
这里是一片红色的海洋，由于地处丛林的外围，独特的地理气候，使得这
里满山红枫，你惊叹自然之神奇，不知不觉的迷失了方向。
LONG                           
        );

        set("exits", ([               
                 "east" : __DIR__"conglin"+(random(4)+1),
                 "west" : __DIR__"conglin"+(random(4)+1),
                 "south" : __DIR__"conglin3",
                 "north" : __DIR__"conglin4",
                 "northeast" : __DIR__"conglin"+(random(8)+1),
                 "northwest" : __DIR__"conglin"+(random(8)+1),
                 "southeast" : __DIR__"conglin"+(random(8)+1),
                 "southwest" : __DIR__"conglin"+(random(4)+1),
        ]));

	 set("objects", ([
                          __DIR__"npc/yetu" : 1, 
                          __DIR__"npc/shanji" : 1, 
        ]));

        setup();

}

void init()
{
         add_action("do_zhao", ({"zhao","find"}));
}

int do_zhao(string arg)
{       object yaocai;
        object me;
        int name;        
        me = this_player();
        name = (int)me->query_temp("caiyao_name",1);
        if (me->is_busy())
        return notify_fail ("你现在很忙！\n");
        if (me->is_fighting())
        return notify_fail ("你还是专心战斗吧。！\n");        
        if (!( present("yao chu", me)))
        return notify_fail("你正在找寻药材，突然发现忘带药锄，不禁暗暗懊恼！！\n");
        if ( !arg || arg != "yaocai" )
        return notify_fail("你要找什么？\n");
        if (!(int)me->query_temp("caiyao_room"))
        return notify_fail("现下这些药材可是紧缺异常，你就不要糟蹋了吧！？\n");
        if(((int)me->query_temp("caiyao_room",1) != 3) && (random(5) < 1 ))
        return notify_fail("你举目四顾，哪有半分药材的影子，还是到其他地方看看吧！\n");
        if ((int)me->query("jingli")<200) 
        return notify_fail ("你已十分疲惫，需要好好休息了！\n");        
        if(((int)me->query_temp("caiyao_room",1) == 3) && (random(5) < 1 )){
        me->delete_temp("caiyao_room");
        me->set_temp("caiyao_ok",1);
        me->add("jingli",-30);
        message_vision("$N拨开草丛，突然发现一株"YEL+name+NOR",欣喜如狂，赶忙轮起药锄挖了起来，放入怀中。\n",me);
        switch(name) {
          case "生地":
               yaocai=new(__DIR__"obj/shengdi");
               yaocai->move(me);
               break;
          case "茯苓":
               yaocai=new(__DIR__"obj/fuling");
               yaocai->move(me);
               break;
          case "红花":
               yaocai=new(__DIR__"obj/honghua");
               yaocai->move(me);
               break;    
          case "灵仙":
               yaocai=new(__DIR__"obj/lingxian");
               yaocai->move(me);
               break;
          case "桃仙":
               yaocai=new(__DIR__"obj/taoxian");
               yaocai->move(me);
               break;
          case "没药":
               yaocai=new(__DIR__"obj/meiyao");
               yaocai->move(me);
               break;
          case "五灵脂":
               yaocai=new(__DIR__"obj/wulingzhi");
               yaocai->move(me);
               break;
          case "千金子":
               yaocai=new(__DIR__"obj/qianjinzi");
               yaocai->move(me);
               break;
          case "当归":
               yaocai=new(__DIR__"obj/danggui");
               yaocai->move(me);
               break;
          case "远志":
               yaocai=new(__DIR__"obj/yuanzhi");
               yaocai->move(me);
               break;
          case "独活":
               yaocai=new(__DIR__"obj/duhuo");
               yaocai->move(me);
               break;
          case "防风":
               yaocai=new(__DIR__"obj/fangfeng");
               yaocai->move(me);
               break;}                  
         return 1;  
        }        
        else
        me->add("jingli",-(100+random(20)));
        message_vision("$N眼光似电，迅速的在丛林中搜寻着。\n", me);
        return 1;
}
