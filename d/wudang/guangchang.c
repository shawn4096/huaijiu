// Room : /d/wudang/guangchang.c  武当广场
// by ydh
#include <ansi.h>
inherit ROOM;
int do_zhao(string arg);

void create()
{
        set("short",HIW"武当广场"NOR);
        set("long", @LONG
这是一个由大白石板铺成的广场，两边有两个兵器架，十八武器
样样俱全，墙角还散放着几个练力的石锤和一些杂物。是武当弟子学
习武功和互相切磋的地点。周围种满了梧桐树，一到秋天就是满地的
落叶。一个年纪轻轻的道童正在打扫。南边是灵霄宫三清殿。
LONG                           
        );
	set("outdoors", "武当");
        set("exits", ([
		   "south" : __DIR__"sanqingdian",
                "northdown" :__DIR__"zxgdamen",
        ]));

        set("objects",([
                "/kungfu/class/wudang/guxu" : 1,
                __DIR__"npc/daotong" : 2,

        ]));

        set("coor/x",-20);
  set("coor/y",-60);
   set("coor/z",100);
   setup();
}

void init()
{
        add_action("do_zhao", ({"zhao","find"}));
}

int do_zhao(string arg)
{
              mapping fam; 
        object me,yc;
        me=this_player();
              fam = me->query("family");

        if ( arg != "yao chu" )
            return notify_fail("你要找什么？\n");
              
                if (!fam || fam["family_name"] != "武当派")
                      return notify_fail("你又不是武当弟子，跑到武当来瞎找什麽东西？！\n");

    if (me->query_temp("yaochu_get"))
            return notify_fail("怎么这么贪，不是拿过一把了吗？\n");         
 
              if (me->query("combat_exp",1) <= 20000)
                     return notify_fail("你刚入武当就要瞎翻东西？\n");
         yc=unew("/d/wudang/obj/yaochu");
       if (yc)
          {
           message_vision("$N在墙脚的杂物堆里翻来翻去找出一把药锄。\n", me);
          me->set_temp("yaochu_get",1);
           yc->move(me);}
        else
           message_vision("$N在墙脚的杂物堆里翻来翻去什么也没找着。\n", me);
     return 1;
}
