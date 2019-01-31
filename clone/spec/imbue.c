
#include <ansi.h>
#include <weapon.h>
inherit HAMMER;

void create()
{
        set_name(HIY"韦兰之锤"NOR, ({ "weilan's hammer", "chui"}));
        set_weight(6000);
        if( clonep())
               set_default_object(__FILE__);
        else {
               set("unit", "柄");
               set("long",@LONG
这是韦兰铁匠打造出传奇式的剑“乔依乌斯”所用的铁锤，可不幸被小偷窃去。
LONG
               );
               set("value", 0);
               set("no_cun", 1);
               set("no_give", 1);
               set("no_drop", 1);
               set("no_get", "这样东西不能离开那儿。\n");
               set("treasure",1);	
               set("degree",1);
               set("credit",60);
               set("material", "steel");
               set("dazao_award",1);
               set("wield_msg", "$N拿起一柄$n。\n");
               set("desc","增加一次打造机会。");
               set("unwield_msg", "$N将手中的$n放下。\n");
        }
        init_hammer(20);
}