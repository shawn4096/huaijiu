// OBJ : /u/lius/obj/wd_dan.c 试炼新丹
// By lius 99/9

#include <ansi.h>
inherit ITEM;

string *eat_msg = ({
HIG"\n丹丸入口即化，如饮琼浆，$N但觉一股真源由丹田而起，遍行奇经八脉，
一身功力大增！\n" NOR,
HIM"\n$N吃下一颗丹丸，但觉一阴一阳两股气劲分由任督二脉缓缓上行，聚于头顶百汇大穴，
$N忙以自身纯正紫气相引，终于收归丹田，功力巨增！\n" NOR,
HIC"\n丹丸入肚，$N顿觉剧痛无比，浑身血脉膨胀，四肢百骸充盈欲裂，$N忙以自身内力相抗。
良久，但觉气息如丝，真力源源不断，功力提升不少！\n"NOR,
});
string *clr = ({RED"",GRN"",YEL"",BLU"",MAG"",CYN"",WHT"",HIR"",HIG"",HIY"",HIB"",HIM"",HIC"",HIW""});

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name( (clr[random(sizeof(clr))])+ "试炼丹药" NOR, ({"wudang danyao","dan"}));
        set_weight(6); 
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long", "这是一颗武当炼制的丹丸，据说功能通神，返老还童。\n");
                set("value", 1000);
                set("no_drop", "这样东西不能离开你。\n");
                set("no_get", "这样东西你拿不了。\n");
                set("no_give", "这样东西不可随便给人。\n");
                set("no_put", "这样东西不能放在这种东西里面。\n");

        }

        setup();
}

int do_eat(string arg)
{
        int i,j,z;
//        int p
        string msg;
        object me = this_player();        
        if (!id(arg))
        return notify_fail("你要吃什么？\n");
        
        z = random(10) + 1;
        if ( z  ) {
        msg = eat_msg[random(sizeof(eat_msg))];
        i = (int)me->query("medicine",1)*random((int)me->query("age",1)/5+10);
        j = 200+random((int)me->query("wd_job",1)/5);
        if (j > 400) j = 400;
        message_vision(msg, me);
        me->add("combat_exp",j);
        destruct(this_object());
        return 1;
        }
/*
        if ( 4 < z && z < 22 ) {
        i = (int)me->query("medicine",1)*random((int)me->query("age",1)/20+5);
        p = 250+random(100+(int)me->query("wd_job",1)/10);
        if (p > 350) p =350;
        message_vision(HIY"$N吃下一颗丹药，功行一周天，只觉浑身舒畅无比。\n"NOR, me);
        me->add("combat_exp",p);
        destruct(this_object());
        return 1;
        }
        if ( 1 < z && z < 3 ) {
        message_vision(HIB"\n$N吃下一颗丹丸,只觉一股毒力由胸间膻中穴下侵，直逼丹田，$N忙出指自点气海穴，
气机反弹，吐出一口淤血，总算无碍，功力却已是受损。\n"NOR,me);
        me->add("combat_exp",-random(60));
        me->receive_damage("qi", me->query("max_qi")/12,"误食丹药,中毒而亡");
        me->receive_wound("qi", me->query("max_qi")/12,"误食丹药,中毒而亡");
        destruct(this_object());
        return 1;
        }
        if ( z < 2 ) {
        message_vision(HIR"\n$N服下一颗丹丸,但觉腹内绞痛，毒性猛烈，待要运功相抗，已是不及。。。\n"NOR,me);
        me->add("combat_exp",-random(120));
        me->receive_damage("qi", me->query("max_qi")/8,"误食丹药,中毒而亡");
        me->receive_wound("qi", me->query("max_qi")/8,"误食丹药,中毒而亡");
        me->receive_damage("jing", (me->query("max_jing")/8),"误食丹药,中毒而亡");
        me->receive_wound("jing", (me->query("max_jing")/8),"误食丹药,中毒而亡");
        me->unconcious();
        destruct(this_object());
        return 1;
        }
*/
        else   {
        message_vision(YEL"$N服下一颗丹丸,但觉药性平平，无甚损益。\n"NOR,me);
        me->add("combat_exp",-random(20)+10);
        destruct(this_object());
        return 1;
        }
        return 1;
}

