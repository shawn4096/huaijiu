#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW"洞箫"NOR,({"dongxiao",  "xiao"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else{
                set("unit", "支");
                set("value", 9000);
                set("rigidity", 9);
                set("sharpness", 5);
                set("material", "starsteel");
                set("treasure",1);
                set("unique",1);
                set("wield_neili", 500);
                set("wield_maxneili", 900);
                set("weapon_prop/parry", 2);
                set("wield_msg",HIY"$N伸手轻轻一招，一支$n" + HIY"已出现在$N手中。\n"NOR);
                set("unwield_msg",HIY"$N一声清啸，将$n" + HIY"插回腰间。\n"NOR);
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

