// Update by looklove at 2000/8/25
//Modify by Looklove for add log_file at 2000/9/1
// Last Modify by Looklove 2000/10/22 fixed fangqi's bug
// Modified by darken@SJ

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

string do_ask();
string do_cancel();
string do_ask_hb();
string do_ask_grj();
string do_ask_times(object who);
string do_pay();

void create()
{
	object ob;
	
	set_name("左冷禅", ({ "zuo lengchan", "zuo", "lengchan" }));
	set("nickname", HIR"五岳剑盟盟主"NOR);
	set("long", "嵩山掌门左冷禅更是当今武林中了不起的人物，武功固然出神入化，
		为人尤富机智，机变百出，江湖上一提到“左盟主”三字，无不惕然。\n");
	set("gender", "男性");
	set("age", 52);
	set("per", 20);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 29);
	set("int", 28);
	set("con", 28);
	set("dex", 28);
	set("unique", 1);
	set("no_bark",1);
	
	set("max_qi", 4300);
	set("max_jing", 2800);
	set("eff_jingli", 3000);
	set("jiali", 50);
	set("combat_exp", 2800000);
	set("shen", -18000);
	set("max_neili", 8000);
	set("neili", 10000);

	set_skill("force", 290);
	set_skill("hanbing-zhenqi", 300);
	set_skill("dodge", 290);
	set_skill("zhongyuefeng", 290);
	set_skill("hand", 300);
	set_skill("songyang-shou", 300);
	set_skill("parry", 300);
	set_skill("sword", 290);
	set_skill("songshan-jian", 290);
	set_skill("literate", 200);
	map_skill("force", "hanbing-zhenqi");
	map_skill("dodge", "zhongyuefeng");
	map_skill("hand", "songyang-shou");
	map_skill("parry", "songshan-jian");
	map_skill("sword", "songshan-jian");
	prepare_skill("hand", "songyang-shou");
	set("inquiry", ([
//		"补偿": (: do_pay() :),
		"job": (: do_ask :),
		"任务": (: do_ask :),
		"cancel": (: do_cancel :),
		"放弃": (: do_cancel :),
		"这个": (: do_ask_hb :),
		"次数": (:do_ask_times :),
		"功劳": (:do_ask_times :),
		"观日剑": (:do_ask_grj :),
	]));
	create_family("嵩山派", 3, "掌门人");
	set("chat_chance_combat", 20);
	set("chat_msg_combat", ({
		(: perform_action, "sword.feiwu" :),
		(: perform_action, "hand.hanbing" :),
		(: exert_function, "juhan" :),
		(: exert_function, "hanbing" :),
	}));

	setup();
	if (clonep()) {		
		ob = unew(BINGQI_D("sword/guanri-jian"));	       
		if (!ob) ob = unew(BINGQI_D("gangjian"));
		ob->move(this_object());
		ob->wield();
		carry_object(ARMOR_D("changpao1"))->wear();
		carry_object(MEDICINE_D("tianwang"));
	}	   
	add_money("gold", 2);
}

void attempt_apprentice(object ob)
{
	if(ob->query_skill("hanbing-zhenqi",1) < 150 ||
	ob->query_skill("songshan-jian",1) < 150 ||
	ob->query_skill("songyang-shou",1) < 150){
		command("say 你的武功还不够娴熟，再回去练练吧。");
		return;
	}
	if ((int)ob->query("songshan_points") < 300) {
		command("say 你自从入我派以来，偷懒耍滑，不务正业，还想拜我为师？");
		return;}
 command("say 好，我正想找些优秀弟子来亲自传授武功，看来你还不错嘛。");
	command("recruit " + ob->query("id"));
}

string do_cancel()
{
	object me;
	int exp;

	me = this_player();
	exp = me->query("combat_exp");
	
	if(!me->query_temp("quest") || me->query_temp("quest/family") != "嵩山派")
		return "你没有领任务,和我嚷嚷什么?";
	
	me->clear_condition("job_busy");
	me->add("combat_exp",-(20+random(50)));
	if(exp > 500000){
	      me->add("combat_exp",-(10+random(40)));
	}
	me->apply_condition("job_busy",6+random(4));
	me->delete_temp("songshan_job");
	me->delete_temp("quest");
	return "既然你干不了也没关系,再去刻苦练功吧,以后再来为我们的并派大计出力!";
}

string do_pay()
{
	object me = this_player();
	mapping fam;

	fam = me->query("family");
	if (!fam || fam["family_name"] !="嵩山派")
	   return RANK_D->query_respect(me)+"不会是想转派吧？BBB 可是不会准许的。\n";
	if( me->query("ss/rec") )
	   return RANK_D->query_respect(me)+"还想要补偿？这个一人只能要一次。\n";

	   me->set_skill("hand", me->query("max_pot") - 100);
	   me->set_skill("force", me->query("max_pot") - 100);
	   me->set_skill("sword", me->query("max_pot") - 100);
	   me->set("ss/rec", 1);

	return  "好了，你的基本内功、剑法、手法我都给你升到目前经验上限了，别再去烦 hunthu 跟 darken 了。\n" ;
}

string do_ask()
{
	object me, ob;      
	string type, t;
	mapping quest;
    
	me = this_player();
	ob = this_object();
    
	if(is_busy()) return "我正忙着呢，你等等。";
  
	if(me->query("combat_exp")>6000000)
		return "你的功夫这么高，不用你跑腿了。";

	if( me->query("combat_exp") < 100000 
	|| me->query("shen") > -1000)
		return RANK_D->query_respect(ob)+"我看你手脚散漫，行动迟缓，再加满脸稚气。怎能放心让你去办大事呢？";
    
	if( me->query("job_name") == "嵩山并派")
		return "嗯，我现在正在思考并派大计，你别打扰。";
 
	if( me->query_temp("quest/id")&& me->query_temp("songshan_job"))
		return "不是让你去"+me->query_temp("quest/type")+me->query_temp("quest/name")+"了吗，怎么还在这里？";
       
	if( me->query_condition("job_busy"))
		return "嗯，我现在忙，你别打扰。"; 
     
	type = random(2)?"请":"杀";

	// get a random npc from TASK_D.
	if(!mapp(quest= TASK_D->get_quest(me, 0, type, "嵩山派"))) 
		return "嗯，我现在正在思考并派大计，你别打扰。"; 
	    
	me->set_temp("quest", quest);
	me->apply_condition("job_busy", 25+random(30));    
	t = TASK_D->get_time(quest["time"]);   // get time limit.
    
	me->set_temp("songshan_job", 1);
	me->set("job_name", "嵩山并派");
	if(type == "杀"){
	    command("grin");
	    command("say 你听好了，有弟子回报"+quest["name"]+"这人对我五岳并派之举深表不满，那么。。。");
	    return "嘿嘿，他在"+quest["place"]+CYN"一带，你去将他杀了，务必在"+t+CYN"之前带着他的尸体赶回来。\n";
	}
	else{
	    command("nod");
	    command("say 对了，"+quest["name"]+"和我交情不错，如得他相助，五岳并派之事简直易如反掌。");
	    return "你就代表我去"+quest["place"]+CYN"邀请他，务必在"+t+CYN"之前赶回来。\n";    
	}   
}

int accept_object(object who, object ob,object me)
{
       int type,count,exp,pot;
       me=this_object();
       
       // check job.
       
       if( who->query_temp("quest/family") != "嵩山派")
		    return 0;
			
       type = TASK_D->is_target(ob, who);
       switch (type){
	    case 0: command("say 你拿个"+ob->name()+"给我干嘛？");
		    return 0;
	    case -1:command("say 耶？让请人你不去，倒杀人丢脸去了，滚开！");
		    return 0;
	    case -2:command("say 嘿嘿，谁让你去乱杀人了？简直是给我嵩山派抹黑！");
		    who->apply_condition("job_busy", 40);
		    return 0;
	    case -3:command("say 嗯，这么久才办完，你干什么去了？给我滚一边去！");
		    who->apply_condition("job_busy", 30);
		    return 0;
	    case -4:command("say 哦，这是个同名同性的人，算他倒霉吧！");
		    return 0;
	    default:command("haha");
		    command("say 好！好！你办事不错，是块好料子。");
		    message_vision("\n$N给$n讲解一些武学上的疑难，$n若有所思地点着头。\n",me, who);
		    // give rewards.
		    TASK_D->give_reward(who, who->query_temp("quest"), -1);
	
	who->add("songshan_points", 1);
	who->apply_condition("job_busy",2+random(5));
	who->delete_temp("songshan_job");
	
	count = who->query("songshan_points");
	if (count<1) count=1;
	pot= who->query_temp("quest/pot_reward");
	exp= who->query_temp("quest/exp_reward");
	who->delete_temp("quest");

	log_file( "job/ss_job",sprintf("%s %s(%s)第%d次嵩山杀人任务获得%d点经验，%d点潜能，经验：%d\n",
	ctime(time())[4..19],who->name(),who->query("id"),count,exp,pot,who->query("combat_exp")));
		    
	who->add("songshan_points", 1);
	call_out("destroy", 1, ob);
	return 1;
	    }
      return 1;
}

void destroy(object ob)
{
	destruct(ob);
}

void init()
{       
	object ob;
	ob = this_player();

	::init();
	ob->delete_skill("hanbing-shenzhang");
	ob->delete_skill("songyang-bian");
	ob->delete_skill("songyang-zhang");
	if( interactive(ob = this_player()) && !is_fighting() && !is_busy()
	   && ob->query_temp("quest/family") == "嵩山派"
	   && ob->query_temp("quest/type") == "请") {
		remove_call_out("greeting");
		call_out("greeting", 2, ob);
	}
}

void greeting(object me)
{
	object target, ob;
	mapping quest;
	
	if( !me || environment(me) != environment() || !living(me)) return;
	
	if (!mapp(quest = me->query_temp("quest")) || quest["type"] != "请"
	|| !stringp(quest["id"])) return;
	
	command("nod "+me->query("id"));
	
	ob = this_object();
	
	if(objectp(target=present(quest["id"], environment(me)))
	  && target->query_temp("songshan_job") == me
	  && living(target)){
		me->add_busy(2);
		target->set_leader(0);
		command("haha");
		command("touch "+target->query("id"));
		command("say "+target->name()+"能来，我嵩山派又多了一份力量啦！哈哈！");
		/*
		if ( quest["time"] < time()) {
			command("say 嗯，"+me->name()+CYN"你这么久才办完，你干什么去了？给我滚一边去！");
			me->delete_temp("quest");
			me->set_temp("quest/last_id", quest["last_id"]);
			me->apply_condition("job_busy", 30);
			call_out("done", 3, target, me, quest, -1);
		}
		
		else */
		call_out("done", 3, target, me, quest, 1);
		return;
	}
}

void done(object target, object me, mapping quest, int i)
{    
       int count,exp,pot;

       if(me && i >= 0){
       if(target){	  
	    message_vision("\n$N点头道："+me->name()+"这娃娃不赖，让我指点他几招，就当是迟来的见面礼吧！\n", target, me);
	    tell_room( environment(me), target->name() + "在" + me->name()+ "耳边小声地说了些话。\n", ({ me, target }) );
	    // give rewards.
	    TASK_D->give_reward(me, me->query_temp("quest"), -1, ABS(me->query("songshan_points")/100));
	    me->apply_condition("job_busy",2+random(5));
	if ( me->query("family/family_name") == "嵩山派"
	  && me->query_skill("hanbing-zhenqi"))
	    me->improve_skill("hanbing-zhenqi",me->query("int")*2);

	count = me->query("songshan_points");
	if (count<1) count=1;
	pot= me->query_temp("quest/pot_reward");
	exp= me->query_temp("quest/exp_reward");
	log_file( "job/ss_job",sprintf("%s %s(%s)第%d次嵩山请人任务获得%d点经验，%d点潜能，经验：%d\n",
	ctime(time())[4..19],me->name(),me->query("id"),count,exp,pot,me->query("combat_exp")));
	me->delete_temp("quest");
	me->delete_temp("songshan_job");
	me->add("songshan_points", 1);
	tell_room(environment(target), target->query("name")+"大笑两声，在知客弟子带领下到厢房休息去了。\n", ({target}));
	if(target->return_home()){
		target->delete_temp("songshan_job");
		target->delete_temp("last_lost_to");
		target->clear_condition("songshan_busy");
		target->set("chat_chance", target->query("chat_c"));
		if(!target->query_temp("location"))
			target->delete("location");
		target->set_leader(0);
		target->reincarnate();
	}
	else destruct(target);
		}
	}
	else if(target){ 
		tell_room(environment(target), target->query("name")+"大笑两声，在知客弟子带领下到厢房休息去了。\n", ({target}));   
		destruct(target);
	}
}

string do_ask_hb()
{
	object me = this_player();

	if (!me->query("ss/hb_improve"))
		return "什么这个那个的呀？！";
	if (random(2)==1)
		return "这个嘛，具体地点我也不是很清楚！";
	me->set_temp("ss/hb_1",1);
		return "大概地点就在一个峡谷附近，具体地点我实在想不起来了。";
}

string do_ask_grj()
{
	object me=this_player() , weapon;
	
	if ((string)me->query("family/master_name") != "左冷禅")
		return 0;	
	weapon = present("guanri jian", this_object());
	if(!objectp(weapon))    weapon = unew(BINGQI_D("sword/guanri-jian"));
	if(!objectp(weapon))
		return "观日剑已经被你师兄拿走了,现在不在我手里。";  
	command("unwield guanri jian");
	weapon->move(me);
	command("wield jian");
	message_vision("\n$N给了$n一把观日剑。\n", this_object(), me);
}


 string do_ask_times(object who)
{	  
	object me;
	int i;
	me = this_player(); 
	if(!intp(i = me->query("songshan_points")))
		return "你这个小混蛋，你是请过人，还是杀过人? 想骗我 ?"; 
	message_vision("$N对着$n想了想，说道，你目前已记功" + chinese_number(i) + "次。\n", who,me);
	return "我嵩山向来赏罚分明，继续努力吧！";
}

