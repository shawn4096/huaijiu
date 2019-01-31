// jqdan.c 绝情丹
// By River 99.5.25
#include <ansi.h>
inherit ITEM;

void create()
{
       set_name(HIG"绝情丹"NOR, ({"jueqing dan", "dan","jueqing"}));
       set_weight(500);
       if (clonep())
             set_default_object(__FILE__);
       else {
             set("unit", "枚");
             set("long","这是一枚四四方方骰子般的丹药，色作深黑，腥臭刺鼻。\n");
             set("value", 1000);
             set("unique", 1);
             set("no_give", 1);
             set("no_drop", 1);
             set("no_get", 1);
             }
             setup();
}

int init()
{
       add_action("do_eat", "eat");
       add_action("do_mix", "mix");
}

int do_eat(string arg)
{
       object me = this_player();
       if(!id(arg))
             return notify_fail("你要吃什么？\n");
       message_vision("$N吃下一枚" + name() + "。\n", me);
       if ((int)me->query_condition("qinghua_poison") > 0) {
          me->clear_condition("qinghua_poison");
          tell_object(me,"你只觉得手指痛楚大减，情花之毒已然解去。\n");
          }
       destruct(this_object());
       return 1;
}

int do_mix(string arg)
{
       object me = this_player();
       object thing,ob;

       if(!id(arg))
             return notify_fail("你要混合什么？\n");

       thing = present("duanchang cao", me);
       if (!thing || !thing->query("credit") ) 
	      return notify_fail("你没有断肠草，如何混合!\n");

       message_vision("$N将绝情丹与断肠草混合在一起。\n", me);
       destruct(thing);

       if (random(50) > 47) {
          ob=unew("/d/gumu/jqg/obj/jqdan1");
          ob->move(me);
          tell_object(me,"解药制作成功，快给杨过送去吧!\n");
          destruct(this_object());
          return 1;
          }
       tell_object(me,"你几经努力终因手法不够纯熟，解药配置失败。\n");
       destruct(this_object());
       return 1;
}
