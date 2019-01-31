//ilovemin 2013.12.11
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIR"钟灵的花鞋"NOR, ({ "xiuhua xie"}));
	set("long","这是一双绣花鞋。\n");
	set("unit","双");
	set_weight(200);
	set("value",30);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "这样东西不能离开那儿。\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","凌波微步的解密物品。");
	set("credit",50);
	setup();
}

void init()
{
	add_action("do_use","mail");
  
}

string long()
{
        string msg;

               msg = "这双绣花鞋是钟灵交付给段誉前往万劫谷寻找救兵的信物。\n"
                      "看来是段誉在路上遗失了，你最好尽快通过驿站邮寄(mail)出去。\n";

        return msg;
}

int do_use(string arg)
{
        object me = this_player();
    
        if (me->is_busy())
                return notify_fail("你现在正在忙。\n");

        if (me->is_fighting())
                return notify_fail("你还是安心战斗吧。\n");

        if (arg && id(arg))
        {
                message_vision(HIW "$N" HIW "扬手招来一匹快马，将绣花鞋邮递了出去。\n" NOR, me);
                tell_object(me, HIY "你感觉浑身充满了正能量。\n" NOR);
                me->set_temp("duanyu/ok",1);
                destruct(this_object());
                return 1;
                
        }
}	 