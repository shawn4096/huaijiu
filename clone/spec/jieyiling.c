//flowray 2005.6.20
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIR"结义令"NOR, ({ "jieyi ling"}));
	set("long","一枚效仿当年刘备、关羽和张飞桃园结义而制造的令牌。\n");
	set("unit","枚");
	set_weight(100);
	set("value",30);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "这样东西不能离开那儿。\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","与周伯通结义的解密物品。");
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

               msg = "这是一枚" + name() + NOR + "，看样子"
                      "已经颇有年时了。\n若想与人结义，你必须事先使用(use)令牌。\n";

        return msg;
}

int do_use(string arg)
{
        object me = this_player();

        int na = this_object()->name();
      
        if (me->is_busy())
                return notify_fail("你现在正在忙。\n");

        if (me->is_fighting())
                return notify_fail("你还是安心战斗吧。\n");

        if (arg && id(arg))
        {
                message_vision(HIW "$N" HIW "手持「" NOR + na + HIW
                               "」，焚香而拜说誓曰，皇天后土，实鉴此心，背义忘恩，天人共戮！\n" NOR, me);
                tell_object(me, HIY "你觉得豪气上涌，只想寻找志同道合之人，纵横江湖快意恩仇。\n" NOR);
                me->set_temp("jieyi",1);
                destruct(this_object());
                return 1;
                
        }
}	 