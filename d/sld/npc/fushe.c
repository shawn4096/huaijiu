inherit NPC;

void create()
{
    set_name("腹蛇", ({ "fu she" }) );
    set("race", "野兽");
    set("age", 20);
    set("long", "这是一条有剧毒的腹蛇，它似乎对你不太友好。\n");
    set("attitude", "peaceful");
	
	set("limbs", ({ "头部", "身体", "七寸", "尾巴" }) );
	set("verbs", ({ "twist", "bite" }) );

	set("combat_exp", 80000);
	
	set_temp("apply/attack", 110);
	set_temp("apply/defense", 110);
	set_temp("apply/damage", 110);
	set_temp("apply/armor", 110);

	setup();
}

void init()
{
      object me,ob;
      object* inv;
      int i;
      mapping myfam;

      ::init();
      me=this_player();
      myfam = (mapping)me->query("family");
      if(interactive(me) && (!myfam || myfam["family_name"] != "神龙教" || me->query("xionghuangjiu")!=1 ))
      {
         //ob=this_object();
         inv = all_inventory(me);
	   for(i=0; i<sizeof(inv); i++)       
	       if(inv[i]->query("id")=="xiong huang")
       	    break;
      	   if(i>=sizeof(inv))      
          {
              remove_call_out("kill_ob");
              call_out("kill_ob", 1, me); 
	          //ob->kill_ob(me);
       	   //me->kill_ob(ob);
	    }
      }
}

int hit_ob(object me, object victim, int damage)
{
        victim->apply_condition("snake_poison",
                victim->query_condition("snake_poison") + 8);
        return 0;
}

 