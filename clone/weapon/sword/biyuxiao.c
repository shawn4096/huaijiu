///u/jpei/thd/obj/biyuxiao.c 碧玉箫
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(GRN"碧玉箫"NOR,({"biyu xiao","xiao"}));
        set_weight(9000);
        if (clonep())
                set_default_object(__FILE__);
        else{
                set("unit","支");
                set("value",2000);
                set("material","gem");
                set("unique", 1);
                set("treasure", 1);       
                set("rigidity", 6);
                set("weapon_prop/parry", 3);
                set("wield_neili", 500);
                set("wield_maxneili", 1000);
                set("long","这是一支通体晶莹的用极为罕见的"GRN"碧玉"NOR"做的箫，看起来年代十分久远。\n");
                set("wield_msg","$N伸手轻轻一招，一支$n已出现在$N手中。\n");
                set("unwield_msg","$N一声清啸，将$n插回腰间。\n");
        }
        init_sword(50);
        setup();
}
int wield() 
{
        object me = environment();
        if (living(me) && me->query_skill("yuxiao-jian", 1) < 200){
            message_vision("$N拿起"+name()+"，但是不会使用。\n", me);
            return 0;
        }           
        if(!query("weapon_prop/damage")) return 0;
        return ::wield();
}

