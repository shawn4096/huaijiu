// by cool 980719
// Modify By River 98/12
#include <ansi.h>
inherit ITEM;
void init()
{
        add_action("do_du", "read");
     	add_action("do_fan", "fan");	
     	add_action("do_fan", "find");
	add_action("do_lingwu", "study");
        add_action("do_lingwu", "lingwu");
}

void create()
{
        set_name(HIW"帛卷"NOR, ({ "bo juan", "bojuan", "book"}));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "一本烂的不成样子的帛制长卷。\n"); 
                set("unique", 1);
                set("treasure", 1);
                set("material", "silk");
                set("no_drop", "这样东西不能离开你。\n");
                set("no_get", "这样东西不能离开那儿。\n");
        }
}

int do_du(string arg)
{
        object me = this_player();
        if (!(arg=="bo juan" || arg == "bojuan" || arg == "book"))
        return 0;
        if( me->is_busy()) 
            return notify_fail("你现在正忙着呢。\n");
        if( me->is_fighting() ) 
            return notify_fail("你无法在战斗中专心下来研读新知！\n");
        if(!id(arg))
             return notify_fail("你要读什么？\n");
        if(!me->query("dali/meet_dy1"))
             return notify_fail("帛卷撕的乱七八糟，什么都看不清，你无法从里面学到东西。\n");
        if(!me->query_temp("book", 1))
             return notify_fail("帛卷撕的乱七八糟，什么都看不清，你无法从里面学到东西。\n");
	if((int)me->query("jing") < 25 )
             return notify_fail("你现在过于疲倦，无法专心下来研读新知。\n");        
	if((int)me->query("neili") < 35 )
             return notify_fail("你内力不够，无法专心下来研读新知。\n");        
        if((int)me->query_int() < 34)
             return notify_fail("你的悟性不足钻研这么高深的武功。\n");
        if((int)me->query_skill("literate", 1) < 100)
             return notify_fail("你看不懂这上面所写的文字。\n"); 
        if((int)me->query("max_neili") < 1200 )
             return notify_fail("你内力修为不够，无法钻研这么高深的武功。\n");
        if((int)me->query("combat_exp")< 200000)
             return notify_fail("你的实战经验不够，无法钻研这么高深的武功。\n"); 
        if( me->query_skill("lingbo-weibu", 1) > 60)
	     return notify_fail("你研读了一会儿，觉得书上讲的步法，如果不身体力行的练习是无法领会的。\n");
          me->receive_damage("jing", 15);
          me->add("neili",-(int)me->query_skill("lingbo-weibu", 1)/2);  
          me->improve_skill("lingbo-weibu", (int)me->query_skill("literate", 1)/3+1);
          write("你仔细研读着帛卷上的步法。\n");
         return 1;
}

int do_fan(string arg)
{
       object me = this_player();
       int i;        		       
       if (!(arg=="bo juan" || arg == "bojuan" || arg == "book"))
           return 0;
       if ( me->is_busy()) 
           return notify_fail("你现在正忙着呢。\n");
       if( me->is_fighting() ) 
           return notify_fail("你无法在战斗中做这个事情。\n");
       if (!id(arg))
           return notify_fail("你要翻什么？\n");
       if( me->query_temp("book"))
           return notify_fail("你已经找到你想要的了。\n");
       if (me->query_temp("find") < 3 ){
         write("你仔细翻看着被撕的破烂的帛卷，希望能从中找出点什么。\n");
         me->add_temp("find", 1);         
         return 1;
         }
	//如果已经通过，直接成功
  if(me->query("dali/pass1"))
  {
	tell_object(me,"你翻到最后，不由得大为狂喜，这部分并没有被撕烂，题着“凌波微步”四字，\n"+
		"其后绘的是无数足印，注明“妇妹”、“无妄”等等字样，尽是易经中的方位。\n"+
		"只见足印密密麻麻，不知有几千百个，自一个足印至另一个足印均有绿线贯串，\n"+
		"线上绘有箭头，料是一套繁复的步法。最后写着一行字道：“猝遇强敌，以此 \n"+
		"保身，更积内力，再取敌命。”\n");
	me->set_temp("book", 1);
  return 1;
  }
  
  //增加标记
  me->set("lbwb/time",time());
  me->delete_temp("find");

  //难度与玩家先天悟性直接相关
  //详细记录log
 
  i = 1;
  if((me->query("int")-25) > 1) i = me->query("int")-24 ;

  if(random(200)<i)
  {
	   tell_object(me,"你翻到最后，不由得大为狂喜，这部分并没有被撕烂，题着“凌波微步”四字，\n"+
		"其后绘的是无数足印，注明“妇妹”、“无妄”等等字样，尽是易经中的方位。\n"+
		"只见足印密密麻麻，不知有几千百个，自一个足印至另一个足印均有绿线贯串，\n"+
		"线上绘有箭头，料是一套繁复的步法。最后写着一行字道：“猝遇强敌，以此 \n"+
		"保身，更积内力，再取敌命。”\n");
	   me->set_temp("book", 1);
	   me->set("dali/pass1",1);
           tell_object(me,HBYEL"\n你于"+NATURE_D->game_time()+"终于解开凌波微步。\n\n");
           log_file("quest/lbwb",sprintf("%s %s(%s)，从帛卷中领悟到凌波微步。\n",
                                  ctime(time())[4..19], me->name(1),capitalize(getuid(me)) ));
  }
  else
  {
	   tell_object(me,HIC"你翻到最后，不由一阵失望，这部分虽然没有完全被撕烂，还隐约题着“凌波微\n"+
		             "步”四字，但是其后绘的似乎是无数足印，全然无法辨。你顺手把帛卷丢掉了。\n"NOR);
           log_file("quest/lbwb",sprintf("%s %s(%s)，从帛卷中领悟凌波微步失败。\n",
                                  ctime(time())[4..19], me->name(1),capitalize(getuid(me)) ));
	   me->delete_temp("find");
           tell_room(environment(me),HIC"\n"+me->name()+"顺手丢掉一卷东西。\n"NOR, ({ me }));
	   destruct(this_object()); 
  }
	return 1;	    
}

int do_lingwu(string arg)
{
	object me = this_player();
	int level, jingcost;
        if ( !arg ) return 0;
        if (!(arg == "bo juan" || arg == "bojuan" || arg=="book"))
	   return notify_fail("你要学什么？\n");
        if ( me->query("int") < 22)
           return notify_fail("你先天悟性过低，终身无法领悟凌波微步。\n");
	
        level = me->query_skill("lingbo-weibu", 1);

	if (level > me->query_skill("dodge", 1))  
           return notify_fail("你先打好轻功的根基吧！\n");
	if ( !me->is_fighting())
           return notify_fail("你觉得必须在战斗中领悟。\n");
        if ( level <= 100 ) {
	  jingcost = level / 3 + random(level / 3);
	if (me->query("jing") <= jingcost)
           return notify_fail("你太疲倦了，先歇歇吧！\n");
        if (me->query("neili") < 20)
           return notify_fail("你的内力不够，先歇歇吧！\n");
          me->receive_damage("jing", jingcost);
          me->add("neili",-random(20));
	  me->improve_skill("lingbo-weibu", (int)me->query_skill("literate", 1)/3+1);
	  message_vision("$N战斗中闭上双眼，回想着帛卷上的步法。\n", me);
	  return 1;
	  }
      return notify_fail("你已经把书中的精髓都领悟到了。\n");
}
