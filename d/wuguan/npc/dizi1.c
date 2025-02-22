// dizi1 鲁坤  
// Modify By River@SJ
// Modified by snowman@SJ 22/11/2000
// 减少flood

#include <ansi.h>
inherit NPC;
string *names = ({"打扫马房", "锯木头", "劈柴", "灌溉菜地", "锄草", "挑水"});
string ask_job();
void create()
{
       set_name("鲁坤", ({ "lu kun","lu","kun", "man" }));
       set("title", "襄阳武馆大弟子");
       set("gender", "男性");
       set("age", 35);  
       set("long", "他是万震山的大弟子，也是馆主最信任的徒弟，长得赳赳昂昂。\n");
       set("combat_exp", 10000);
       set("shen_type", 1); 
       set("unique", 1);

       set_skill("force", 70);
       set_skill("strike", 70);
       set_skill("shenzhao-jing",70);
       map_skill("force", "shenzhao-jing");          
 
       set("inquiry",([
           "工作" : (: ask_job :),
           "job" : (: ask_job :),
           "工具" : "你去物品房找六弟吴坎要吧！", 
       ]));
       setup();
       carry_object(ARMOR_D("cloth"))->wear();
}

void init()
{
       object ob;
       ::init();
       if( interactive(ob = this_player()) && !is_fighting()){
               remove_call_out("greeting");
               call_out("greeting", 1, ob);
       }
       add_action("do_task","task"); 
}

string ask_job()
{
	string target;
       	object ob = this_player();
       	
       	if(ob->query_temp("job_name"))
             	return "你不是已经领了工作吗？还不快去做。";
       	if(ob->query("combat_exp") > 3000)
             	return "你功夫已经挺高了，这里没有什么适合你的工作了。";
       	if((int)ob->query_condition("wuguan_job" ) > 0 )
             	return RANK_D->query_respect(ob)+ "现在没有什么事可做，过段时间再来吧。";
        target = names[random(sizeof(names))];
       	ob->set_temp("job_name",target);
       	ob->apply_condition("wuguan_job", random(5) + 5);
       	return "正好现在有好多事要做，你先去东物品房领工具，然后去后院"+ target+ "吧。";
}

int do_task(string arg)
{
       	object ob,me;
       	int pot;
       	
       	ob = this_player();
       	me = this_object();
       	if( !arg || arg != "ok" ) return 0;
       	if( !ob->query_temp("job_name") ){
            	tell_object(ob, CYN+me->name()+"说道：“没给你工作，你怎么跑来覆命了？”\n"NOR);
            	return 1;
       	}
       	if(!ob->query_temp("mark/还了")){ 
            	tell_object(ob, CYN+me->name()+"说道：“你先把工具还给六弟，再来覆命吧。”\n"NOR);
            	return 1;
       	}
       	if(!ob->query_temp("mark/完了")){
            	tell_object(ob, CYN+me->name()+"说道：“你偷懒啊，叫你干活你不去干，跑来领功！”\n"NOR);
            	return 1;
       	}
       	if( arg=="ok" && ob->query_temp("mark/完了")){
            	command("smile "+ob->query("id"));
            	tell_object(ob, CYN+me->name()+"说道：“好，"+RANK_D->query_respect(ob)+"，做得好，这是给你的奖赏！”\n"NOR);
            	if (random(10) < 6){
              		me->add_money("coin",(int)(ob->query_skill("force",1)/2)+50);
              		command("give "+ob->query("id")+" "+((int)(ob->query_skill("force",1)/2)+50)+" coin");
            	}
            	else{
              		me->add_money("silver",(int)(ob->query_skill("force",1)/5)+1);
              		command("give "+ob->query("id")+" "+((int)(ob->query_skill("force",1)/5)+1)+" silver");
            	}
            	pot = (int)(ob->query_skill("force",1)/5)+10;
            	ob->add("potential",pot);
            	if(ob->query("potential") > ob->query("max_pot"))
                	ob->set("potential", ob->query("max_pot"));
            	ob->add("combat_exp", (pot + 30) );
            	ob->delete_temp("job_name");
            	ob->delete_temp("mark");
            	tell_object(ob,HIW"你被奖励了："+chinese_number(pot+30)+"点经验和"+chinese_number(pot)+"点潜能。\n"NOR);
            	return 1;
       	}
       return 1;
}

void greeting(object ob)
{
       	if( !ob || environment(ob) != environment() ) return;
       	if(ob->query_temp("mark/还了")
        && ob->query_temp("job_name")){ 
           	command("nod " +ob->query("id"));
           	tell_object(ob, CYN+this_object()->name()+"说道：“"+ob->name()+" 你工作做的不错，可以跟我覆命（"HIW"task ok"CYN"）了。”\n"NOR);
           	return;
       	}
       	if ( ob->query("combat_exp") < 3000 
        && !ob->query_condition("wuguan_job")
        && !ob->query_temp("job_name")) {
           	command("pat "+ob->query("id"));
           	tell_object(ob, CYN+this_object()->name()+"说道：“这位"+ RANK_D->query_respect(ob)+ "，我们这缺人手，你可以找我领工作"HIY HBCYN" ask lu about 工作 "CYN"来做。”\n"NOR);
       	}
}
