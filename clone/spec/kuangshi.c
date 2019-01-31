
#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("天外陨石", ({ "yun shi" , "shi" }));
        set_weight(3000+random(5000));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long",HIC"不知出处，铁质坚硬，似乎可以用来淬炼兵器。\n"NOR);
                set("value", 3000);
                set("weapon_pro",1);
                set("no_cun", 1);
                set("no_give", 1);
                set("no_drop", 1);
                set("no_get", "这样东西不能离开那儿。\n");
                set("treasure",1);	
                set("degree",1);
                set("credit",60);
                set("desc","用于提升玩家打造武器的威力。");               
                set("no_sell","稀奇古怪的一块石头，要来何用？");
        }
        setup();
}
