// bamboo_stick.c 玉竹棒
// by shang 97/6
// modified by explorer, 9/11/97

#include <ansi.h>
#include <weapon.h>

inherit STICK;

string* skills = ({
        "stick",
        "bangjue",
});

void create()
{
        int i;

        i = 0;
        if (random(10) > 6) i = 1;

        set_name(HIG "玉竹棒" NOR, ({"yuzhu bang", "bang", "stick"}));
        set_weight(10000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long",HIG + "一根看起来温润晶莹,通体碧绿的竹棒,,泛着淡淡的青光 。\n" NOR);
                set("value", 1000);
                set("material", "bamboo");
                set("treasure", 1);
                set("unique", 1);
                set("weapon_prop/parry", 4);
                set("rigidity", 10);
                set("wield_neili", 900);
                set("wield_maxneili", 1400);
                set("wield_str", 24);
                set("wield_msg", "$N抽出一根青光闪闪的玉竹杖抓在手中。\n");
                set("unwield_msg", "$N把手中的玉竹杖插回腰中。\n");
                set("skill", ([
                     "name": skills[i],
                     "exp_required": 50000,
                     "difficulty": 24,
                     "max_skill": 100,
                ]) );
        }
        init_stick(60);
        setup();
}       

void init()
{
        if( this_player() == environment() )
                add_action("do_study", "study");
}

int do_study(string arg)
{
        int damage;

        object me = this_player();

        if ( arg != "bang" && arg != "stick" )
            return notify_fail("你要学什么？\n");

        if ((int)me->query_skill("literate", 1) < 30 )
            return notify_fail("你的学识还没够领会棒上的口决。\n");

        if ((int)me->query_skill("bangjue",1) > 120)
            return notify_fail("你已经不能从棒上学到任何东西了。\n");

        if ((int)me->query_skill("stick", 1) < 60 )
            return notify_fail("你的基本棒法太差, 还领会不了棒决。\n");

        damage = 2400 / (int)me->query("int");
        me->receive_damage("jing", damage);
        me->receive_damage("jingli", damage);
        me->improve_skill("bangjue", me->query("int"));
        message_vision("$N看着棒上的字迹, 凝思不已。\n", me);
        return 0;
}
