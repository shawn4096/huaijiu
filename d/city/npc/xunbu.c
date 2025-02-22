// xunbu.c 巡捕
#include <ansi.h>
inherit NPC;
string ask_me();
void create()
{
	set_name("巡捕", ({ "xunbu"}));
	set("gender", "男性");
	set("age", random(10) + 30);
	set("str", 25);
	set("dex", 16);
	set("long", "他站在那里，的确有说不出的威风。\n");
	set("combat_exp", 500000);
	set("shen_type", 1);
	set("attitude", "peaceful");

	set_skill("unarmed", 100);
	set_skill("blade",100);
	set_skill("force", 100);
	set_skill("sword", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 70);
	set_temp("apply/damage", 50);

	set("neili", 1000); 
	set("max_neili", 1000);
	set("jiali", 50);
	
	        set("inquiry", 
                ([
                        "通缉犯"  : (: ask_me :),                       
                ]));

	setup();
	carry_object("/d/city/obj/gangdao")->wield();
	carry_object("/d/city/obj/yayifu")->wear();
	if (clonep()) call_out("randommove", 10);
}

void init()
{
        object ob;

        ::init();
	ob = this_player();
        if( ob->query_condition("killer") && userp(ob) ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
	}
}
void greeting(object ob)
{
        object me;

        me=this_object();
	if (is_fighting()) return;
	if (wizardp(ob)) return;
        if(interactive(ob) && !ob->is_fighting() && ob->query_condition("killer")) 
	{
		me->set("killer_name",ob->query("name"));
            	call_out("do_kill", 0, me, ob);
	}
}

int do_kill(object me,object ob)
{	
	if(me->is_fighting()) return 0;
	if (wizardp(ob)) return 0;
        if( objectp(ob) && present(ob, environment(me))
                 && !environment(me)->query("no_fight"))
	{	if (!me->query_temp("marks/杀1")){
			command("look "+ob->query("id"));
			message_vision(CYN "$N对$n说道：杀了人，就要偿命，"
				+RANK_D->query_rude(ob)+"，你赶快受死吧！\n" NOR, me,ob);
			me->set_temp("marks/杀1",1);
		}
		me->set_leader(ob);
                me->kill_ob(ob);
		call_out("checking", 0,  me);   
	}

	else
                call_out("waiting", 1, me);     
        return 1;
}
int waiting(object me)
{
	object ob;
	
	if ( objectp(ob) )
	{
		if (ob->is_ghost())
		{
			me->delete_temp("marks/杀1");
			call_out("do_back", 1, me);
			return 1;
		}else if (me->is_fighting() && present(ob, environment(me)))
		{
			call_out("checking", 0, me);
			return 1;
		}
	}		
	
	remove_call_out("waiting");
	call_out("waiting", 60, me);
    return 1;
}

int checking(object me)
{
	object ob;
	
	if (me->is_fighting()) 
	{
		call_out("checking", 1, me);
        return 1;
	}
	if( objectp(ob = present("corpse", environment(me)))
		 &&ob->query("victim_name") ==me->query("killer_name") )
	{
		command("say 唉，终于杀了一个通缉犯，真累呀，还是先回去交差吧。");
		me->delete("killer_name");
		this_object()->delete_temp("marks/杀1");
		call_out("do_back", 1, me);
        return 1;
	}
	call_out("waiting", 0, me);
	return 1;
}
int do_back(object me)
{
	me=this_object();
	message("vision", "巡捕杀气腾腾的离开了。\n", 
		environment(), me );
	me->move("/d/city/guangchang");
	message("vision", "巡捕杀气腾腾的走了过来。\n", 
		environment(), me );

	me->set_leader(0);
	return 1;
}
void randommove()
{
	call_out("randommove", 10);
	if (living(this_object()) && !is_fighting()) random_move();
}
string ask_me()
{
	object ob=this_player();
	if(ob->query_condition("killer")>0)
		return "哼，通缉犯就是你自已，你还是乖乖的受死吧！";
	if(ob->query("shen")<=-100){
		write("巡捕正盯着你看，不知道打些什么主意。\n");
		return RANK_D->query_respect(this_player()) + 
                "，很对不起，不能告诉你，不过我看你样子倒很象通缉犯。";
	}
	if(ob->query("shen")>-100){
		write("巡捕在你耳边悄悄的说道，"+FINGER_D->get_killer());
                message("vision","巡捕悄悄的在"+ob->name()+"耳边说了几句话。\n",
                        environment(ob), ({ob}) );
		return "天子犯法，与庶民同罪。杀了人，就要偿命！";
	}	
}
