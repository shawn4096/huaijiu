// duoming-wan.c 

#include <ansi.h>

inherit ITEM;

void init()
{
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW"白虎夺命丸"NOR, ({"duoming wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long", "这是一颗晶莹如珠的救命药丸。\n");
                set("value", 1000);
        }
	set_weight(100);

        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if (!id(arg))
        return notify_fail("你要吃什么？\n");

        message_vision(HIW "$N吃下一颗白虎夺命丹，但觉一股暖流自丹田升起，随即遍布四肢，浑身说不出有多舒服！\n" NOR, me);
        me->set("eff_qi", me->query("max_qi"));
        me->set("qi", me->query("eff_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("jing", me->query("eff_jing"));
        if(me->query("jingli") < me->query("eff_jingli"))
        me->add("jingli", 200);
        if(me->query("neili") < me->query("max_neili")*2)
        me->add("neili", 200);
        destruct(this_object());

        return 1;
}

