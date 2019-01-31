#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + HIY "劳模勋章" NOR, ({ "worker medal" }) );
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("value", 30);
                set("long", "这是一枚劳模勋章，专门为奖励先进劳动模范而制作的，你可以将其佩带(wear)在胸前。\n");
                set("no_cun", 1);
                set("no_drop", 1);
                set("no_give", 1);
		set("no_get", "这样东西不能离开那儿。\n");
		set("treasure",1);
                set("degree",1);
                set("credit",100);
                set("desc","扣减1000次明教巡逻任务次数的辅助物品。");
               
        }
        setup();
}

void init()
{
    add_action("do_dai",({"dai","wear"}));
}

int do_dai(string arg)
{
    object me=this_player();

    if( !arg ) return 0;

    if( arg!="worker medal" && arg!="劳模勋章" ) return 0;
       
    if( me->is_fighting() || me->is_busy() )
            return notify_fail("你正忙着呢。\n");

    if( me->query("mingjiao_job")<1001 )
            return notify_fail("你工作不积极，还想佩带劳模勋章？\n");

    message_vision("$N将劳模勋章佩带在胸前。\n", me);

    tell_object(me, "你将劳模勋章佩带在胸前，心里不由自主地充满了正能量。\n");

    me->add("mingjiao_job", -1000);
            
    destruct(this_object());

    return 1;
    }
