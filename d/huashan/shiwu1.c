// Room: /d/huashan/shiwu1.c
// Date: Look 99/03/25

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "石屋");
	set("long", @LONG
一间不见日光的石室，墙壁上镶嵌着几枝松油火把，使室内满是昏黄的光
晕。给人的唯一感觉，也许可以让人在此静心领悟无上的剑法绝诣。
LONG
	);

	set("exits", ([ /* sizeof() == 3 */
	       "east" : __DIR__ "jiabi",
           ]));
   	setup();
}

 void init()
{
    add_action("do_lingwu","comprehend");
}

int do_lingwu(string arg)
{
    object me=this_player();
    int sl,dl;
    if (arg!="sword") return notify_fail("你要领悟什么？\n");
         if(!me->query("fengset")) return notify_fail("你非风老前辈的弟子，怎能在此领悟？\n");
    if (me->is_busy() || me->is_fighting()) return notify_fail("你正忙着呢。\n");
     sl=(int)me->query_skill("sword",1);
     dl=(int)me->query_skill("dugu-jiujian",1);
     if (!dl)
     return notify_fail("你连独孤九剑的总诀式都没听说过，瞎领悟什么?\n");
       if (sl > me->query("jing") || me->query("jing")*100/me->query("max_jing") < 50) {
                me->receive_damage("jing",sl/2);
                return notify_fail("你没办法集中精神。\n");
        }
if (dl>=150)
        	{
                if (((int)me->query("max_pot") - 100 - (int)me->query_skill("huashan-jianfa",1) < dl) && dl < 350)
	                return notify_fail("学习独孤九剑需心无旁骛，看来你的华山剑法旧习太深，无法继续领悟更高深的剑法了。\n");
		}
      if (sl < dl)
      return notify_fail("你的基本剑法造诣不够，无法领悟更深一层的独孤九剑剑意。\n");
      if((int)me->query("potential", 1) < 5 )
      return notify_fail("你现在的潜能不足以领悟独孤九剑。\n");
      write(CYN"你默默念道:归妹趋无妄，无妄趋同人，同人趋大有。甲转丙，
           丙转庚，庚转癸。子丑之交，辰巳之交，午未之交。风雷是一变，
           山泽是一变，水火是一变。乾坤相激，震兑相激，离巽相激。
           三增而成五，五增而成九……。\n"NOR);
     if( me->query_skill("dugu-jiujian",1 ) < 200)
     me->add("potential", -random(5));
     me->improve_skill("dugu-jiujian", random(me->query_int())*10+1);
     me->start_busy(random(2));
     return 1;
 }
