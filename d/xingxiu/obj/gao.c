inherit ITEM;

#include <ansi.h>


int do_chang(string);

void create() 
  {
   set_name(HIY "四虫膏" NOR,({"gao"}));
   set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
   set("long","一包花花绿绿的"+this_object()->query("name")+"，来尝尝(chang)味道？\n");
   set("unit","包");
	set("no_drop", 1);
	set("no_get", 1);
	}
   setup();
  }

void init()
{
  add_action("do_chang", "chang");
}

int do_chang(string arg)
  {
  	
   object me=this_object();
   object who=this_player();
   mapping fam=who->query("family");
          if( who->is_busy()) return notify_fail("你正忙着呢。\n");
   if( !this_object()->id(arg) ) return notify_fail("你想尝啥？\n");
   message_vision("$N端起"+me->query("name")+"啊呜一口的吃了下去。\n", who);
   if (!fam || fam["family_name"] !="星宿派"){
                return notify_fail("你不是星宿弟子，吃了这"+me->name()+"会中毒的。\n");
        }
   if ( me->query("prices")<= 0 || me->query("xx/owner")!=who)  message_vision("但什么滋味也没尝出来。\n", who);
   else if (who->query("combat_exp") > 2000000 || who->query_skill("huagong-dafa", 1) < 10)
     {
      message_vision("$N只感到一阵恶心，天旋地转。\n", who);
      who->unconcious();
     }
   else 
     {
      message_vision("$N苦得涕泪横流，强忍着没吐出来。\n", who);
      //who->improve_skill("force", me->query("prices"));
      tell_object(who,"你只感到腹内如有数十把小刀在乱攒乱刺，你使尽了力气，"
         +"才将毒药的药力完全化解。\n");
      who->add("combat_exp",me->query("prices"));
        who->add("potential",me->query("prices")/4);
         who->add("xx_job4",4);
        if(who->query("potential") > who->query("max_pot")) 
                who->set("potential",who->query("max_pot"));
      tell_object(who, YEL "你的经验和潜能各增加了"
         +chinese_number(me->query("prices"))+"点！\n" NOR);
      log_file( "job/xx_job4",sprintf("%s %s(%s)第%d次任务结束，得到潜能和经验：%d。\n",
                ctime(time())[4..19],who->name(),who->query("id"),who->query("xx_job4"),me->query("prices")) );
     } 
   destruct(me);
   return 1;
  }

