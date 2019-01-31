//flowray 2005.6.20
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIG"小树枝"NOR, ({ "xiao shuzhi"}));
	set("long","这是一枝小树枝。\n");
	set("unit","枝");
	set_weight(100);
	set("value",30);
        set("no_cun", 1);
        set("no_drop", 1);
        set("no_give", 1);
	set("no_get", "这样东西不能离开那儿。\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","双手互搏的解密物品。");
	set("credit",50);
	setup();
}

void init()
{
	add_action("do_use","use");
  
}

string long()
{
        string msg;

               msg = "这是一枝" + name() + NOR + "，估计是哪个淘气的孩子刚刚折断的。\n"
                      "手持树枝，你不禁想用(use)它在沙盘上肆意涂鸦一翻。\n";

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
                message_vision(HIW "$N" HIW "童心未泯，双手各持一段小树枝，在沙盘中画了两个大猪头。\n" NOR, me);
                tell_object(me, HIY "你感觉双手灵活多了。\n" NOR);
                me->set_temp("hubo",1);
                destruct(this_object());
                return 1;
                
        }
}	 