//flowray 2005.6.16
#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(NOR + HIY "奇珍宝石" NOR, ({ "bao shi"}));
	set("long","这是大理大富之家马五德的传家之宝，你可以向他出示("HIY"show"NOR")这块宝石。\n");

	set("unit","颗");
	set_weight(100);
	set("value",3000000);
        set("no_give",1);
        set("no_drop",1);	
        set("no_get",1);
        set("no_sell",1);
	set("desc","可以到大理大富之家领取奖赏。");
        setup();
}

void init()
{
	add_action("do_show","show");   
}

int do_show(string str)
{
	
	object my_object,me = this_player(),thing = this_object();

        if (me->is_busy())
		return notify_fail("你正忙着呢！\n");
	
	if (!str)
		return notify_fail("你要把东西给谁看啊？\n");
    
	if (!(my_object = present(str, environment(me))))
		return notify_fail("你要找的人不在这里。去别处找找看吧。\n");
	
	if ( str != "ma wude")
		return notify_fail("这个东西不能随便给别人看的！\n");
    
	if (!living(my_object))
		return notify_fail("哦，你得先把他弄醒在说。\n");
	
	if (me->query_temp("token/maker"))
		return notify_fail("先把你身上的一个送出去再说吧。\n");
        me->add_busy(5+random(3));

	write("马五德一把夺过宝石，道：“这位" + RANK_D->query_respect(me) + "，没想到你真能将它取回来！”\n"NOR);
        if (random(10)) {
                write("马五德仔细辨别了一翻，颤声道：“这...这是个赝品啊，你是不是拿错了！”\n");
                write("马五德叹道：“命里无时别强求，也罢。为了感谢" + RANK_D->query_respect(me) + "深入虎穴，这点黄金你就收下吧。”\n");
                MONEY_D->pay_player(me, 50 * 10000);
                destruct(thing);
	        return 1;
        }
        else {
                write("马五德道：“为了略表谢意,这里有几样小东西您就任选一个吧,千万别客气！”\n");
	        write("马五德到内堂拿出几样东西摆在你的面前。\n");
	        write(HIM"紫水晶项链"NOR"(necklace),"HIW"白金钻戒"NOR"(ring),"HIG"翡翠玉镯"NOR"(bangle),"+
				HIR"龙凤玉佩"NOR"(jade),"HIY"黄金发饰"NOR"(headgear)\n");	
	        write("你要选什么呢：");            
	        input_to("choose_item", me);
                return 1;
        }
}	 

private void choose_item(string arg, object me)
{
	object ob;
	if (arg!="necklace" && arg!="ring" && arg!="jade" && arg!="bangle" && arg!="headgear")
	{
		write("看清楚点到底要选什么：");
		input_to((: choose_item :), ob,me);
		return;
	}
	
	me->set_temp("token/maker",1);
	ob=new("/clone/gift/item/box.c");
	ob->set("token/id",arg);
	

	switch(random(3)+1)
	{
		case 1:
			ob->set("token/parry",1+random(30));
			break;
		case 2:
			ob->set("token/dodge",1+random(30));			
			break;
		case 3:
			ob->set("token/armor_vs_force",1+random(30));			
			break;
	}

	write("你要在刻上什么赠言：");
	input_to("desc_item", me,ob);
	return; 
}

private void desc_item(string arg, object me,object ob)
{
	if (!strlen(strip(arg))) 
	{
		write("你到底要刻的什么内容啊？");
		input_to((: desc_item :),me,ob);
		return;
	}

	arg = explode(arg+"\n", "\n")[0];
	arg = replace_string(arg, "$RED$", RED);
	arg = replace_string(arg, "$GRN$", GRN);
	arg = replace_string(arg, "$YEL$", YEL);
	arg = replace_string(arg, "$BLU$", BLU);
	arg = replace_string(arg, "$MAG$", MAG);
	arg = replace_string(arg, "$CYN$", CYN);
	arg = replace_string(arg, "$WHT$", WHT);
	arg = replace_string(arg, "$HIR$", HIR);
	arg = replace_string(arg, "$HIG$", HIG);
	arg = replace_string(arg, "$HIY$", HIY);
	arg = replace_string(arg, "$HIB$", HIB);
	arg = replace_string(arg, "$HIM$", HIM);
	arg = replace_string(arg, "$HIC$", HIC);
	arg = replace_string(arg, "$HIW$", HIW);
	arg = replace_string(arg, "$NOR$", NOR);
	if (strlen(strip(arg)) > 40)
	{
		write("赠言还是要简短一点,请重新输入:");
		input_to((: desc_item :),me,ob);
		return;
	}
	arg = " "+arg+NOR+"   「"+me->query("name")+"("+me->query("id")+") 谨赠」";
	ob->set("token/desc",arg);
	write("片刻马五德就在你要的东西上刻好了赠言,把它装在一个"HIW"水晶盒子"NOR"里交给你。\n");
	ob->move(me);
        me = this_player();
        ob = present("bao shi",me);
        destruct(ob);
}
