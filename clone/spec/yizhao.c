//ilovemin 2013.12.11
#include <ansi.h>

string long();

inherit ITEM;

void create()
{
	set_name (HIR"大燕国遗诏"NOR, ({ "dayan yizhao"}));
	set("long","这是一封大燕国遗诏。\n");
	set("unit","封");
	set_weight(200);
	set("value",30);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "这样东西不能离开那儿。\n");
	set("treasure",1);	
	set("degree",1);
        set("desc","姑苏慕容之刀剑双绝的解密物品。");
	set("credit",50);
	setup();
}

void init()
{
	add_action("do_use","read");
  
}

string long()
{
        string msg;

               msg = "这封大燕国遗诏是大燕国湮灭前的传国诏书，里面提到了关于玉玺的下落。\n"
                      "你觉得应该仔细研读（read）一下为好。\n";

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
                message_vision(HIW "$N" HIW "仔细地研读着大燕国遗诏。\n" NOR, me);
                tell_object(me, HIY "你已经知晓了玉玺所在，快点行动吧。\n" NOR);
                me->set_temp("djsj",1);
                destruct(this_object());
                return 1;
                
        }
}	 