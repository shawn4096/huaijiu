//奖励系统之书籍篇

#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "古武残篇" NOR, ({ "guwu book","book" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set_weight(300);
                set("unit", "本");
                set("long", "这是一张残缺不全的书页。\n" NOR);
                set("value", 30);
                set("no_cun", 1);
                set("no_sell", "什么世道，就一张破纸头也拿来卖钱？");
                set("material", "paper");
                set("cloned",0);
               
        }
        setup();
}

void init()
{
	add_action("do_read","read");
}

string long()
{
        string msg;

               msg = "这是一本" + name() + NOR + "，看样子"
                      "已经颇有年时了。\n页片上用隶体密密麻麻写满了蝇"
                      "头小字，似乎都和空手技能有关，\n你可以试着读读(read)看，也许对武学能够"
                      "有所帮助。\n";


        return msg;
}

int do_read(string arg)
{
        object me = this_player();

        int na = this_object()->name();
      
        if (me->is_busy())
                return notify_fail("你现在正在忙。\n");

        if (me->is_fighting())
                return notify_fail("战斗中无法研读新知。\n");

        if (arg && id(arg))
        {
                message_vision(HIW "$N" HIW "聚精会神地阅读「" NOR + na + HIW
                               "」上所记载的东西，似乎有所收获。\n" NOR, me);
                if (!me->query("sjsz_guwu")) me->set("sjsz_guwu",1);
                me->add("sjsz_guwu", 5);
                tell_object(me, HIY "你只觉以前存在的诸多疑问豁然开朗，对空手技能有了新的感悟。\n" NOR);
                destruct(this_object());
                return 1;
        }
}
