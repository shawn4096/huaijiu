// ITEM: /d/huashan/npc/obj/ling.c
// Date: Look 99/03/25

inherit ITEM;

#include <ansi.h>
void create()
{
        set_name(YEL"令牌"NOR, ({ "ling pai","ling"}));
        set_weight(10);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long",
                        "这是一枚华山派的赏善罚恶令，有了它，华山弟子在外便能时刻提醒自己赏善罚恶。\n");
                set("value", 0);
                set("material", "iron");
         }
	setup();
}
