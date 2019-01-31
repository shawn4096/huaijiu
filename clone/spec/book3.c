//奖励系统之书籍篇

#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "嵩山剑残篇" NOR, ({ "songshan book" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set_weight(300);
                set("unit", "本");
                set("long", "这是一张残缺不全的书页。\n" NOR);
                set("value", 30);
                set("no_cun", 1);
                set("no_give", 1);
                set("no_drop", 1);
		set("no_get", "这样东西不能离开那儿。\n");
		set("treasure",1);
                set("material", "paper");
                set("degree",1);
                set("credit",50);
                set("desc","全面掌握嵩山剑法的解密物品。");
               
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
                      "头小字，记载着一些与嵩山剑法绝技之龙吟凤翔有关的内容，\n你可以试着读读(read)看，也许对武学能够"
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

        if (me->query("ss/pass_deng"))
                return notify_fail("你都学会了，还想知道什么？\n");

        message_vision(HIW "$N" HIW "聚精会神地阅读「" NOR + na + HIW
                               "」上所记载的东西，似乎有所收获。\n" NOR, me);

        tell_object(me, HIY "你始终无法参透页片上所载内容，不过页片上不断提及的邓八公(Deng bagong)引起了你的注意。\n" NOR);
        me->set_temp("ss/zsb_0",1);
        destruct(this_object());
        return 1;

}
