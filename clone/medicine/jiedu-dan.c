// jiedu-dan.c

#include <ansi.h>

inherit ITEM;

void init()
{
             add_action("do_eat", "fu");
}

void create()
{
        set_name("天心解毒丹", ({"jiedu dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","这是一颗其貌不扬的丹药，却可解百毒。\n");
                set_weight(25);
                set("value", 10);
                set("unit", "颗");

        }
}

int do_eat(string arg)
{
        object me;
        int i,plvl,cure;
        mixed a;
        mapping fam;
        string poison;
        a = ({"snake_poison","xx_poison","dsy_poison","fs_poison","huagu_poison","man_poison","qinghua_poison","qishang_poison","qzhu_poison","sl_poison","sy_poison","warm_poison","hot_poison","cold_poison","bing_poison","hb_poison","bt_poison"}); 
        me = this_player();
        for( i=0; i < sizeof(a); i++ )
                        if( me->query_condition(a[i]) > 0 )
                        {
                                poison = a[i];
                                break;
                        }
        if (!id(arg)) return 0;

        plvl= me->query_condition(poison , 1);

        if( plvl == 0 )
                return notify_fail("你并没中毒，小心吃错了药！\n");


        message_vision(MAG"\n$N服下一颗天心解毒丹，感到体内所中剧毒已经被药力所驱散！\n\n"NOR , me);

        me->apply_condition(poison, 0);

        destruct(this_object()); 
        return 1;
}